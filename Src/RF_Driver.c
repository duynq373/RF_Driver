/**
  ******************************************************************************
  * File Name          : RF_Driver.c
  * Description        : Interfaces to work with RF module
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

#include "RF_Driver.h"
#include "RF_Driver_priv.h"

/******************************************************************************/
void RF_Test (void)
{
//    uint8_t tmpVar[5] = {0,0,0,0,0};
    /*TEST CASE 1*/
    /*Test Read Write Register functions OK*/
#ifdef PRX_DEVICE
    uint8_t tmpVar[5] = {0,0,0,0,0};
    (void) RF_Read_Register(STATUS, tmpVar, 1);
    if (tmpVar[0] & RX_DR)
    {
        RcvStat = 1;
    }
    else 
    {
        RcvStat = 0;
    }
#endif
    
//    tmpVar[0] = 0x01;
//    (void) RF_Write_Register(EN_AA, tmpVar, 1);
//    (void) RF_Read_Register(EN_AA, tmpVar, 1);
//    tmpVar[0] = 0x3F;
//    (void) RF_Write_Register(EN_AA, tmpVar, 1);
//    (void) RF_Read_Register(EN_AA, tmpVar, 1);
    
    /*TEST CASE 2*/
    /*Test get status function :)*/
//    (void) RF_Get_Status(tmpVar);
    
    /*TEST CASE 3*/
    /*Test RF Init function*/
//    (void) RF_Init();
//    printf("READ BACK:\n");
//    printf("RF_CH:\n");
//    (void) RF_Read_Register(RF_CH, tmpVar, 1);
//    printf("RF_SETUP:\n");
//    (void) RF_Read_Register(RF_SETUP, tmpVar, 1);
//    printf("EN_AA:\n");
//    (void) RF_Read_Register(EN_AA, tmpVar, 1);
//    printf("FEATURE:\n");
//    (void) RF_Read_Register(FEATURE, tmpVar, 1);
//    printf("RX_PW_P0:\n");
//    (void) RF_Read_Register(RX_PW_P0, tmpVar, 1);
//    printf("SETUP_AW:\n");
//    (void) RF_Read_Register(SETUP_AW, tmpVar, 1);
//    printf("CONFIG:\n");
//    (void) RF_Read_Register(CONFIG, tmpVar, 1);
//    printf("SETUP_RETR:\n");
//    (void) RF_Read_Register(SETUP_RETR, tmpVar, 1);

    /*TEST CASE 4*/
//    (void) RF_Read_Register(RX_ADDR_P0,tmpVar, 5);
    
    /*TEST CASE 5*/
//    (void) RF_Get_Status(tmpVar);
    /*TEST CASE 6*/
    /*TEST CASE 7*/
    /*TEST CASE 8*/
}   

/******************************************************************************/
StatusType RF_Init(void)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[5];
    
    SPI_CS_DIS;
    CE_LOW;
    
    HAL_Delay(5);
    
    /*Set working channel*/
    tmpVar[0] = RF_WK_CH;
    status = RF_Write_Register(RF_CH, tmpVar, 1);
    
    /*Set Data Rate and RF Power*/
    status = RF_Read_Register(RF_SETUP, tmpVar, 1);
    tmpVar[0] &= (~(RF_DR_HIGH|RF_DR_LOW));         /*Set data rate to 1Mbps*/
    tmpVar[0] |= (RF_PWR_HIGH|RF_PWR_HIGH);         /*Set RF Power to 0dBm*/
    status = RF_Write_Register(RF_SETUP, tmpVar, 1);
    
    /*Set auto ACK*/
    tmpVar[0] = ENAA_P0;    /*Enable for channel 0. Only use this channel*/
    status = RF_Write_Register(EN_AA, tmpVar, 1);
    
    /*Set no ACK payload and no dynamic payload*/
    tmpVar[0] = 0x00;       /*Enable for channel 0. Only use this channel*/
    status = RF_Write_Register(FEATURE, tmpVar, 1);
    
    /*Set fix payload 32 bytes*/
    tmpVar[0] = 0x20;       /*Set for channel 0. Only use this channel*/
    status = RF_Write_Register(RX_PW_P0, tmpVar, 1);
    
    /*Set address width*/
    tmpVar[0] = 0x03;       /*5 bytes*/
    status = RF_Write_Register(SETUP_AW, tmpVar, 1);
    
    /*Enable 2 bytes CRC and RX_DR interrupt source only*/
    status = RF_Read_Register(CONFIG, tmpVar, 1);
    tmpVar[0] |= EN_CRC;            /*Enable CRC*/
    tmpVar[0] |= CRCO;              /*2 bytes CRC*/
    tmpVar[0] &= (~MASK_RX_DR);     /*Enable RX_DR interrupt*/
    tmpVar[0] |= MASK_TX_DS;        /*Disable TX_DS interrupt*/
    tmpVar[0] |= MASK_MAX_RT;       /*Disable MAX_RT interrupt*/
    status = RF_Write_Register(CONFIG, tmpVar, 1);
    
    /*Set number of retry and time between retry while transmit fail*/
    tmpVar[0] = (ARD & 0x30);       /*1000 us*/
    tmpVar[0] |= (ARC & 0x05);      /*5 retries*/
    status = RF_Write_Register(SETUP_RETR, tmpVar, 1);
    
    /*Set mode Rx or Tx: no need, done on transmit or receive*/
    
    /*Flush buffers*/
    status = RF_Flush_RX();
    status = RF_Flush_TX();
    
    return status;
}

