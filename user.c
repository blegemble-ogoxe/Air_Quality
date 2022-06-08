#include <stdlib.h>
#include <math.h>
#include "user.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/uart2.h"
#include "mcc_generated_files/i2c1.h"
#include "global.h"
#define FCY 3786000UL
#include "libpic30.h"


uint8_t config_cpt=0;

void USB_SendString(char* s)
{
	while(*s)
	{
		UART2_Write(*s++);
	}
}

void SetDeviceConfig(void){
    
    //When the config has been received form UART, this function is called
    //USB_rxData[] should be full
    
    year = Byte2Word(USB_rxData[0],USB_rxData[1]);
    month = Byte2Word(USB_rxData[2],USB_rxData[3]);
    day = Byte2Word(USB_rxData[4],USB_rxData[5]);
    weekday = Byte2Word(USB_rxData[6],USB_rxData[7]);
    hour = Byte2Word(USB_rxData[8],USB_rxData[9]);
    minute = Byte2Word(USB_rxData[10],USB_rxData[11]);
    second = Byte2Word(USB_rxData[12],USB_rxData[13]);
    DeviceID = Byte2Word(USB_rxData[14],USB_rxData[15]);
    Temperature_Alert_threshold = Byte2float(USB_rxData[16],USB_rxData[17],USB_rxData[18],USB_rxData[19]);
    Temperature_Norm_freq = USB_rxData[20];
    Temperature_Fast_freq = USB_rxData[21];
    Humidity_Alert_threshold = Byte2float(USB_rxData[22],USB_rxData[23],USB_rxData[24],USB_rxData[25]);
    Humidity_Norm_freq = USB_rxData[26];
    Humidity_Fast_freq = USB_rxData[27];
    PM10_Alert_threshold = Byte2float(USB_rxData[28],USB_rxData[29],USB_rxData[30],USB_rxData[31]);
    PM10_Norm_freq = USB_rxData[32];
    PM10_Fast_freq = USB_rxData[33];
    PM25_Alert_threshold = Byte2float(USB_rxData[34],USB_rxData[35],USB_rxData[36],USB_rxData[37]);
    PM25_Norm_freq = USB_rxData[38];
    PM25_Fast_freq = USB_rxData[39];
    PM40_Alert_threshold = Byte2float(USB_rxData[40],USB_rxData[41],USB_rxData[42],USB_rxData[43]);
    PM40_Norm_freq = USB_rxData[44];
    PM40_Fast_freq = USB_rxData[45];
    PM100_Alert_threshold = Byte2float(USB_rxData[46],USB_rxData[47],USB_rxData[48],USB_rxData[49]);
    PM100_Norm_freq = USB_rxData[50];
    PM100_Fast_freq = USB_rxData[51];
    NC05_Alert_threshold = Byte2float(USB_rxData[52],USB_rxData[53],USB_rxData[54],USB_rxData[55]);
    NC05_Norm_freq = USB_rxData[56];
    NC05_Fast_freq = USB_rxData[57];
    NC10_Alert_threshold = Byte2float(USB_rxData[58],USB_rxData[59],USB_rxData[60],USB_rxData[61]);
    NC10_Norm_freq = USB_rxData[62];
    NC10_Fast_freq = USB_rxData[63];
    NC25_Alert_threshold = Byte2float(USB_rxData[64],USB_rxData[65],USB_rxData[66],USB_rxData[67]);
    NC25_Norm_freq = USB_rxData[68];
    NC25_Fast_freq = USB_rxData[69];
    NC40_Alert_threshold = Byte2float(USB_rxData[70],USB_rxData[71],USB_rxData[72],USB_rxData[73]);
    NC40_Norm_freq = USB_rxData[74];
    NC40_Fast_freq = USB_rxData[75];
    NC100_Alert_threshold = Byte2float(USB_rxData[76],USB_rxData[77],USB_rxData[78],USB_rxData[79]);
    NC100_Norm_freq = USB_rxData[80];
    NC100_Fast_freq = USB_rxData[81];
    TypPartSize_Alert_threshold = Byte2float(USB_rxData[82],USB_rxData[83],USB_rxData[84],USB_rxData[85]);
    TypPartSize_Norm_freq = USB_rxData[86];
    TypPartSize_Fast_freq = USB_rxData[87];
    NO2_Alert_threshold = Byte2Word(USB_rxData[88],USB_rxData[89]);
    NO2_Norm_freq = USB_rxData[90];
    NO2_Fast_freq = USB_rxData[91];
    CO_Alert_threshold = Byte2Word(USB_rxData[92],USB_rxData[93]);
    CO_Norm_freq = USB_rxData[94];
    CO_Fast_freq = USB_rxData[95];
    CO2_Alert_threshold = Byte2Word(USB_rxData[96],USB_rxData[97]);
    CO2_Norm_freq = USB_rxData[98];
    CO2_Fast_freq = USB_rxData[99];
    NH3_Alert_threshold = Byte2Word(USB_rxData[100],USB_rxData[101]);
    NH3_Norm_freq = USB_rxData[102];
    NH3_Fast_freq = USB_rxData[103];
    
    configRTC();
    
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
    NO2 = floor((float)(NO2_16*0.125/1.53)); //mV
    
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
    uint8_t bit=0,i=0;
    for(i = 0; i < 2; i++) {
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

void checkThresholds(void){
    
    if(NO2>NO2_Alert_threshold){
        NO2_freq = NO2_Fast_freq;
    }else NO2_freq = NO2_Norm_freq;
}

/**
 End of File
*/
