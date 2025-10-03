/*
 * rtc_ds3231.h
 *
 *  Created on: 30.05.2022
 *      Author: Michael
 */

#ifndef MAIN_RTC_DS3231_H_
#define MAIN_RTC_DS3231_H_



typedef enum weekday_e{
	monday = 1,			//Offset for weekday, chip goes on from 1-7
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday
}weekday_t;

typedef enum month_e{
	january = 1,		//Offset for month, chip goes on from 1-12
	february,
	march,
	april,
	may,
	june,
	july,
	august,
	september,
	october,
	november,
	december
}month_t;

//!!! watch out !!! month and weekday have an internal offset. to access the texts, just subtract 1. Else, memory gets corrupted
const char* weekday [] = { "Monday" , "Tuesday" ,	"Wednesday" , "Thursday" , "Friday" , "Saturday" , "Sunday"};
const char* month [] = { "January" , "February" , "March" , "April" , "May" , "June" , "July" ,
						 "August" , "September" , "October" ,"November" , "December" };

typedef struct time_ds3231_s{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	weekday_t day;
	uint8_t date;
	month_t month;
	uint8_t year;
}time_ds3231_t;


//RTC timekeeping registers
#define RTC_REG_SECONDS				0x00
#define RTC_REG_MINUTES				0x01
#define RTC_REG_HOURS				0x02
#define RTC_REG_DAY					0x03
#define RTC_REG_DATE				0x04
#define RTC_REG_MONTH_CENTURY		0x05
#define RTC_REG_YEAR				0x06
#define RTC_REG_AL1_SECONDS			0x07
#define RTC_REG_AL1_MINUTES			0x08
#define RTC_REG_AL1_HOURS			0x09
#define RTC_REG_AL1_DAY_DATE		0x0A
#define RTC_REG_AL2_MINUTES			0x0B
#define RTC_REG_AL2_HOURS			0x0C
#define RTC_REG_AL2_DAY_DATE		0x0D
#define RTC_REG_CONTROL				0x0E
#define RTC_REG_CONTROL_STATUS		0x0F
#define RTC_REG_AGING_OFFSET		0x10
#define RTC_REG_MSB_OF_TEMP			0x11
#define RTC_REG_LSB_OF_TEMP			0x12

#define RTC_CONTROL_REG_EOSC		BIT7
#define RTC_CONTROL_REG_BBSQW		BIT6
#define RTC_CONTROL_REG_CONV		BIT5
#define RTC_CONTROL_REG_RS2			BIT4
#define RTC_CONTROL_REG_RS1			BIT3
#define RTC_CONTROL_REG_INTCN		BIT2
#define RTC_CONTROL_REG_A2IE		BIT1
#define RTC_CONTROL_REG_A1IE		BIT0

#define RTC_TIME_MODE_12H			BIT6
#define RTC_TIME_IS_PM				BIT5

#define RTC_STATUS_REG_OSF			BIT7
#define RTC_STATUS_REG_EN32kHz		BIT3
#define RTC_STATUS_REG_BSY			BIT2
#define RTC_STATUS_REG_A2F			BIT1
#define RTC_STATUS_REG_A1F			BIT0


#endif /* MAIN_RTC_DS3231_H_ */
