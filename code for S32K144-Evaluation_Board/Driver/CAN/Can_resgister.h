#ifndef CAN_RESISTER_H
#define CAN_RESISTER_H

#include <stdint.h>
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
#define     __I     volatile const       /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     NULL    ((void *)0)          /*!< Define NULL pointer                             */


typedef struct 
{
    /*******************************************************************************
    *                             CAN Module Configuration Register (MCR)
    ******************************************************************************/
    union{
        __IO uint32_t MCR_Register;
        struct{
            __IO uint32_t MAXMB             :7; /*Number of The Last Message Buffer*/
            __IO uint32_t reserved_0        :1;
            __IO uint32_t IDAM              :2; /*ID Acceptance Mode*/
            __IO uint32_t reserved_1        :1;
            __IO uint32_t FDEN              :1; /*CAN FD operation enable*/
            __IO uint32_t AEN               :1; /*Abort Enable*/
            __IO uint32_t LPRIOEN           :1; /*Local Priority Enable*/
            __IO uint32_t PNET_EN           :1; /*Pretended Networking Enable*/
            __IO uint32_t DMA               :1; /*DMA Enable*/
            __IO uint32_t IRMQ              :1; /*Individual Rx Masking and Queue Enable*/
            __IO uint32_t SRXDIS            :1; /*Self Reception Disable*/
            __IO uint32_t reserved_2        :2;
            __IO uint32_t LPMACK            :1; /*Low Power Mode Acknowledge*/
            __IO uint32_t WRNEN             :1; /*Warning Interrupt Enable*/
            __IO uint32_t reserved_3        :1;
            __IO uint32_t SUPV              :1; /*Supervisor Enable*/
            __IO uint32_t FRZACK            :1; /*Freeze Mode Acknowledge*/
            __IO uint32_t SOFTRST           :1; /*Soft Reset*/
            __IO uint32_t reserved_4        :1;
            __IO uint32_t NOTRDY            :1; /*Module Not Ready*/
            __IO uint32_t HALT              :1; /*Halt FlexCAN*/
            __IO uint32_t RFEN              :1; /*Rx FIFO Enable*/
            __IO uint32_t FRZ               :1; /*Freeze FlexCAN*/
            __IO uint32_t MDIS              :1; /*Module Disable*/
        }MCR_Bits;
    };

    /*******************************************************************************
    *                             CAN Control 1 Register (CTRL1)
    ******************************************************************************/
    union{
        __IO uint32_t CTRL1_Register;
        struct{
            __IO uint32_t PROPSEG           :3; /*Propagation Segment*/
            __IO uint32_t LOM               :1; /*Listen-Only Mode*/
            __IO uint32_t LBUF              :1; /*Last Sample Point*/
            __IO uint32_t TSYN              :1; /*Timer Sync*/
            __IO uint32_t BOFFREC           :1; /*Bus Off Recovery*/
            __IO uint32_t SMP               :1; /*Sampling Mode*/
                uint32_t                    :2;  
            __IO uint32_t RWRNMSK           :1; /*Rx Warning Interrupt Mask*/
            __IO uint32_t TWRNMSK           :1; /*Tx Warning Interrupt Mask*/
            __IO uint32_t LPB               :1; /*Loop Back Mode*/
            __IO uint32_t CLKSRC            :1; /*CAN Engine Clock Source*/
            __IO uint32_t ERRMSK            :1; /*Error Interrupt Mask*/
            __IO uint32_t BOFFMSK           :1; /*Bus Off Interrupt Mask*/
            __IO uint32_t PSEG2             :3; /*Phase Segment 2*/
            __IO uint32_t PSEG1             :3; /*Phase Segment 1*/
            __IO uint32_t RJW               :2; /*Resync Jump Width*/
            __IO uint32_t PRESDIV           :8; /*Prescaler Division Factor*/
        }CTRL1_Bits;
    };

    /*******************************************************************************
    *                             CAN Free Running Timer (TIMER)
    ******************************************************************************/
    __IO uint32_t TIMER;

uint32_t RESERVED_0;
    /*******************************************************************************
    *                   CAN Rx Mailboxes Global Mask register (RXMGMASK)
    ******************************************************************************/    
    __IO uint32_t RXMGMASK;

    /*******************************************************************************
    *                           CAN Rx 14 Mask register (RX14MASK)
    ******************************************************************************/
   __IO uint32_t RX14MASK;

    /*******************************************************************************
    *                           CAN Rx 15 Mask register (RX15MASK)
    ******************************************************************************/
    __IO uint32_t RX15MASK;

    /*******************************************************************************
    *                           CAN Error Counter Register (ECR)
    ******************************************************************************/
    union{
        __IO uint32_t ECR_Register;
        struct{
            __IO uint32_t TEC               :8; /*Transmit Error Counter*/
            __IO uint32_t REC               :8; /*Receive Error Counter*/
            __I  uint32_t TXERRCNT_FAST     :8; /*Transmit Error Counter for fast bits*/
            __I  uint32_t RXERRCNT_FAST     :8; /*Receive Error Counter for fast bits*/
        }ECR_Bits;
    };
    
    /*******************************************************************************
    *                           CAN Error and Status 1 register (ESR1)
    ******************************************************************************/   
    __IO uint32_t ESR1;

uint32_t RESERVED_1;
    /*******************************************************************************
    *                           CAN Interrupt Masks 1 register (IMASK1)
    ******************************************************************************/
    __IO uint32_t IMASK1;

uint32_t RESERVED_2;
    /*******************************************************************************
    *                           CAN Interrupt Flags 1 register (IFLAG1)
    ******************************************************************************/
    __IO uint32_t IFLAG1;
    /*******************************************************************************
    *                           CAN Control 2 register (CTRL2)
    ******************************************************************************/ 
    //__IO uint32_t CTRL2;
    union{
        __IO uint32_t CTRL2_Register;
        struct{
            uint32_t :11;
            __IO uint32_t EDFLTDIS      :1; /*Edge Filter Disable*/
            __IO uint32_t ISOCANFDEN    :1; /*ISO CAN FD Enable*/
            uint32_t :1;
            __IO uint32_t PREXCEN       :1; /*Protocol Exception Enable*/
            __IO uint32_t TIMER_SRC     :1; /*Timer Source*/
            __IO uint32_t EACEN         :1; /*Entire Frame Arbitration Field Comparison Enable For Rx Mailboxes*/
            __IO uint32_t RRS           :1; /*Remote Request Storing*/
            __IO uint32_t MRP           :1; /*Mailboxes Reception Priority*/
            __IO uint32_t TASD          :5; /*Tx Arbitration Start Delay*/   
            __IO uint32_t RFFN          :4; /*Number Of Rx FIFO Filters*/ 
            uint32_t :2;
            __IO uint32_t BOFFDONEMSK   :1; /*Bus Off Done Interrupt Mask*/
            __IO uint32_t ERRMSK_FAST   :1; /*Error Interrupt Mask for errors detected in the data phase of fast CAN FD frames*/
        }CTRL2_Bits;
    };
    /*******************************************************************************
    *                           CAN Error and Status 2 register (ESR2)
    ******************************************************************************/ 
    __IO uint32_t ESR2;

uint8_t RESERVED_3[8];
    /*******************************************************************************
    *                           CAN CRC register (CRCR)
    ******************************************************************************/
    __IO uint32_t CRCR; 
    /*******************************************************************************
    *                           CAN Rx FIFO Global Mask register (RXFGMASK)
    ******************************************************************************/ 
    __IO uint32_t RXFGMASK;
    /*******************************************************************************
    *                           Rx FIFO Information register (RXFIR)
    ******************************************************************************/
    __IO uint32_t RXFIR;   
    /*******************************************************************************
    *                           Rx CAN Bit Timing register (CBT)
    ******************************************************************************/
    __IO uint32_t CBT;

uint8_t RESERVED_4[44];
    /*******************************************************************************
    *                           Embedded RAM Address register (RAMn)
    ******************************************************************************/
    union{
        __IO uint32_t RAMn[128];

        struct{
            __IO uint32_t TIMESTAMP  : 16;			/* Note that if you add from "TIMESTAMP" to "PRIO" */
            __IO uint32_t DLC        : 4;			/* you get 64 bits = 8 bytes for header */
            __IO uint32_t RTR        : 1;			/* 16 + 4 + 1 + ... + 3 = 64 */
            __IO uint32_t IDE        : 1;
            __IO uint32_t SRR        : 1;
                  uint32_t            : 1;
            __IO uint32_t CODE       : 4;
                  uint32_t            : 1;
            __IO uint32_t ESI        : 1;
            __IO uint32_t BRS        : 1;
            __IO uint32_t EDL        : 1;
                  uint32_t            : 18;
            __IO uint32_t STD_ID     : 11;
            __IO uint32_t PRIO       : 3;
            __IO uint8_t payload[8];				/* 8 bytes (2 words) for payload */
        } Classic_MessageBuffer[32];				/* 32 MBs available */
    };


uint8_t RESERVED_5[1536];
    /*******************************************************************************
    *                           Rx Individual Mask registers (RXIMR0 - RXIMR31)
    ******************************************************************************/ 
    __IO uint32_t RXIMR[32];

}CAN_Type;

 /** Number of instances of the CAN module. */
