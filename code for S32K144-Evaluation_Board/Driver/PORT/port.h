#ifndef PORT_H_
#define PORT_H_

#include <stdint.h>
#include "pcc.h"

/* ----------------------------------------------------------------------------
   -- PORT Peripheral Access Layer
   ---------------------------------------------------------------------------- */
typedef struct
{
    volatile uint32_t    PCR[32];    /** 0x00 **/ /** Pin Control Register **/
    volatile uint32_t    GPCLR;      /** 0x80 **/ /** Global Pin Control Low Register **/
    volatile uint32_t    GPCHR;      /** 0x84 **/ /** Global Pin Control High Register **/
    volatile uint32_t    GICLR;      /** 0x88 **/ /** Global Interrupt Control Low Register **/
    volatile uint32_t    GICHR;      /** 0x8C **/ /** Global Interrupt Control High Register **/
        uint8_t RESERVE_1[16];
    volatile uint32_t    ISFR;       /** 0xA0 **/ /** Interrupt Status Flag Register **/
        uint8_t RESERVE_2[28];
    volatile uint32_t    DFER;       /** 0xC0 **/ /** Digital Filter Enable Register **/
    volatile uint32_t    DFCR;       /** 0xC4 **/ /** Digital Filter Clock Register **/
    volatile uint32_t    DFWR;       /** 0xC8 **/ /** Digital Filter Width Register **/
} PORT_Type;

/* PORT - Peripheral instance base addresses */
#define PORTA_BASE  0x40049000u
#define PORTA       ((PORT_Type*)PORTA_BASE) 

#define PORTB_BASE  0x4004A000u
#define PORTB       ((PORT_Type*)PORTB_BASE)  

#define PORTC_BASE  0x4004B000u
#define PORTC       ((PORT_Type*)PORTC_BASE) 

#define PORTD_BASE  0x4004C000u
#define PORTD       ((PORT_Type*)PORTD_BASE) 

#define PORTE_BASE  0x4004D000u
#define PORTE       ((PORT_Type*)PORTE_BASE) 

void PORT_init (void);
#endif /* PORT_H_ */