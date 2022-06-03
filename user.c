#include "user.h"
#include <math.h>
#include "global.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/i2c1.h"
#include "AT.h"

uint8_t config_cpt=0;

void USB_SendString(char* s)
{
	while(*s)
	{
		UART2_Write(*s++);
	}
}

void SetDeviceConfig(void){
    
    //when an interrupt comes from UART2, this function is called
    switch(config_cpt){
        case 0 : //Set RTC data
            USB_SendString("Year :\n");
            clearRxData();
            config_cpt++;
            break;
        case 1 :
            year = atoi(USB_rxData);
            clearUSBRxData();
            config_cpt++;
            break;
        case 2 : 
            USB_SendString("Month (1-12) :\n");
            clearRxData();
            config_cpt++;
            break;
        case 3 :
            month = atoi(USB_rxData);
            clearUSBRxData();
            config_cpt++;
            break;
        case 4 : 
            USB_SendString("Day (1-31) :\n");
            clearRxData();
            config_cpt++;
            break;
        case 5 :
            day = atoi(USB_rxData);
            clearUSBRxData();
            config_cpt++;
            break;            
        case 6 : 
            USB_SendString("WeekDay (Sunday 0 - Saturday 6) :\n");
            clearRxData();
            config_cpt++;
            break;
        case 7 : 
            weekday = atoi(USB_rxData);
            clearUSBRxData();
            config_cpt++;
            break;
        case 8 : 
            USB_SendString("Hour (0-23) :\n");
            clearRxData();
            config_cpt++;
            break;
        case 9 :
            hour = atoi(USB_rxData);
            clearUSBRxData();
            config_cpt++;
            break;
        case 10 : 
            USB_SendString("Minute (0-59) :\n");
            clearRxData();
            config_cpt++;
            break;
        case 11 :
            month = atoi(USB_rxData);
            clearUSBRxData();
            config_cpt++;
            break;
        case 12: 
            USB_SendString("Second (0-59) :\n");
            clearRxData();
            config_cpt++;
            break;
        case 13 :
            second = atoi(USB_rxData);
            clearUSBRxData();
            config_cpt=0; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            configRTC();
            break;
        default : break;
    }
}

uint16_t Byte2Word(uint8_t MSB,uint8_t LSB){
    uint16_t word=0;
    
    word = MSB;
    word = (word << 8) & 0xFF00;
    word |= LSB;
    return word;
}

float Byte2float(uint8_t word1,uint8_t word2,uint8_t word3,uint8_t word4)
{    
    return ((float)(word1<<24 | word2 << 16 | word3<<8 | word4));
}

void configRTC(void){
    uint8_t data[8];
    
    data[0] = 0x02; //register
    data[1] = second; //data
    data[2] = minute; //data
    data[3] = hour; //data
    data[4] = day; //data
    data[5] = weekday; //data
    data[6] = month; //data
    data[7] = year; //data
    I2C1_MasterWrite(data,8,RTC_Write_I2C_ADDR,&statusI2C);
}

void Get_RTC_Data(void){
    uint8_t data[7];
    uint8_t reg[]={0x02};
    
    I2C1_MasterWrite(reg,1,RTC_Write_I2C_ADDR,&statusI2C);
    I2C1_MasterRead(data,7,RTC_Read_I2C_ADDR,&statusI2C);
    second = data[0];
    minute = data[1];
    hour = data[2];
    day = data[3];
    weekday = data[4];
    month = data[5];
    year = data[6];
}

