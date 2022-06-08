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

extern uint16_t TMR1_INTERRUPT_TICKER_FACTOR;

extern I2C1_MESSAGE_STATUS statusI2C;
extern uint8_t RTC_I2C_ADDR;
extern uint8_t RTC_Read_I2C_ADDR;
extern uint8_t RTC_Write_I2C_ADDR;

extern uint8_t DeviceID;
extern uint8_t State1;

extern uint8_t second;
extern uint8_t minute;
extern uint8_t hour;
extern uint8_t day;
extern uint8_t weekday;
extern uint8_t month;
extern uint8_t year;

extern uint8_t USB_rxData[105];
extern uint8_t HAT_rxData[100];
extern uint8_t z1;
extern uint8_t z2;

extern uint8_t TH_sensor_ADDR;
extern float Temperature;
extern float Humidity;

extern float Temperature_Alert_threshold;
extern uint8_t Temperature_Fast_freq;
extern uint8_t Temperature_Norm_freq;

extern float Humidity_Alert_threshold;
extern uint8_t Humidity_Fast_freq;
extern uint8_t Humidity_Norm_freq;

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
extern int16_t NO2;
extern int16_t CO;
extern int16_t NH3;

extern float PM10_Alert_threshold;
extern uint8_t PM10_Fast_freq;
extern uint8_t PM10_Norm_freq;
extern float PM25_Alert_threshold;
extern uint8_t PM25_Fast_freq;
extern uint8_t PM25_Norm_freq;
extern float PM40_Alert_threshold;
extern uint8_t PM40_Fast_freq;
extern uint8_t PM40_Norm_freq;
extern float PM100_Alert_threshold;
extern uint8_t PM100_Fast_freq;
extern uint8_t PM100_Norm_freq;
extern float NC05_Alert_threshold;
extern uint8_t NC05_Fast_freq;
extern uint8_t NC05_Norm_freq;
extern float NC10_Alert_threshold;
extern uint8_t NC10_Fast_freq;
extern uint8_t NC10_Norm_freq;
extern float NC25_Alert_threshold;
extern uint8_t NC25_Fast_freq;
extern uint8_t NC25_Norm_freq;
extern float NC40_Alert_threshold;
extern uint8_t NC40_Fast_freq;
extern uint8_t NC40_Norm_freq;
extern float NC100_Alert_threshold;
extern uint8_t NC100_Fast_freq;
extern uint8_t NC100_Norm_freq;
extern float TypPartSize_Alert_threshold;
extern uint8_t TypPartSize_Fast_freq;
extern uint8_t TypPartSize_Norm_freq;

extern uint16_t NO2_Alert_threshold;
extern uint8_t NO2_Fast_freq;
extern uint8_t NO2_Norm_freq;
extern uint8_t NO2_freq;
extern uint8_t NO2_tmr_cpt;

extern uint16_t CO_Alert_threshold;
extern uint8_t CO_Fast_freq;
extern uint8_t CO_Norm_freq;

extern uint16_t CO2_Alert_threshold;
extern uint8_t CO2_Fast_freq;
extern uint8_t CO2_Norm_freq;

extern uint16_t NH3_Alert_threshold;
extern uint8_t NH3_Fast_freq;
extern uint8_t NH3_Norm_freq;

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

