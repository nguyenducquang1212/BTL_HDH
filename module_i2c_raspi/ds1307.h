/*
 * ds1307.h
 *
 *  Created on: Aug 18, 2021
 *      Author: Quang Anh
 */

#ifndef DS1307_H_
#define DS1307_H_

typedef struct sDS1307
{
	uint8_t sec;

	uint8_t min;

	uint8_t hour;

	uint8_t day;

	uint8_t month;

	uint8_t year;

	uint8_t date;

	uint8_t buffer [8];

} DS1307_t;

extern DS1307_t ds;

void RTC_Init(void);

void getTime(DS1307_t* ds1307);

void setTime(DS1307_t* ds1307, uint8_t sec, uint8_t min, uint8_t hour,
		uint8_t date, uint8_t month, uint8_t year);

#endif /* DS1307_H_ */
