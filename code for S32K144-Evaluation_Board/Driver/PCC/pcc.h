#ifndef PCC_H_
#define PCC_H_

#include<stdint.h>

typedef struct
{
    volatile uint32_t    PCC_FTFC;           /** 0x80 **/
    volatile uint32_t    PCC_DMAMUX;         /** 0x84 **/
        uint8_t RESERVE_1[8];
    volatile uint32_t    PCC_FlexCAN0;       /** 0x90 **/
    volatile uint32_t    PCC_FlexCAN1;       /** 0x94 **/
    volatile uint32_t    PCC_FTM3;           /** 0x98 **/
    volatile uint32_t    PCC_ADC1;           /** 0x9C **/
        uint8_t RESERVE_2[12];
    volatile uint32_t    PCC_FlexCAN2;       /** 0xAC **/
    volatile uint32_t    PCC_LPSPI0;         /** 0xB0 **/
    volatile uint32_t    PCC_LPSPI1;         /** 0xB4 **/
    volatile uint32_t    PCC_LPSPI2;         /** 0xB8* */
        uint8_t RESERVE_3[8];
    volatile uint32_t    PCC_PDB1;           /** 0xC4 **/
    volatile uint32_t    PCC_CRC;            /** 0xC8 **/
        uint8_t RESERVE_4[12];
    volatile uint32_t    PCC_PBD0;           /** 0xD8 **/
    volatile uint32_t    PCC_LPIT;           /** 0xDC **/
    volatile uint32_t    PCC_FTM0;           /** 0xE0 **/
    volatile uint32_t    PCC_FTM1;           /** 0xE4 **/
    volatile uint32_t    PCC_FTM2;           /** 0xE8 **/
    volatile uint32_t    PCC_ADC0;           /** 0xEC **/
        uint8_t RESERVE_5[4];
    volatile uint32_t    PCC_RTC;            /** 0xF4 **/
        uint8_t RESERVE_6[8];
    volatile uint32_t    PCC_LPTMR0;         /** 0x100 **/
        uint8_t RESERVE_7[32];
    volatile uint32_t    PCC_PORTA;          /** 0x124 **/
    volatile uint32_t    PCC_PORTB;          /** 0x128 **/
    volatile uint32_t    PCC_PORTC;          /** 0x12C **/
    volatile uint32_t    PCC_PORTD;          /** 0x130 **/
    volatile uint32_t    PCC_PORTE;          /** 0x134 **/
        uint8_t RESERVE_8[24];
    volatile uint32_t    PCC_SAI0;            /** 0x150 **/
    volatile uint32_t    PCC_SAI1;            /** 0x154 **/
        uint8_t RESERVE_9[16];
    volatile uint32_t    PCC_FlexIO;          /** 0x168 **/
        uint8_t RESERVE_10[24];
    volatile uint32_t    PCC_EWM;             /** 0x184 **/
        uint8_t RESERVE_11[16];
    volatile uint32_t    PCC_LPI2C0;          /** 0x198 **/
    volatile uint32_t    PCC_LPI2C1;          /** 0x19C **/
        uint8_t RESERVE_12[8];
    volatile uint32_t    PCC_LPUART0;         /** 0x1A8 **/
    volatile uint32_t    PCC_LPUART1;         /** 0x1AC **/
    volatile uint32_t    PCC_LPUART2;         /** 0x1B0 **/
        uint8_t RESERVE_13[4];
    volatile uint32_t    PCC_FTM4;             /** 0x1B8 **/
    volatile uint32_t    PCC_FTM5;             /** 0x1BC **/
    volatile uint32_t    PCC_FTM6;             /** 0x1C0 **/
    volatile uint32_t    PCC_FTM7;             /** 0x1C4 **/
} PCC_Type;


#define PCC_BASE    (0x40065000u + 0x80u) 
#define PCC         ((PCC_Type*)PCC_BASE)
#endif /* PCC_H_ */