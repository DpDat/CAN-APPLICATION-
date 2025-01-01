#ifndef LPUART_REGISTER_H
#define LPUART_REGISTER_H

#include <stdint.h>

#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
#define     __I     volatile const       /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */


typedef struct{
    /*******************************************************************************
    *                             LPUART Version ID Register (VERID)
    ******************************************************************************/    
    union{
        __I uint32_t VERID_Register;
        struct{
            __I uint32_t FEATURE  :16; /*Feature Specification Number*/
            __I uint32_t MINOR    :8;  /*Minor Version Number*/
            __I uint32_t MAJOR    :8;  /*Major Version Number*/
        }VERID_Bits;
    };

    /*******************************************************************************
    *                             LPUART PARAM Register (PARAM)
    ******************************************************************************/ 
    union{
        __I uint32_t PARAM_Register;
        struct{
            __I uint32_t TXFIFO  :8; /*Number of Transmit Data Registers*/
            __I uint32_t RXFIFO  :8; /*Number of Receive Data Registers*/
            uint32_t           :16;
        }PARAM_Bits;
    };

    /*******************************************************************************
    *                             LPUART Global Register (GLOBAL)
    ******************************************************************************/
    union{
        __IO uint32_t GLOBAL_Register;
        struct{
            uint32_t :1;
            __IO uint32_t RST      :1; /*Software Reset*/
            uint32_t :30;
        }GLOBAL_Bits;
    };

    /*******************************************************************************
    *                             LPUART Pin Configuration Register (PINCFG)
    ******************************************************************************/
    union{
        __IO uint32_t PINCFG_Register;
        struct{
            __IO uint32_t TRGSEL   :2; /*Trigger Select*/
            uint32_t            :30;
        }PINCFG_Bits;
    };
    /*******************************************************************************
    *                             LPUART Baud Rate Register (BAUD)
    ******************************************************************************/
    union{
        __IO uint32_t BAUD_Register;
        struct{
            __IO uint32_t SBR      :13; /*Baud Rate Modulo Divisor*/
            __IO uint32_t SBNS     :1;  /*Stop Bit Number Select*/
            __IO uint32_t RXEDGIE  :1;  /*RX Input Active Edge Interrupt Enable*/
            __IO uint32_t LBKDIE   :1;  /*LIN Break Detect Interrupt Enable*/
            __IO uint32_t RESYNCDIS:1;  /*Resync Disable*/
            __IO uint32_t BOTHEDGE :1;  /*Both Edge Sampling*/
            __IO uint32_t MATCFG   :2;  /*Match Configuration*/
            __IO uint32_t RIDMAE   :1;  /*Receiver Idle DMA Enable*/
            __IO uint32_t RDMAE    :1;  /*Receiver Full DMA Enable*/
            uint32_t   :1;  
            __IO uint32_t TDMAE    :1;  /*Transmitter DMA Enable*/
            __IO uint32_t OSR      :5;  /*Oversampling Ratio*/
            __IO uint32_t M10      :1;  /*10-bit Mode select*/
            __IO uint32_t MAEN2    :1;  /*Match Address Mode Enable 2*/
            __IO uint32_t MAEN1    :1;  /*Match Address Mode Enable 1*/
        }BAUD_Bits;
    };
    /*******************************************************************************
    *                             LPUART Status Register (STAT)
    ******************************************************************************/
    union{
        __IO uint32_t STAT_Register;
        struct{
            uint32_t :14;
            __IO uint32_t MA2F     :1; /*Match 2 Flag*/
            __IO uint32_t MA1F     :1; /*Match 1 Flag*/
            __IO uint32_t PF       :1; /*Parity Error Flag*/
            __IO uint32_t FE       :1; /*Framing Error Flag*/
            __IO uint32_t NF       :1; /*Noise Flag*/
            __IO uint32_t OR       :1; /*Receiver Overrun Flag*/
            __IO uint32_t IDLE     :1; /*Idle Line Flag*/
            __I  uint32_t RDRF     :1; /*Receive Data Register Full Flag*/
            __I  uint32_t TC       :1; /*Transmission Complete Flag*/
            __I  uint32_t TDRE     :1; /*Transmit Data Register Empty Flag*/
            __I  uint32_t RAF      :1; /*Receiver Active Flag*/
            __IO uint32_t LBKDE    :1; /*LIN Break Detection Enable*/
            __IO uint32_t BRK13    :1; /*Break Character Generation Length*/
            __IO uint32_t RWUID    :1; /*Receive Wake Up Idle Detect*/
            __IO uint32_t RXINV    :1; /*Receive Data Inversion*/
            __IO uint32_t MSBF     :1; /*MSB First*/
            __IO uint32_t RXEDGIF  :1; /*RX Input Active Edge Interrupt Flag*/
            __IO uint32_t LBKDIF   :1; /*LIN Break Detect Interrupt Flag*/
            }STAT_Bits;
    };
    /*******************************************************************************
    *                             LPUART Control Register (CTRL)
    ******************************************************************************/
    union{
        __IO uint32_t CTRL_Register;
        struct{
            __IO uint32_t PT       :1; /*Parity Type*/
            __IO uint32_t PE       :1; /*Parity Enable*/
            __IO uint32_t ILT      :1; /*Idle Line Type Select*/
            __IO uint32_t WAKE     :1; /*Receiver Wakeup Method Select*/
            __IO uint32_t M        :1; /*9-bit or 8-bit Mode Select*/
            __IO uint32_t RSRC     :1; /*Receiver Source Select*/
            __IO uint32_t DOZEEN   :1; /*Doze Enable*/
            __IO uint32_t LOOPS    :1; /*Loop Mode Select*/
            __IO uint32_t IDLECFG  :3; /*Idle Configuration*/
            __IO uint32_t M7       :1; /*7-bit Mode Select*/
            uint32_t            :2;
            __IO uint32_t MA2IE    :1; /*Match 2 Interrupt Enable*/
            __IO uint32_t MA1IE    :1; /*Match 1 Interrupt Enable*/
            __IO uint32_t SBK      :1; /*Send Break*/
            __IO uint32_t RWU      :1; /*Receiver Wakeup Control*/
            __IO uint32_t RE       :1; /*Receiver Enable*/
            __IO uint32_t TE       :1; /*Transmitter Enable*/
            __IO uint32_t ILIE     :1; /*Idle Line Interrupt Enable*/
            __IO uint32_t RIE      :1; /*Receiver Full Interrupt or DMA Transfer Enable*/
            __IO uint32_t TCIE     :1; /*Transmission Complete Interrupt Enable*/
            __IO uint32_t TIE      :1; /*Transmit Interrupt or DMA Transfer Enable*/
            __IO uint32_t PEIE     :1; /*Parity Error Interrupt Enable*/
            __IO uint32_t FEIE     :1; /*Framing Error Interrupt Enable*/
            __IO uint32_t NEIE     :1; /*Noise Error Interrupt Enable*/
            __IO uint32_t ORIE     :1; /*Overrun Interrupt Enable*/
            __IO uint32_t TXINV    :1; /*Transmit Data Inversion*/
            __IO uint32_t TXDIR    :1; /*Transmitter Pin Data Direction in Single-Wire mode*/
            __IO uint32_t R9T8     :1; /*Receive Bit 9 / Transmit Bit 8*/
            __IO uint32_t R8T9     :1; /*Receive Bit 8 / Transmit Bit 9*/
        }CTRL_Bits;
    };
    /*******************************************************************************
    *                             LPUART Data Register (DATA)
    ******************************************************************************/
    union{
        __IO uint32_t DATA_Register;
        struct{
            __IO uint32_t R0T0     :1; /*Receiver Data Bit 0 or Transmitter Data Bit 0*/
            __IO uint32_t R1T1     :1; /*Receiver Data Bit 1 or Transmitter Data Bit 1*/
            __IO uint32_t R2T2     :1; /*Receiver Data Bit 2 or Transmitter Data Bit 2*/
            __IO uint32_t R3T3     :1; /*Receiver Data Bit 3 or Transmitter Data Bit 3*/
            __IO uint32_t R4T4     :1; /*Receiver Data Bit 4 or Transmitter Data Bit 4*/
            __IO uint32_t R5T5     :1; /*Receiver Data Bit 5 or Transmitter Data Bit 5*/
            __IO uint32_t R6T6     :1; /*Receiver Data Bit 6 or Transmitter Data Bit 6*/
            __IO uint32_t R7T7     :1; /*Receiver Data Bit 7 or Transmitter Data Bit 7*/
            __IO uint32_t R8T8     :1; /*Receiver Data Bit 8 or Transmitter Data Bit 8*/
            __IO uint32_t R9T9     :1; /*Receiver Data Bit 9 or Transmitter Data Bit 9*/
            uint32_t            :1;
            __I  uint32_t IDLINE   :1; /*Idle Line*/
            __I  uint32_t RXEMPT   :1; /*Receive Buffer Empty*/
            __IO uint32_t FRETSC   :1; /*Frame Error / Transmit Special Character*/
            __I  uint32_t PARITYE  :1; /*Parity Error*/
            __I  uint32_t NOISY    :1; /*Noise Detected Flag*/
            uint32_t            :16;
        }DATA_Bits;
    };
    /*******************************************************************************
    *                             LPUART Match Address Register (MATCH)
    ******************************************************************************/
    union{
        __IO uint32_t MATCH_Register;
        struct{
            __IO uint32_t MA1      :10; /*Match Address 1*/
            uint32_t            :6;
            __IO uint32_t MA2      :10; /*Match Address 2*/
            uint32_t            :6;
        }MATCH_Bits;
    };
    /*******************************************************************************
    *                             LPUART Modem IrDA Register (MODIR)
    ******************************************************************************/
    union{
        __IO uint32_t MODIR_Register;
        struct{
            __IO uint32_t TXCTSE   :1; /*Transmitter clear to send enable*/
            __IO uint32_t TXRTSE   :1; /*Transmitter request to send enable*/
            __IO uint32_t TXRTSPOL :1; /*Transmitter request to send polarity*/
            __IO uint32_t RXRTSE   :1; /*Receiver request to send enable*/
            __IO uint32_t TXCTSC   :1; /*Transmitter clear to send enable*/
            __IO uint32_t TXCTSSRC :1; /*Transmitter clear to send source*/
            uint32_t            :2;
            __IO uint32_t RTSWATER :2; /*Receive RTS Configuration*/
            uint32_t            :6;
            __IO uint32_t TNP      :2; /*Transmitter narrow pulse*/
            __IO uint32_t IREN     :1; /*IrDA Enable*/
            uint32_t            :13;
        }MODIR_Bits;
    };
    /*******************************************************************************
    *                             LPUART FIFO Register (FIFO)
    ******************************************************************************/
    union{
        __IO uint32_t FIFO_Register;
        struct{
            __IO uint32_t RXFIFOSIZE    :3; /*Receive FIFO. Buffer Depth*/
            __IO uint32_t RXFE          :1; /*Receive FIFO Enable*/
            __IO uint32_t TXFIFOSIZE    :3; /*Transmit FIFO. Buffer Depth*/
            __IO uint32_t TXFE          :1; /*Transmit FIFO Enable*/
            __IO uint32_t RXUFE         :1; /*Receive FIFO Underflow Interrupt Enable*/
            __IO uint32_t TXOFE         :1; /*Transmit FIFO Overflow Interrupt Enable*/
            __IO uint32_t RXIDEN        :3; /*Receiver Idle Empty Enable*/
            uint32_t            :1;
            __O  uint32_t RXFLUSH       :1; /*Receive FIFO/Buffer Flush*/
            __O  uint32_t TXFLUSH       :1; /*Transmit FIFO/Buffer Flush*/
            __IO uint32_t RXUF          :1; /*Receive  Buffer Underflow Flag*/
            __IO uint32_t TXOF          :1; /*Transmit Buffer Overflow Flag*/
            uint32_t            :4;
            __I  uint32_t RXEMPT        :1; /*Receive Buffer/FIFO Empty*/
            __I  uint32_t TXEMPT        :1; /*Transmit Buffer/FIFO Empty*/
            uint32_t            :8;
        }FIFO_Bits;
    };
    /*******************************************************************************
    *                             LPUART Watermark Register (WATER)
    ******************************************************************************/
    union{
        __IO uint32_t WATER_Register;
        struct{
            __IO uint32_t TXWATER       :2; /*Transmit Watermark*/
            uint32_t    :6;
            __I  uint32_t TXCOUNT       :3; /*Transmit Counter*/
            uint32_t    :5;
            __IO uint32_t RXWATER       :2; /*Receive Watermark*/         
            uint32_t    :6;
            __IO uint32_t RXCOUNT       :3; /*Receive Counter*/
            uint32_t    :5;
        }WATER_Bits;
    };
}LPUART_TypeDef;



#define LPUART0_BASE_ADDR          (0x4006A000u)
#define LPUART1_BASE_ADDR          (0x4006B000u)
#define LPUART2_BASE_ADDR          (0x4006C000u)

#define LPUART0                    ((LPUART_TypeDef*)LPUART0_BASE_ADDR)
#define LPUART1                    ((LPUART_TypeDef*)LPUART1_BASE_ADDR)
#define LPUART2                    ((LPUART_TypeDef*)LPUART2_BASE_ADDR)

#endif 