/******************************************************************************/
/*Functions sequence:
    + RF_StartListen
    + Got interrupt:
        * RF_Receive
        * RF_StopListen
*/
StatusType RF_StartListen(void)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[1] = {0};
    
    /*Power up and set Rx Mode*/
    status = RF_Read_Register(CONFIG, tmpVar, 1);
    tmpVar[0] |= (PWR_UP | PRIM_RX);
    status = RF_Write_Register(CONFIG, tmpVar, 1);
    
    /* Wait for the radio start up. Maximum 1.5 ms from Power Down*/
    HAL_Delay(2);
    
    /*Reset interrupt results in RF chip*/
    tmpVar[0] = (RX_DR | TX_DS | MAX_RT);
    status = RF_Write_Register(STATUS, tmpVar, 1);

    /*Flush buffers*/
    status = RF_Flush_RX();
    status = RF_Flush_TX();

    /*Start Listen*/
    CE_HIGH;
    
    return status;
}

/******************************************************************************/
StatusType RF_StopListen(void)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[1] = {0};
    
    CE_LOW;
    
    /*Flush buffers*/
    status = RF_Flush_RX();
    status = RF_Flush_TX();
    
    /*Power Down to save energy*/
    status = RF_Read_Register(CONFIG, tmpVar, 1);
    tmpVar[0] &= (~PWR_UP);     /*Power down*/
    status = RF_Write_Register(CONFIG, tmpVar, 1);
    
    return status;
}

/******************************************************************************/
StatusType RF_Write_RX_Add(RF_Device* DevPtr)
{
    StatusType status = STATUS_ERROR;
    
    status = RF_Write_Register(RX_ADDR_P0, DevPtr->Address, 5);
    
#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("WRITE COMMAND SUCCESS\n");
    }
    else
    {
        printf("WRITE COMMAND ERROR\n");
    }
#endif
    return status;
}

/******************************************************************************/
StatusType RF_Transmit(uint8_t DeviceID, RF_Device* DevPtr)
{
    StatusType status = STATUS_ERROR;
    uint32_t index = 0;
    uint32_t timer = 0;
    uint8_t tmpVar[1] = {0};
    
    /*Get index of device from array*/
    for (index = 0; index < NUMBER_OF_RX_DEV; index++)
    {
        if (DevPtr[index].ID == DeviceID)
        {
            break;
        }
        if (index == NUMBER_OF_RX_DEV)
        {
            return status;
        }
    }
    
    /*Reset interrupt results in RF chip*/
    tmpVar[0] = (RX_DR | TX_DS | MAX_RT);
    status = RF_Write_Register(STATUS, tmpVar, 1);
    
    /*Power up and set Tx Mode*/
    status = RF_Read_Register(CONFIG, tmpVar, 1);
    tmpVar[0] |= PWR_UP;
    tmpVar[0] &= (~PRIM_RX);
    status = RF_Write_Register(CONFIG, tmpVar, 1);
    
    /* Wait for the radio start up. Maximum 1.5 ms from Power Down*/
    HAL_Delay(2);
    
    /*Write TX0 address*/
    status = RF_Write_Register(TX_ADDR, DevPtr[index].Address, 5);
    
    /*Write RX0 address*/
    status = RF_Write_Register(RX_ADDR_P0, DevPtr[index].Address, 5);
    
    /*Write TX Payload*/
    status = RF_Write_Payload(DevPtr[index].data);
    
    /*Let It Go, Let the Data Go :)*/
    CE_HIGH;
    HAL_Delay(15);      /*Minimum 5 retries x 1000us = 5ms + other delays*/
    CE_LOW;
    
    timer = HAL_GetTick();
    
    while (1)
    {
        if ((HAL_GetTick() - timer) > 1000)
        {
#ifdef DEBUG_ENABLE
            printf("TRANSMIT FAIL TIME OUT\n");
#endif
            status = STATUS_ERROR;
            break;
        }
        if (STATUS_OK == RF_Get_Status(tmpVar))
        {
            if (tmpVar[0] & TX_DS)
            {
#ifdef DEBUG_ENABLE
                printf("TRANSMIT OK\n");
#endif
                status = STATUS_OK;
                break;
            }
            else if (tmpVar[0] & MAX_RT)
            {
#ifdef DEBUG_ENABLE
                printf("TRANSMIT FAIL MAX RETRY\n");
#endif
                status = STATUS_ERROR;
                break;
            }
        }
        
    }
    
    status = RF_Flush_TX();
    
    return status;
}

