#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

#include "rtc_ds3231.h"

#define BUTTON_SET_TIME 					GPIO_NUM_9

//Run in fast mode, pin 4 SCL, pin 5 SDA, 1 sec timeout
#define I2C_MASTER_SCL_IO           GPIO_NUM_4     			   /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           GPIO_NUM_5				   /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency*/
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define RTC_DS3231_I2C_ADDR                0x68    			   /*!< Slave address of the DS3231 RTC */

//TODO: add a bunch of macros for better reading of the bit manipulation stuff
#define CHECK_ESP_ERROR_STATE(_s)			if((_s) != ESP_OK){ return _s;}

const char* TAG = "I2C_RTC";

static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}


static esp_err_t rtc_ds3231_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(I2C_MASTER_NUM, RTC_DS3231_I2C_ADDR, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
}


static esp_err_t rtc_ds3231__register_write_byte(uint8_t reg_addr, uint8_t data)
{
    int ret;
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(I2C_MASTER_NUM, RTC_DS3231_I2C_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    return ret;
}



esp_err_t setTime(time_ds3231_t* data){
	esp_err_t state = ESP_OK;
	state = rtc_ds3231__register_write_byte(RTC_REG_DAY	, data->day);


	uint8_t temp = (data->year / 10) << 4;
	//temp |= ((data->year % 10 ) & 0x0F) ;
	state = rtc_ds3231__register_write_byte(RTC_REG_YEAR, temp);
	return state;
}


esp_err_t getActualTime(time_ds3231_t* data){
	uint8_t tempBuffer = 0;
	esp_err_t state = ESP_OK;

	state = rtc_ds3231_register_read(RTC_REG_SECONDS, &tempBuffer, 1);
	CHECK_ESP_ERROR_STATE(state);
	data->seconds = (tempBuffer & 0x0F) + ( ((tempBuffer & 0x70) >> 4) * 10);	//in bit 0-3 are the seconds from 0-9, in bit 4-6 seconds*10
	//TODO: Add macros to get a better reading of bit manipulation stuff

	state = rtc_ds3231_register_read(RTC_REG_MINUTES, &tempBuffer, 1);
	CHECK_ESP_ERROR_STATE(state);
	data->minutes = (tempBuffer & 0x0F) + ( ((tempBuffer & 0x70) >> 4) * 10);

	//TODO: check if 12/24 hour format reader works!!
	state = rtc_ds3231_register_read(RTC_REG_HOURS, &tempBuffer, 1);
	CHECK_ESP_ERROR_STATE(state);
	{
		uint8_t hours = (tempBuffer & 0x0F);			//add low byte. No matter what case, its always right
		if(tempBuffer & RTC_TIME_MODE_12H){
			hours += ((tempBuffer & 0x10) >> 4) * 10;	//add lowest bit of higher nibble
			if(tempBuffer & RTC_TIME_IS_PM){
				hours += 12;							//its pm, so +12
			}
		}else{
			hours += ((tempBuffer & 0x30) >> 4) * 10;	//with "normal" time format
		}
		data->hours = hours;
	}

	state = rtc_ds3231_register_read(RTC_REG_DAY, &tempBuffer, 1);
	CHECK_ESP_ERROR_STATE(state);
	data->day = (tempBuffer & 0x07);

	state = rtc_ds3231_register_read(RTC_REG_DATE, &tempBuffer, 1);
	CHECK_ESP_ERROR_STATE(state);
	data->date = (tempBuffer & 0x0F);

	state = rtc_ds3231_register_read(RTC_REG_MONTH_CENTURY, &tempBuffer, 1);
	CHECK_ESP_ERROR_STATE(state);
	data->month = (tempBuffer & 0x0F);

	state = rtc_ds3231_register_read(RTC_REG_YEAR, &tempBuffer, 1);
	CHECK_ESP_ERROR_STATE(state);
	data->year = (tempBuffer & 0x0F);

	return state;
}


static uint8_t gReqToSetTime = 0;
void isrHandler(void* args){
	//TODO: add debouncer
	gReqToSetTime = 1;
}

esp_err_t configPeriphery(){
	gpio_config_t button = {
			.pin_bit_mask = (1 << BUTTON_SET_TIME),
			.mode = GPIO_MODE_INPUT,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.pull_up_en = GPIO_PULLUP_ENABLE,
			.intr_type = GPIO_INTR_NEGEDGE,
	};
	esp_err_t state = ESP_OK;
	state = gpio_config(&button);
	CHECK_ESP_ERROR_STATE(state);
	state = gpio_install_isr_service(0);
	CHECK_ESP_ERROR_STATE(state);
	state = gpio_isr_handler_add(BUTTON_SET_TIME,isrHandler , 0);
	return  0;
}

void app_main(void)
{
	//initialize I2C and GPIO
	{
		esp_err_t initError = i2c_master_init();
		if(initError){
			ESP_LOGI(TAG, "Failed to initialize I2C. Code: %d", initError);
			exit(initError);
		}

		initError = configPeriphery();
		if(initError){
			ESP_LOGI(TAG, "Failed to initialize GPIO. Code: %d", initError);
			exit(initError);
		}
	}


	time_ds3231_t actualTime = { 0 };
	time_ds3231_t setTimeTo = {
			.hours = 5,
			.minutes = 33,
			.date = 15,
			.day = tuesday,
			.year = 22,

	};

    while (true) {
    	esp_err_t state = getActualTime(&actualTime);

    	if(state){
    		ESP_LOGI(TAG, "Failed to get actual values.");
    	}else{
    		ESP_LOGI(TAG, "Time of day: %.2u : %.2u : %.2u" , actualTime.hours, actualTime.minutes, actualTime.seconds);
    		ESP_LOGI(TAG, "%s, %u of %s, 20%.2u" , weekday[actualTime.day - 1], actualTime.date, month[actualTime.month - 1], actualTime.year); //Offset in day and month is because of array starts at 0, chip values start from 1
    	}

    	if(gReqToSetTime){
    		ESP_LOGI(TAG, "Button was pressed");
    		setTime(&setTimeTo);
    		gReqToSetTime = 0;
    	}

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

