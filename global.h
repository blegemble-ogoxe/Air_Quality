/* 
 * File:   global.h
 * Author: USER
 *
 * Created on May 31, 2022, 2:54 PM
 */

#include <stdint.h>
#include "mcc_generated_files/i2c1.h"
#ifndef GLOBAL_H
#define	GLOBAL_H

extern I2C1_MESSAGE_STATUS statusI2C;
extern uint8_t RTC_I2C_ADDR;
extern uint8_t RTC_Read_I2C_ADDR;
extern uint8_t RTC_Write_I2C_ADDR;

extern uint8_t DeviceID;
extern uint8_t State1;
extern uint8_t ConfigCPT;

extern uint8_t second;
extern uint8_t minute;
extern uint8_t hour;
extern uint8_t day;
extern uint8_t weekday;
extern uint8_t month;
extern uint8_t year;


extern uint8_t USB_rxData[50];
extern uint8_t HAT_rxData[150];
extern uint8_t z1;
extern uint8_t z2;

extern uint16_t NH3_Alert_threshold;
extern uint16_t NH3_Normal_freq;
extern uint16_t NH3_Fast_freq;

extern uint8_t TH_sensor_ADDR;
extern float Temperature;
extern float Humidity;

extern uint8_t PPM_sensor_ADDR;
extern float PM10;
extern float PM25;
extern float PM40;
extern float PM100;
extern float NC05;
extern float NC10;
extern float NC25;
extern float NC45;
extern float NC100;
extern float TypPartSize;

extern uint8_t CO2_sensor_ADDR;
extern uint16_t CO2;

extern uint8_t ADC_sensor_ADDR;
extern int8_t NO2;
extern int16_t CO;
extern int16_t NH3;


extern uint16_t CO_Alert_threshold;
extern uint16_t CO_Normal_freq;
extern uint16_t CO_Fast_freq;

extern uint16_t CO2_Alert_threshold;
extern uint16_t CO2_Normal_freq;
extern uint16_t CO2_Fast_freq;

extern uint16_t PPM_Alert_threshold;
extern uint16_t PPM_Normal_freq;
extern uint16_t PPM_Fast_freq;

extern uint16_t NO2_Alert_threshold;
extern uint16_t NO2_Normal_freq;
extern uint16_t NO2_Fast_freq;

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

