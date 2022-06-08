#include "AT.h"
#include <string.h>
#include <stdio.h>
#include "mcc_generated_files/uart1.h"
#include "global.h"
#define FCY 3786000UL
#include "libpic30.h"

void AT_SendString(char* s)
{
	while(*s)
	{
		UART1_Write(*s++);
	}
}


void AT_SetConfig(void){



}


void AT_getTime(){
    

}

void AT_SendSMS(uint8_t alert){  
    uint8_t i = 0;
    int8_t buf[20];
    int8_t message[24];
    
    sprintf(buf,"Ogoxe : Alerte Niveau %d\x1A",alert);
    AT_getNumbers(alert,1);
    
    while(strlen(phone_book[i])!=0){
        sprintf(buf,"AT+CMGS=\"%s\n\"",phone_book[i]);
        AT_SendString(buf);
        AT_SendString(message);
        i++;
    }    
    AT_clearPhoneBook();
}

void AT_Call(uint8_t alert){
    int8_t buf[15];
    int8_t msg[]="VOICE CALL:BEGIN";
    int8_t * word;
    int8_t delim[]="\r\n";
    uint8_t cpt=0;
    uint8_t i=0;
    AT_getNumbers(alert,2);
    
    while(strlen(phone_book[i])!=0){
        clearRxData();
        cpt=0;
        sprintf(buf,"ATD%s;\r",phone_book[i]);
        AT_SendString(buf);
        if(alert == 1) sprintf(buf,"AT+CCMXPLAY=\"d:/pre_alerte.wav\",3,0\r",phone_book[i]);
        else {sprintf(buf,"AT+CCMXPLAY=\"d:/alerte.wav\",3,0\r",phone_book[i]);}
        
        //We need to check if the voice call has begun
        word = strtok(HAT_rxData,delim);
        while (word != NULL){            
            if(strcmp(word,msg)==0){
                AT_SendString(buf);
                __delay_ms(6000); //Give delay to pay audio file remotely
                break;
            }
            if(cpt>100){
                break;
            }
            __delay_ms(100);
            cpt++;
        }
        AT_SendString("ATH\r");
        i++;
    }    
}

void AT_getNumbers(uint8_t alert,uint8_t type){
    int8_t buf[20];
    int8_t folder[10];
    int8_t file[5];
    int8_t delim[3]="\r\n";  
    int8_t num[10]="0123456789";
    int8_t * word;
    int8_t * ptr;
    uint8_t index=0;    
    
    AT_clearPhoneBook();
    
    //send the command to get files containing numbers
    if(alert == 1){
        strcpy(folder,"pre_alerte");
    }else strcpy(folder,"alerte");
    
    if(type == 1){
        strcpy(file,"SMS");
    }else strcpy(file,"appel");    
    
    sprintf(buf,"AT+CFTRANTX=\"d:/%s/%s.txt\"\r",folder,file);
    
    AT_SendString(buf);
    
    __delay_ms(500);
    
    //Break rxData into substrings, search for numbers and append them into phonebook
    word = strtok(HAT_rxData,delim);
    while (word != NULL){
        ptr = strpbrk(word,num);
        if(ptr != NULL){
            if(index<20){
                strcpy(phone_book[index],word);           
                index++;
            }
        }
        word = strtok(NULL, delim);
    }
}

void AT_clearPhoneBook(){
    uint8_t i;
    
    for(i=0;i<20;i++){
        strcpy(phone_book[i],"\0");
    }
}

void AT_writeLogs(uint8_t alert){

}

void clearRxData(void){
    int i=0;
    for(i=0;i<150;i++){
        HAT_rxData[i]='\0';
    }
}