void Get_Sensors_Data(){
    uint8_t cmd[5]={0x2C,0x0D,0,0,0}; // T°/H : Clock stretching with medium repeatability
    uint8_t arg[2]={0};
    uint8_t data[60];
    uint16_t temperature =0;
    uint16_t humidity =0;
    int16_t CO_16=0;
    int16_t NO2_16=0;
    int16_t NH3_16=0;
    
    //Humidity and temperature
    I2C1_MasterWrite(cmd,2,TH_sensor_ADDR, &statusI2C);
    I2C1_MasterRead(data, 6, TH_sensor_ADDR, &statusI2C);
    
    temperature = Byte2Word(data[0],data[1]);
    humidity = Byte2Word(data[3],data[4]);
    
    Temperature = -45 + 174 * (Temperature/65535.0);
    Humidity = 100 * (humidity / 65535.0);
    
    //PPM sensor
    //start measurement
    cmd[0] = 0;
    cmd[1] = 0x10;
    arg[0] = 0x03;
    arg[1] = 0x00;
    cmd[4] = CalcCrc(arg);
    cmd[2] = arg[0];
    cmd[3] = arg[1];
    I2C1_MasterWrite(cmd,5,PPM_sensor_ADDR,&statusI2C);
    __delay_ms(1000);
    I2C1_MasterRead(data,30,PPM_sensor_ADDR,&statusI2C);
    
    PM10 = Byte2float(data[0],data[1],data[3],data[4]);
    
    PM25 = Byte2float(data[6],data[7],data[9],data[10]);
    
    PM40 = Byte2float(data[12],data[13],data[15],data[16]);
    
    PM100 = Byte2float(data[18],data[19],data[21],data[22]);
    
    NC05 = Byte2float(data[24],data[25],data[27],data[28]);
    
    NC10 = Byte2float(data[30],data[31],data[33],data[34]);
    
    NC25 = Byte2float(data[36],data[37],data[39],data[40]);
    
    NC45 = Byte2float(data[42],data[43],data[45],data[46]);
      
    NC100 = Byte2float(data[48],data[49],data[51],data[52]);
    
    TypPartSize = Byte2float(data[54],data[55],data[57],data[58]);
    
    //stop measurement
    cmd[0]=0x01;
    cmd[1]=0x04;
    I2C1_MasterWrite(cmd,2,PPM_sensor_ADDR,&statusI2C);
    
    
    //CO2
    cmd[0] = 0x21;
    cmd[1] = 0xb1;
    //start periodic measurement
    I2C1_MasterWrite(cmd,2,CO2_sensor_ADDR,&statusI2C);
    cmd[0] = 0xec;
    cmd[1] = 0x05;
    //read data
    I2C1_MasterWrite(cmd,2,CO2_sensor_ADDR,&statusI2C);
    __delay_ms(1);
    I2C1_MasterRead(data,2,CO2_sensor_ADDR,&statusI2C);
    CO2 = Byte2Word(data[0],data[1]);
    cmd[0] = 0x3f;
    cmd[1] = 0x86;
    //stop periodic measurement
    I2C1_MasterWrite(cmd,2,CO2_sensor_ADDR,&statusI2C);
    
    //ADC
    //NO2
    cmd[0] = 0x01;
    cmd[1] = 0xC3;
    cmd[2] = 0x83;
    I2C1_MasterWrite(cmd,3,ADC_sensor_ADDR,&statusI2C);// config for NO2
    cmd[1] = 0x00;
    cmd[2] = 0x00;
    I2C1_MasterWrite(cmd,2,CO2_sensor_ADDR,&statusI2C);//Addr pointer register
    I2C1_MasterRead(data,2,CO2_sensor_ADDR,&statusI2C);//Read Data
    NO2_16 = (int16_t) Byte2Word(data[0],data[1]);
    //NO2=0 => V=0V
    //NO2=32767 => V=4.096V
    //1 bit = 125uV
    NO2 = floor(NO2_16*0.125/1.53); //mV
    
    //CO
    cmd[0] = 0x01;
    cmd[1] = 0xD3;
    cmd[2] = 0x83;
    I2C1_MasterWrite(cmd,3,ADC_sensor_ADDR,&statusI2C);// config for CO
    cmd[1] = 0x00;
    cmd[2] = 0x00;
    I2C1_MasterWrite(cmd,2,CO2_sensor_ADDR,&statusI2C);//Addr pointer register
    I2C1_MasterRead(data,2,CO2_sensor_ADDR,&statusI2C);//Read Data
    CO_16 = (int16_t) Byte2Word(data[0],data[1]);
    CO = floor(CO_16*1.25/2.37); //mV
    
    //NH3
    cmd[0] = 0x01;
    cmd[1] = 0xE3;
    cmd[2] = 0x83;
    I2C1_MasterWrite(cmd,3,ADC_sensor_ADDR,&statusI2C);// config for NH3
    cmd[1] = 0x00;
    cmd[2] = 0x00;
    I2C1_MasterWrite(cmd,2,CO2_sensor_ADDR,&statusI2C);//Addr pointer register
    I2C1_MasterRead(data,2,CO2_sensor_ADDR,&statusI2C);//Read Data
    NH3_16 = (int16_t) Byte2Word(data[0],data[1]);
}

uint8_t CalcCrc(uint8_t *data) {
    uint8_t crc = 0xFF;
    uint8_t bit=0;
    for(int i = 0; i < 2; i++) {
        crc ^= data[i];
        for(bit = 8; bit > 0; --bit) {
            if(crc & 0x80) {
                crc = (crc << 1) ^ 0x31u;
                } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}


void clearUSBRxData(){
    uint8_t i=0;
    
    for(i=0;i<50;i++){
        USB_rxData[i] = '\0';
    }
    z2=0;
}

/**
 End of File
*/
