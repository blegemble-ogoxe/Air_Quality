/* 
 * File:   AT.h
 * Author: USER
 *
 * Created on June 1, 2022, 9:37 AM
 */
#include <stdint.h>
#ifndef AT_H
#define	AT_H

uint8_t phone_book[20][10];


void AT_SendString(char* s);
void AT_SetConfig(void);
void AT_getTime();
void AT_SendSMS(uint8_t alert);
void AT_Call(uint8_t alert);
void AT_getNumbers(uint8_t alert,uint8_t type);
void AT_clearPhoneBook();
void AT_writeLogs(uint8_t alert);
void clearRxData(void);


#ifdef	__cplusplus
extern "C" {
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* AT_H */

