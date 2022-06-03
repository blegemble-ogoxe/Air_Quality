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
    
void SetDeviceConfig(void);
uint16_t Byte2Word(uint8_t MSB,uint8_t LSB);
void configRTC(void);
void Get_RTC_Data(void);
void Get_Sensors_Data();
void SetDeviceConfig();




#ifdef	__cplusplus
}
#endif

#endif	/* USER_H */

