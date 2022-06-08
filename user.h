/* 
 * File:   user.h
 * Author: USER
 *
 * Created on May 31, 2022, 2:56 PM
 */

#include <stdint.h>

#ifndef USER_H
#define	USER_H
#ifdef	__cplusplus
extern "C" {
#endif

void USB_SendString(char* s);
void SetDeviceConfig(void);
uint16_t Byte2Word(uint8_t MSB,uint8_t LSB);
float Byte2float(uint8_t word1,uint8_t word2,uint8_t word3,uint8_t word4);
void configRTC(void);
void Get_RTC_Data(void);
void Get_Sensors_Data();
uint8_t CalcCrc(uint8_t *data);
void clearUSBRxData();
void checkThresholds(void);



#ifdef	__cplusplus
}
#endif

#endif	/* USER_H */