#define CAN_INSTANCE_COUNT                       (3u)

#define CAN0_BASE_ADDR          (0x40024000u)
#define CAN1_BASE_ADDR          (0x40025000u)
#define CAN2_BASE_ADDR          (0x4002B000u)

#define CAN0                    ((CAN_Type *)CAN0_BASE_ADDR)
#define CAN1                    ((CAN_Type *)CAN1_BASE_ADDR)
#define CAN2                    ((CAN_Type *)CAN2_BASE_ADDR)

#define CAN_BASE_ADDRS                           { CAN0_BASE, CAN1_BASE, CAN2_BASE }
/** Array initializer of CAN peripheral base pointers */
#define CAN_BASE_PTRS                            { CAN0, CAN1, CAN2 }
 /** Number of interrupt vector arrays for the CAN module. */
#define CAN_IRQS_ARR_COUNT                       (7u)
 /** Number of interrupt channels for the Rx_Warning type of CAN module. */
#define CAN_Rx_Warning_IRQS_CH_COUNT             (1u)
 /** Number of interrupt channels for the Tx_Warning type of CAN module. */
#define CAN_Tx_Warning_IRQS_CH_COUNT             (1u)
 /** Number of interrupt channels for the Wake_Up type of CAN module. */
#define CAN_Wake_Up_IRQS_CH_COUNT                (1u)
 /** Number of interrupt channels for the Error type of CAN module. */
