/**
  ******************************************************************************
  * File Name          : RF_Driver.h
  * Description        : Header for RF_Driver.c
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

#include "SW_Header.h"

/*Typedef*/
typedef struct
{
    uint8_t ID;
    uint8_t Address[5];     /*LSB byte first => index 0*/
    uint8_t data[32];
} RF_Device;

/*Prototypes*/
void RF_Test (void);
StatusType RF_Init(void);
StatusType RF_Write_RX_Add(RF_Device* DevPtr);
StatusType RF_StartListen(void);
StatusType RF_StopListen(void);
StatusType RF_Transmit(uint8_t DeviceID, RF_Device* DevPtr);
StatusType RF_Receive(RF_Device* DevPtr);
StatusType RF_DeInit(void);


