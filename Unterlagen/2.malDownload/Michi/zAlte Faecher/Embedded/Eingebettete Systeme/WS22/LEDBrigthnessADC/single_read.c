/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* ADC1 Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_adc_cal.h"
#include "led_strip.h"
#include <math.h>



//ADC Channels
#define ADC1_EXAMPLE_CHAN0          ADC1_CHANNEL_2
#define ADC2_EXAMPLE_CHAN0          ADC2_CHANNEL_0
static const char *TAG_CH[2][10] = {{"ADC1_CH2"}, {"ADC2_CH0"}};

#define BLINK_GPIO 						8
#define CONFIG_BLINK_LED_RMT_CHANNEL	0

//ADC Attenuation
#define ADC_EXAMPLE_ATTEN           ADC_ATTEN_DB_11

//ADC Calibration

#define ADC_EXAMPLE_CALI_SCHEME     ESP_ADC_CAL_VAL_EFUSE_TP

static int adc_raw[2][10];
static const char *TAG = "ADC SINGLE";
static const double maxOutputValue = 100.0f;
static const double maxInputVoltage = 3000.0f;
//static const double expConstant = (maxOutputValue / maxInputVoltage) * (1.0f / exp(1));
//static const double logConstant = 100.0f/(log(3000.0f));
static led_strip_t *pStrip_a;

static esp_adc_cal_characteristics_t adc1_chars;
static esp_adc_cal_characteristics_t adc2_chars;

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    pStrip_a = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, BLINK_GPIO, 1);
    /* Set all LED off to clear all pixels */
    pStrip_a->clear(pStrip_a, 50);
}


static bool adc_calibration_init(void)
{
    esp_err_t ret;
    bool cali_enable = false;

    ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
    if (ret == ESP_ERR_NOT_SUPPORTED) {
        ESP_LOGW(TAG, "Calibration scheme not supported, skip software calibration");
    } else if (ret == ESP_ERR_INVALID_VERSION) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else if (ret == ESP_OK) {
        cali_enable = true;
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
        esp_adc_cal_characterize(ADC_UNIT_2, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc2_chars);
    } else {
        ESP_LOGE(TAG, "Invalid arg");
    }

    return cali_enable;
}


void setLedIntensity(int voltage)
{
	double normedVal = (-1.0f) * maxOutputValue * log((double)voltage / maxInputVoltage);
	normedVal = normedVal > 255.0f ? 255.0f : normedVal;
	ESP_LOGI("INTENSITIY", "normed dec: %d, normed float: %lf", (uint32_t)normedVal, normedVal);
	pStrip_a->set_pixel(pStrip_a, 0, normedVal, 0, 0);
	pStrip_a->refresh(pStrip_a, 100);
}


void app_main(void)
{
    uint32_t voltage = 0;
    bool cali_enable = adc_calibration_init();

    //ADC1 config
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_EXAMPLE_CHAN0, ADC_EXAMPLE_ATTEN));

    configure_led();

    while (1) {
        adc_raw[0][0] = adc1_get_raw(ADC1_EXAMPLE_CHAN0);
        ESP_LOGI(TAG_CH[0][0], "raw  data: %d", adc_raw[0][0]);
        if (cali_enable) {
            voltage = esp_adc_cal_raw_to_voltage(adc_raw[0][0], &adc1_chars);
            setLedIntensity(voltage);
            ESP_LOGI(TAG_CH[0][0], "cali data: %d mV", voltage);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