#define CAN_Error_IRQS_CH_COUNT                  (1u)
 /** Number of interrupt channels for the Bus_Off type of CAN module. */
#define CAN_Bus_Off_IRQS_CH_COUNT                (1u)
 /** Number of interrupt channels for the ORed_0_15_MB type of CAN module. */
#define CAN_ORed_0_15_MB_IRQS_CH_COUNT           (1u)
 /** Number of interrupt channels for the ORed_16_31_MB type of CAN module. */
#define CAN_ORed_16_31_MB_IRQS_CH_COUNT          (1u)
/** Interrupt vectors for the CAN peripheral type */
#define CAN_Rx_Warning_IRQS                      { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn }
#define CAN_Tx_Warning_IRQS                      { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn }
#define CAN_Wake_Up_IRQS                         { CAN0_Wake_Up_IRQn, NotAvail_IRQn, NotAvail_IRQn }
#define CAN_Error_IRQS                           { CAN0_Error_IRQn, CAN1_Error_IRQn, CAN2_Error_IRQn }
#define CAN_Bus_Off_IRQS                         { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn }
#define CAN_ORed_0_15_MB_IRQS                    { CAN0_ORed_0_15_MB_IRQn, CAN1_ORed_0_15_MB_IRQn, CAN2_ORed_0_15_MB_IRQn }
#define CAN_ORed_16_31_MB_IRQS                   { CAN0_ORed_16_31_MB_IRQn, NotAvail_IRQn, NotAvail_IRQn }

#endif/**/

