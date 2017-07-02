/**
  ******************************************************************************
  * File Name          : debug.c
  * Description        : Debug file
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

#ifndef __DEBUG_HDR
#define __DEBUG_HDR

#include "debug.h"

#ifdef DEBUG_ENABLE

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    if (HAL_UART_Transmit(&UART_Hndlr, (uint8_t *)&ch, 1, 0xFFFF) != HAL_OK)
    {
        //Error_Handler(4);
    }
    return ch;
}

#endif  /*DEBUG_ENABLE*/
#endif  /*__DEBUG_HDR*/