/******************************************************************************/
StatusType RF_Receive(RF_Device* DevPtr)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[1] = {0};
#ifdef DEBUG_ENABLE
    uint32_t index = 0;
#endif
    
    /*Check whether package received or not*/
    if (STATUS_OK == RF_Get_Status(tmpVar))
    {
        if (tmpVar[0] & RX_DR)
        {
            status = RF_Read_Payload(DevPtr->data);
#ifdef DEBUG_ENABLE
            printf("RECEIVED DATA\n");
            for (index = 0; index < 32; index++)
            {
                printf ("Data[%d] = %x ", index, DevPtr->data[index]);
            }
            printf("\n");
#endif            
        }
        else
        {
#ifdef DEBUG_ENABLE
            printf("NO VALID RECEIVED DATA\n");
#endif
        }
    }
    return status;
}

/******************************************************************************/
StatusType RF_DeInit(void)
{
    StatusType status = STATUS_ERROR;
    
    status = RF_StopListen();
    
    return status;
}

/******************************************************************************/
static StatusType RF_Read_Register(uint8_t reg, uint8_t* buf, uint8_t len)
{
    StatusType status = STATUS_ERROR;
    uint32_t index = 0;
    uint8_t tmpVar[33];
    uint8_t tmpRx[33];
    uint8_t loc_len = len;
    
    /*If read data length argument is larger than 32 bytes => return ERROR*/
    if (loc_len > 32)
    {
#ifdef DEBUG_ENABLE
        printf("READ COMMAND ERROR: DATA LENGTH IS NOT CORRECT\n");
#endif
        return status;
    }
    
    /*Initialize variables*/
    for (index = 0; index < 33; index++)
    {
        tmpRx[index] = 0;
    }
    
    
    /*Prepare TX frame*/
    /*Command*/
    tmpVar[0] = (R_REGISTER | (REGISTER_MASK & reg));
    
    /*Lengh is increased 1 for command byte*/
    loc_len++;
    
    /*NOP for TX*/
    for (index = 1; index < loc_len; index++)
    {
        tmpVar[index] = NOP;
    }
    
    SPI_CS_EN;
    status = (StatusType) HAL_SPI_TransmitReceive(&SPI_Hndlr, tmpVar, tmpRx, 
                                                                  loc_len, 500);
    SPI_CS_DIS;
    
    /*Lengh is decreased 1 for data only*/
    loc_len--;
    
    /*Assign received data to input buffer*/
    memcpy((void*) buf, (void*) (tmpRx + 1), loc_len);
    
#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("READ COMMAND SUCCESS\n");
        printf("Register %x value:\n", reg);
        for (index = 0; index < loc_len; index++)
        {
            printf ("%x ", *buf);
            buf++;
        }
        printf ("\n");
    }
    else
    {
        printf("READ COMMAND ERROR\n");
    }
#endif

    return status;
}

/******************************************************************************/
static StatusType RF_Write_Register(uint8_t reg, uint8_t* buf, uint8_t len)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[33];
    uint8_t tmpRx[33];
    uint8_t loc_len = len;
    
    /*If write data length argument is larger than 32 bytes => return ERROR*/
    if (loc_len > 32)
    {
#ifdef DEBUG_ENABLE
        printf("WRITE COMMAND ERROR: DATA LENGTH IS NOT CORRECT\n");
#endif
        return status;
    }
    
    /*Prepare TX frame*/
    /*Command*/
    tmpVar[0] = (W_REGISTER | (REGISTER_MASK & reg));
    /*Copy data from input buffer to transmit data*/
    memcpy ((void*) (tmpVar + 1), (void*) buf, loc_len);
    
    /*Lengh is increased 1 for command byte*/
    loc_len++;
    
    SPI_CS_EN;
    status = (StatusType) HAL_SPI_TransmitReceive(&SPI_Hndlr, tmpVar, tmpRx, 
                                                                  loc_len, 500);
    SPI_CS_DIS;

