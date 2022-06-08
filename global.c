#include "global.h"
#include <stdint.h>
#include "mcc_generated_files/i2c1.h"

uint16_t TMR1_INTERRUPT_TICKER_FACTOR = 0;//75 = 10 min (75 * 8s)

I2C1_MESSAGE_STATUS statusI2C = I2C1_MESSAGE_PENDING;
uint8_t RTC_Read_I2C_ADDR=0xA3;
uint8_t RTC_Write_I2C_ADDR=0xA2;

uint8_t DeviceID=0;
uint8_t State1=0;

uint8_t second=0;
uint8_t minute=0;
uint8_t hour=0;
uint8_t day=0;
uint8_t weekday=0;
uint8_t month=0;
uint8_t year=0;

uint8_t USB_rxData[105]={0};
uint8_t HAT_rxData[100]={0};
uint8_t z1=0;
uint8_t z2=0;

uint8_t TH_sensor_ADDR=0x44;
float Temperature = 0;
float Humidity=0;

float Temperature_Alert_threshold=0;
uint8_t Temperature_Fast_freq=0;
uint8_t Temperature_Norm_freq=0;

float Humidity_Alert_threshold=0;
uint8_t Humidity_Fast_freq=0;
uint8_t Humidity_Norm_freq=0;

uint8_t PPM_sensor_ADDR=0x69;
float PM10=0;
float PM25=0;
float PM40=0;
float PM100=0;
float NC05=0;
float NC10=0;
float NC25=0;
float NC45=0;
float NC100=0;
float TypPartSize=0;

uint8_t CO2_sensor_ADDR = 0x62;
uint16_t CO2 = 0;

uint8_t ADC_sensor_ADDR = 0x48;
int16_t NO2=0;
int16_t CO=0;
int16_t NH3=0;

float PM10_Alert_threshold=0;
uint8_t PM10_Fast_freq=0;
uint8_t PM10_Norm_freq=0;
float PM25_Alert_threshold=0;
uint8_t PM25_Fast_freq=0;
uint8_t PM25_Norm_freq=0;
float PM40_Alert_threshold=0;
uint8_t PM40_Fast_freq=0;
uint8_t PM40_Norm_freq=0;
float PM100_Alert_threshold=0;
uint8_t PM100_Fast_freq=0;
uint8_t PM100_Norm_freq=0;
float NC05_Alert_threshold=0;
uint8_t NC05_Fast_freq=0;
uint8_t NC05_Norm_freq=0;
float NC10_Alert_threshold=0;
uint8_t NC10_Fast_freq=0;
uint8_t NC10_Norm_freq=0;
float NC25_Alert_threshold=0;
uint8_t NC25_Fast_freq=0;
uint8_t NC25_Norm_freq=0;
float NC40_Alert_threshold=0;
uint8_t NC40_Fast_freq=0;
uint8_t NC40_Norm_freq=0;
float NC100_Alert_threshold=0;
uint8_t NC100_Fast_freq=0;
uint8_t NC100_Norm_freq=0;
float TypPartSize_Alert_threshold=0;
uint8_t TypPartSize_Fast_freq=0;
uint8_t TypPartSize_Norm_freq=0;

uint16_t NO2_Alert_threshold=0;
uint8_t NO2_Fast_freq=0;
uint8_t NO2_Norm_freq=0;
uint8_t NO2_freq=0;
uint8_t NO2_tmr_cpt=0;

uint16_t CO_Alert_threshold=0;
uint8_t CO_Fast_freq=0;
uint8_t CO_Norm_freq=0;

uint16_t CO2_Alert_threshold=0;
uint8_t CO2_Fast_freq=0;
uint8_t CO2_Norm_freq=0;

uint16_t NH3_Alert_threshold=0;
uint8_t NH3_Fast_freq=0;
uint8_t NH3_Norm_freq=0;