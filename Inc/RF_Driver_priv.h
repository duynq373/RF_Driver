/**
  ******************************************************************************
  * File Name          : RF_Driver.h
  * Description        : Private header for RF_Driver.c
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

#include "SW_Header.h"
#include "nRF24L01p.h"
#include <string.h>

/*Prototypes*/
static StatusType RF_Read_Register(uint8_t reg, uint8_t* buf, uint8_t len);
static StatusType RF_Write_Register(uint8_t reg, uint8_t* buf, uint8_t len);
static StatusType RF_Read_Payload(uint8_t* buf);
static StatusType RF_Write_Payload(uint8_t* buf);
static StatusType RF_Flush_RX(void);
static StatusType RF_Flush_TX(void);
static StatusType RF_Get_Status(uint8_t* buf);

/*Defines*/
#define     RF_WK_CH            30
