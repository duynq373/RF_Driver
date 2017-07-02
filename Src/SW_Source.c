/**
  ******************************************************************************
  * File Name          : SW_Source.c
  * Description        : SW main file
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

#include "SW_Header.h"
#include "RF_Driver.h"

#ifdef PTX_DEVICE
uint32_t state = 0;
uint32_t BTN_IRQ = 0;

RF_Device RX_Devs[NUMBER_OF_RX_DEV];

void SW_main (void)
{
    uint32_t index = 0;
    
    SPI_CS_DIS;
    CE_LOW;
    HAL_Delay(10);
    
//    RF_Test();
    
    /*Device info*/
    RX_Devs[0].ID = 1;
    
    RX_Devs[0].Address[0] = 0x51;
    RX_Devs[0].Address[1] = 0x4E;
    RX_Devs[0].Address[2] = 0x59;
    RX_Devs[0].Address[3] = 0x55;
    RX_Devs[0].Address[4] = 0x44;
    
    
    RX_Devs[0].data[0] = 0xCA;
    RX_Devs[0].data[1] = 0;
    for (index = 2; index < 32; index++)
    {
        RX_Devs[0].data[index] = 0;
    }
    
    (void) RF_Init();
    
    while(1)
    {
//        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
//        {
//            while (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
//            {}
//            if (state == 0)
//            {
//                state = 1;
//            }
//            else
//            {
//                state = 0;
//            }
//        }
        if (BTN_IRQ == 1)
        {
            BTN_IRQ = 0;
            
            if (state == 1)
            {
                state = 0;
                RX_Devs[0].data[1] = 0x01;
                (void)RF_Transmit(1, RX_Devs);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            }
            else
            {
                state = 1;
                RX_Devs[0].data[1] = 0x00;
                (void)RF_Transmit(1, RX_Devs);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            }
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* Prevent unused argument(s) compilation warning */
    //UNUSED(GPIO_Pin);
    if (GPIO_PIN_13 == GPIO_Pin)
    {
        BTN_IRQ = 1;
    }
}

#endif /*PTX_DEVICE*/


#ifdef PRX_DEVICE
RF_Device RX_Dev;

//uint8_t tmpVar[1] = {0};
uint32_t RcvStat = 0;
uint32_t RF_IRQ_flg = 0;

void SW_main (void)
{
//    uint32_t state = 0;
    uint32_t index = 0;
    
    
    SPI_CS_DIS;
    HAL_Delay(10);
    
//    RF_Test();
    
    /*Device info*/
    RX_Dev.ID = 1;
    
    RX_Dev.Address[0] = 0x51;
    RX_Dev.Address[1] = 0x4E;
    RX_Dev.Address[2] = 0x59;
    RX_Dev.Address[3] = 0x55;
    RX_Dev.Address[4] = 0x44;
    
    for (index = 0; index < 32; index++)
    {
        RX_Dev.data[index] = 0;
    }
    
    RF_Init();
    
    /*Set address for Rx device*/
    (void) RF_Write_RX_Add(&RX_Dev);
    
    (void) RF_StartListen();
    
//    RF_Test();
    while(1)
    {
        RF_Test();
        if (RcvStat == 1)
        {
            RF_IRQ_flg = 0;
            (void) RF_Receive(&RX_Dev);
            (void) RF_StopListen();
            
            if (0xCA == RX_Dev.data[0])     /*Valid command*/
            {
                if (0x01 == RX_Dev.data[1])
                {
                    LED_ON;
                }
                else
                {
                    LED_OFF;
                }
            }
            else
            {
                HAL_Delay (50);/*Delay for somewhile before start listen again*/
                (void) RF_StartListen();
            }
        }
        //tmpVar[0] = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_PIN_9 == GPIO_Pin)
    {
        RF_IRQ_flg = 1;
    }
}
#endif /*PRX_DEVICE*/
