/**
  ******************************************************************************
  * File Name          : SW_header.h
  * Description        : Software main header
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

#ifndef __SW_HDR_H
#define __SW_HDR_H

#include "HW_Config.h"

/*Prototypes*/
void SW_main (void);

/*Extern variables*/
#ifdef PRX_DEVICE
extern uint32_t RcvStat;
#endif

/*Typedef*/
/*Enum values are kept consistent with HAL_StatusTypeDef*/
typedef enum 
{
    STATUS_OK       = 0x00u,
    STATUS_ERROR    = 0x01u
} StatusType;

#endif /*__SW_HDR_H*/