#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("WRITE COMMAND SUCCESS\n");
    }
    else
    {
        printf("WRITE COMMAND ERROR\n");
    }
#endif
    
    return status;
}

/******************************************************************************/
/*Static Payload length only: 32 Bytes*/
static StatusType RF_Read_Payload(uint8_t* buf)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[33];
    uint8_t tmpRx[33];
    uint32_t index = 0;
    
    /*Initialize variables*/
    for (index = 0; index < 33; index++)
    {
        tmpRx[index] = 0;
    }
    
    /*Prepare TX frame*/
    /*Command*/
    tmpVar[0] = R_RX_PAYLOAD;
    
    /*NOP for TX*/
    for (index = 1; index < 33; index++)
    {
        tmpVar[index] = NOP;
    }
    
    SPI_CS_EN;
    status = (StatusType) HAL_SPI_TransmitReceive(&SPI_Hndlr, tmpVar, tmpRx, 33, 
                                                                           500);
    SPI_CS_DIS;
    
    /*Assign the received data to input buffer*/
    for (index = 1; index < 33; index++)
    {
        *buf = tmpRx[index];
        buf++;
    }
    
#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("READ COMMAND SUCCESS\n");
        for (index = 0; index < 32; index++)
        {
            printf ("%d ", *buf);
            buf++;
        }
        printf ("\n");
    }
    else
    {
        printf("READ COMMAND ERROR\n");
    }
#endif

    return status;
}

/******************************************************************************/
/*Static Payload length only: 32 Bytes*/
static StatusType RF_Write_Payload(uint8_t* buf)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[33];
    uint8_t tmpRx[33];

    /*Prepare TX frame*/
    /*Command*/
    tmpVar[0] = W_TX_PAYLOAD;
    
    /*copy data from passed buf to transmit data*/
    memcpy ((void*) (tmpVar + 1), (void*) buf, 32);
    
    SPI_CS_EN;
    status = (StatusType) HAL_SPI_TransmitReceive(&SPI_Hndlr, tmpVar, tmpRx, 33, 
                                                                           500);
    SPI_CS_DIS;

#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("WRITE COMMAND SUCCESS\n");
    }
    else
    {
        printf("WRITE COMMAND ERROR\n");
    }
#endif

    return status;
}

/******************************************************************************/
static StatusType RF_Flush_RX(void)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[1] = {FLUSH_RX};
    uint8_t tmpRx[1] = {0};

    SPI_CS_EN;
    status = (StatusType) HAL_SPI_TransmitReceive(&SPI_Hndlr, tmpVar, tmpRx, 1,
                                                                           500);
    SPI_CS_DIS;
    
#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("FLUSH RX SUCCESS\n");
    }
    else
    {
        printf("FLUSH RX ERROR\n");
    }
#endif
    
    return status;
}

/******************************************************************************/
static StatusType RF_Flush_TX(void)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[1] = {FLUSH_TX};
    uint8_t tmpRx[1] = {0};

    SPI_CS_EN;
    status = (StatusType) HAL_SPI_TransmitReceive(&SPI_Hndlr, tmpVar, tmpRx, 1,
                                                                           500);
    SPI_CS_DIS;
    
#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("FLUSH TX SUCCESS\n");
    }
    else
    {
        printf("FLUSH TX ERROR\n");
    }
#endif
    
    return status;
}

/******************************************************************************/
/*My stupid function LOL*/
static StatusType RF_Get_Status(uint8_t* buf)
{
    StatusType status = STATUS_ERROR;
    uint8_t tmpVar[1] = {(R_REGISTER|STATUS)};
    uint8_t tmpRx[1] = {0};

    SPI_CS_EN;
    status = (StatusType) HAL_SPI_TransmitReceive(&SPI_Hndlr, tmpVar, tmpRx, 1,
                                                                           500);
    SPI_CS_DIS;
    *buf = tmpRx[0];

#ifdef DEBUG_ENABLE
    if (STATUS_OK == status)
    {
        printf("READ STATUS SUCCESS\n");
        printf("Status register value: %x\n", tmpRx[0]);
    }
    else
    {
        printf("READ STATUS ERROR\n");
    }
#endif
    
    return status;
}
