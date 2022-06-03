/* 
 * File:   modbus.h
 * Author: USER
 *
 * Created on May 30, 2022, 2:31 PM
 */

#ifndef MODBUS_H
#define	MODBUS_H

#ifdef	__cplusplus
extern "C" {
#endif

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/
unsigned char checkCRC(void);
void clearResponse(void);
void readReg(void);         /* I/O and Peripheral Initialization */
void readInputReg(void);
void writeReg(void);
void readCoil(void);
void readInputCoil(void);
void writeCoil(void);
void modbusDelay(void);              /* Writes to Timer0 for 1.04ms delay*/
void decodeIt(void);
unsigned int generateCRC(unsigned char);



#ifdef	__cplusplus
}
#endif

#endif	/* MODBUS_H */

