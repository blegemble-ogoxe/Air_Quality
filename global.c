#include "global.h"
#include <stdint.h>
#include "mcc_generated_files/i2c1.h"

I2C1_MESSAGE_STATUS statusI2C = I2C1_MESSAGE_PENDING;
uint8_t RTC_Read_I2C_ADDR=0xA3;
uint8_t RTC_Write_I2C_ADDR=0xA2;

uint8_t DeviceID=0;
uint8_t State1=0;
uint8_t ConfifCPT=0;

uint8_t second=0;
uint8_t minute=0;
uint8_t hour=0;
uint8_t day=0;
uint8_t weekday=0;
uint8_t month=0;
uint8_t year=0;

uint8_t USB_rxData[50]={0};
uint8_t HAT_rxData[150]={0};
uint8_t z1=0;
uint8_t z2=0;

        
uint16_t NH3_Alert_threshold=0;
uint16_t NH3_Normal_freq=0;
uint16_t NH3_Fast_freq=0;

uint8_t TH_sensor_ADDR=0x44;
float Temperature = 0;
float Humidity=0;

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

uint8_t C02_sensor_ADDR = 0x62;
uint16_t CO2 = 0;

uint8_t ADC_sensor_ADDR = 0x48;
int8_t NO2=0;
int16_t CO=0;
int16_t NH3=0;


uint16_t CO_Alert_threshold=0;
uint16_t CO_Normal_freq=0;
uint16_t CO_Fast_freq=0;

uint16_t CO2_Alert_threshold=0;
uint16_t CO2_Normal_freq=0;
uint16_t CO2_Fast_freq=0;

uint16_t PPM_Alert_threshold=0;
uint16_t PPM_Normal_freq=0;
uint16_t PPM_Fast_freq=0;

uint16_t NO2_Alert_threshold=0;
uint16_t NO2_Normal_freq=0;
uint16_t NO2_Fast_freq=0;