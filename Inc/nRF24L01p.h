/**
  ******************************************************************************
  * File Name          : nRF24L01p.h
  * Description        : Header for nRF24L01p definition
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

/* COMMANDS */
#define     R_REGISTER      0x00
#define     W_REGISTER      0x20
#define     REGISTER_MASK   0x1F
#define     ACTIVATE        0x50
#define     R_RX_PL_WID     0x60
#define     R_RX_PAYLOAD    0x61
#define     W_TX_PAYLOAD    0xA0
#define     W_ACK_PAYLOAD   0xA8
#define     FLUSH_TX        0xE1
#define     FLUSH_RX        0xE2
#define     REUSE_TX_PL     0xE3
#define     NOP             0xFF

/* REGISTERS */
#define     CONFIG          0x00
#define     EN_AA           0x01
#define     EN_RXADDR       0x02
#define     SETUP_AW        0x03
#define     SETUP_RETR      0x04
#define     RF_CH           0x05
#define     RF_SETUP        0x06
#define     STATUS          0x07
#define     OBSERVE_TX      0x08
#define     RPD             0x09
#define     RX_ADDR_P0      0x0A
#define     RX_ADDR_P1      0x0B
#define     RX_ADDR_P2      0x0C
#define     RX_ADDR_P3      0x0D
#define     RX_ADDR_P4      0x0E
#define     RX_ADDR_P5      0x0F
#define     TX_ADDR         0x10
#define     RX_PW_P0        0x11
#define     RX_PW_P1        0x12
#define     RX_PW_P2        0x13
#define     RX_PW_P3        0x14
#define     RX_PW_P4        0x15
#define     RX_PW_P5        0x16
#define     FIFO_STATUS     0x17
#define     DYNPD           0x1C
#define     FEATURE         0x1D

/* BIT MASK */
#define     MASK_RX_DR      0x40        /*CONFIG*/
#define     MASK_TX_DS      0x20        /*CONFIG*/
#define     MASK_MAX_RT     0x10        /*CONFIG*/
#define     EN_CRC          0x08        /*CONFIG*/
#define     CRCO            0x04        /*CONFIG*/
#define     PWR_UP          0x02        /*CONFIG*/
#define     PRIM_RX         0x01        /*CONFIG*/

#define     ENAA_P5         0x20        /*EN_AA*/
#define     ENAA_P4         0x10        /*EN_AA*/
#define     ENAA_P3         0x08        /*EN_AA*/
#define     ENAA_P2         0x04        /*EN_AA*/
#define     ENAA_P1         0x02        /*EN_AA*/
#define     ENAA_P0         0x01        /*EN_AA*/

#define     ERX_P5          0x20        /*EN_RXADDR*/
#define     ERX_P4          0x10        /*EN_RXADDR*/
#define     ERX_P3          0x08        /*EN_RXADDR*/
#define     ERX_P2          0x04        /*EN_RXADDR*/
#define     ERX_P1          0x02        /*EN_RXADDR*/
#define     ERX_P0          0x01        /*EN_RXADDR*/

#define     AW              0x02        /*SETUP_AW*/

#define     ARD             0xF0        /*SETUP_RETR*/
#define     ARC             0x0F        /*SETUP_RETR*/

#define     CONT_WAVE       0x80        /*RF_SETUP*/
#define     RF_DR_LOW       0x20        /*RF_SETUP*/
#define     PLL_LOCK        0x10        /*RF_SETUP*/
#define     RF_DR_HIGH      0x08        /*RF_SETUP*/
#define     RF_PWR_HIGH     0x04        /*RF_SETUP*/
#define     RF_PWR_LOW      0x02        /*RF_SETUP*/

#define     RX_DR           0x40        /*STATUS*/
#define     TX_DS           0x20        /*STATUS*/
#define     MAX_RT          0x10        /*STATUS*/
#define     RX_P_NO         0x04        /*STATUS*/
#define     TX_FULL         0x01        /*STATUS*/

#define     PLOS_CNT        0x80        /*OBSERVE_TX*/
#define     ARC_CNT         0x04        /*OBSERVE_TX*/

#define     TX_REUSE        0x40        /*FIFO_STATUS*/
#define     TX_FIFO_FULL    0x20        /*FIFO_STATUS*/
#define     TX_EMPTY        0x10        /*FIFO_STATUS*/
#define     RX_FULL         0x02        /*FIFO_STATUS*/
#define     RX_EMPTY        0x01        /*FIFO_STATUS*/

#define     DPL_P5          0x20        /*DYNPD*/
#define     DPL_P4          0x10        /*DYNPD*/
#define     DPL_P3          0x08        /*DYNPD*/
#define     DPL_P2          0x04        /*DYNPD*/
#define     DPL_P1          0x02        /*DYNPD*/
#define     DPL_P0          0x01        /*DYNPD*/

#define     EN_DPL          0x04        /*FEATURE*/
#define     EN_ACK_PAY      0x02        /*FEATURE*/
#define     EN_DYN_ACK      0x01        /*FEATURE*/
