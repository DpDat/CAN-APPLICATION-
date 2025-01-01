#ifndef CAN_H
#define CAN_H

#include <stdbool.h>
#include "Can_resgister.h"
#include "status.h"
#include "nvic.h"


/***************************************************************************************************************************************************
 *                              Definitions
 **************************************************************************************************************************************************/
 
#define FLEXCAN_ALL_INT                          (0x3B0006U)    /*!< Masks for wakeup, error, bus off*/
                                                                        /*! interrupts*/
#define CAN_RXMGMASK_MG_MASK                     (0xFFFFFFFFu)
#define CAN_RX14MASK_RX14M_MASK                  (0xFFFFFFFFu)
#define CAN_RX15MASK_RX15M_MASK                  (0xFFFFFFFFu)
#define CAN_IMASK1_BUF31TO0M_MASK                (0xFFFFFFFFu)
#define CAN_RXFGMASK_FGM_MASK                    0xFFFFFFFFu
#define CAN_RXIMR_MI_MASK                        0xFFFFFFFFu

#define CAN_ID_EXT_MASK                          0x3FFFFu
#define CAN_ID_EXT_SHIFT                         0
#define CAN_ID_EXT_WIDTH                         18

#define CAN_ID_STD_MASK                          0x1FFC0000u
#define CAN_ID_STD_SHIFT                         18
#define CAN_ID_STD_WIDTH                         11

#define FLEXCAN_MB_HANDLE_RXFIFO    0U

/* CAN bit timing values */
#define FLEXCAN_NUM_TQ_MIN     8U
#define FLEXCAN_NUM_TQ_MAX    26U
#define FLEXCAN_PRESDIV_MAX  256U
#define FLEXCAN_PSEG1_MAX      8U
#define FLEXCAN_PSEG2_MIN      1U
#define FLEXCAN_PSEG2_MAX      8U
#define FLEXCAN_PROPSEG_MAX    8U
#define FLEXCAN_TSEG1_MIN      2U
#define FLEXCAN_TSEG1_MAX     17U
#define FLEXCAN_TSEG2_MIN      2U
#define FLEXCAN_TSEG2_MAX      9U
#define FLEXCAN_RJW_MAX        3U


/* CAN module features */

/* @brief Maximum number of Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS_MAX_COUNT       (2U)
/* @brief Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS                 { CAN_ORed_0_15_MB_IRQS, \
                                              CAN_ORed_16_31_MB_IRQS }
/* @brief Frames available in Rx FIFO flag shift */
#define FEATURE_CAN_RXFIFO_FRAME_AVAILABLE  (5U)
/* @brief Rx FIFO warning flag shift */
#define FEATURE_CAN_RXFIFO_WARNING          (6U)
/* @brief Rx FIFO overflow flag shift */
#define FEATURE_CAN_RXFIFO_OVERFLOW         (7U)
/* @brief Has Flexible Data Rate for CAN0 */
#define FEATURE_CAN0_HAS_FD                 (1)
/* @brief Has Flexible Data Rate for CAN1 */
#define FEATURE_CAN1_HAS_FD                 (0)
/* @brief Has Flexible Data Rate for CAN2 */
#define FEATURE_CAN2_HAS_FD                 (0)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN0 */
#define FEATURE_CAN0_MAX_MB_NUM             (32U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN1 */
#define FEATURE_CAN1_MAX_MB_NUM             (16U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN2 */
#define FEATURE_CAN2_MAX_MB_NUM             (16U)
/* @brief Has PE clock source select (bit field CAN_CTRL1[CLKSRC]). */
#define FEATURE_CAN_HAS_PE_CLKSRC_SELECT    (1)
/* @brief Has DMA enable (bit field MCR[DMA]). */
#define FEATURE_CAN_HAS_DMA_ENABLE          (1)
/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM              (32U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM_ARRAY        { FEATURE_CAN0_MAX_MB_NUM, \
                                              FEATURE_CAN1_MAX_MB_NUM, \
                                              FEATURE_CAN2_MAX_MB_NUM }


/**************************************************************************************************************************************************
 *                                  ENUM
 **************************************************************************************************************************************************/

/*! @brief The type of the event which occurred when the callback was invoked.
 * Implements : flexcan_event_type_t_Class
 */
typedef enum {
    FLEXCAN_EVENT_RX_COMPLETE,     /*!< A frame was received in the configured Rx MB. */
    FLEXCAN_EVENT_RXFIFO_COMPLETE, /*!< A frame was received in the Rx FIFO. */
    FLEXCAN_EVENT_RXFIFO_WARNING,  /*!< Rx FIFO is almost full (5 frames). */
    FLEXCAN_EVENT_RXFIFO_OVERFLOW, /*!< Rx FIFO is full (incoming message was lost). */
    FLEXCAN_EVENT_TX_COMPLETE,     /*!< A frame was sent from the configured Tx MB. */
//#if FEATURE_CAN_HAS_WAKE_UP_IRQ
    FLEXCAN_EVENT_WAKEUP_TIMEOUT,  /*!< An wake up event occurred due to timeout. */
    FLEXCAN_EVENT_WAKEUP_MATCH,    /*!< An wake up event occurred due to matching. */
    FLEXCAN_EVENT_SELF_WAKEUP,     /*!< A self wake up event occurred. */
//#endif /* FEATURE_CAN_HAS_WAKE_UP_IRQ */
//#if FEATURE_CAN_HAS_DMA_ENABLE
	FLEXCAN_EVENT_DMA_COMPLETE,	  /*!< A complete transfer occurred on DMA */
	FLEXCAN_EVENT_DMA_ERROR,	  /*!< A DMA transfer fail, because of a DMA channel error */
//#endif /* FEATURE_CAN_HAS_DMA_ENABLE */
    FLEXCAN_EVENT_ERROR
} flexcan_event_type_t;

/*! @brief FlexCAN Rx FIFO filters number
 * Implements : flexcan_rx_fifo_id_filter_num_t_Class
 */
typedef enum {
    FLEXCAN_RX_FIFO_ID_FILTERS_8   = 0x0,         /*!<   8 Rx FIFO Filters. @internal gui name="8 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_16  = 0x1,         /*!<  16 Rx FIFO Filters. @internal gui name="16 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_24  = 0x2,         /*!<  24 Rx FIFO Filters. @internal gui name="24 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_32  = 0x3,         /*!<  32 Rx FIFO Filters. @internal gui name="32 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_40  = 0x4,         /*!<  40 Rx FIFO Filters. @internal gui name="40 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_48  = 0x5,         /*!<  48 Rx FIFO Filters. @internal gui name="48 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_56  = 0x6,         /*!<  56 Rx FIFO Filters. @internal gui name="56 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_64  = 0x7,         /*!<  64 Rx FIFO Filters. @internal gui name="64 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_72  = 0x8,         /*!<  72 Rx FIFO Filters. @internal gui name="72 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_80  = 0x9,         /*!<  80 Rx FIFO Filters. @internal gui name="80 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_88  = 0xA,         /*!<  88 Rx FIFO Filters. @internal gui name="88 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_96  = 0xB,         /*!<  96 Rx FIFO Filters. @internal gui name="96 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_104 = 0xC,         /*!< 104 Rx FIFO Filters. @internal gui name="104 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_112 = 0xD,         /*!< 112 Rx FIFO Filters. @internal gui name="112 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_120 = 0xE,         /*!< 120 Rx FIFO Filters. @internal gui name="120 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_128 = 0xF          /*!< 128 Rx FIFO Filters. @internal gui name="128 Rx FIFO Filters" */
} flexcan_rx_fifo_id_filter_num_t;


/*! @brief FlexCAN operation modes
 * Implements : flexcan_operation_modes_t_Class
 */
typedef enum {
    FLEXCAN_NORMAL_MODE,        /*!< Normal mode or user mode @internal gui name="Normal" */
    FLEXCAN_LISTEN_ONLY_MODE,   /*!< Listen-only mode @internal gui name="Listen-only" */
    FLEXCAN_LOOPBACK_MODE,      /*!< Loop-back mode @internal gui name="Loop back" */
    FLEXCAN_FREEZE_MODE,        /*!< Freeze mode @internal gui name="Freeze" */
    FLEXCAN_DISABLE_MODE        /*!< Module disable mode @internal gui name="Disabled" */
} flexcan_operation_modes_t;

/*! @brief FlexCAN payload sizes
 * Implements : flexcan_fd_payload_size_t_Class
 */
typedef enum {
    FLEXCAN_PAYLOAD_SIZE_8 = 0,  /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_16 ,    /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_32 ,    /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_64      /*!< FlexCAN message buffer payload size in bytes*/
} flexcan_fd_payload_size_t;


/*! @brief FlexCAN PE clock sources
 * Implements : flexcan_clk_source_t_Class
 */
typedef enum {
    FLEXCAN_CLK_SOURCE_OSC    = 0U,  /*!< The CAN engine clock source is the oscillator clock. */
    FLEXCAN_CLK_SOURCE_PERIPH = 1U   /*!< The CAN engine clock source is the peripheral clock. */
} flexcan_clk_source_t;


/*! @brief The type of the RxFIFO transfer (interrupts/DMA).
 * Implements : flexcan_rxfifo_transfer_type_t_Class
 */
typedef enum {
    FLEXCAN_RXFIFO_USING_INTERRUPTS,    /*!< Use interrupts for RxFIFO. */
//#if FEATURE_CAN_HAS_DMA_ENABLE
    FLEXCAN_RXFIFO_USING_DMA            /*!< Use DMA for RxFIFO. */
//#endif
} flexcan_rxfifo_transfer_type_t;


/*! @brief The state of a given MB (idle/Rx busy/Tx busy).
 * Implements : flexcan_mb_state_t_Class
 */
typedef enum {
    FLEXCAN_MB_IDLE,      /*!< The MB is not used by any transfer. */
    FLEXCAN_MB_RX_BUSY,   /*!< The MB is used for a reception. */
    FLEXCAN_MB_TX_BUSY,   /*!< The MB is used for a transmission. */
//#if FEATURE_CAN_HAS_DMA_ENABLE
	FLEXCAN_MB_DMA_ERROR /*!< The MB is used as DMA source and fail to transfer */
//#endif
} flexcan_mb_state_t;


typedef enum {
    MB0,
    MB1,
    MB2,
    MB3,
    MB4,
    MB5,
    MB6,
    MB7,
    MB8,
    MB9,
    MB10,
    MB11,
    MB12,
    MB13,
    MB14,
    MB15,
} flexcan_mailbox_t;

/**********************************************************************************************************************************************************
 *                                  Struct 
 **********************************************************************************************************************************************************/
/*!
* @brief Structure for a CAN frame. Header + Payload.
*/
typedef struct
{
	uint32_t ID;
	uint8_t payload[8];
} standard_frame_t;

/*! @brief FlexCAN message buffer structure
 * Implements : flexcan_msgbuff_t_Class
 */
typedef struct {
    uint32_t cs;                        /*!< Code and Status*/
    uint32_t msgId;                     /*!< Message Buffer ID*/
    uint8_t data[64];                   /*!< Data bytes of the FlexCAN message*/
    uint8_t dataLen;                    /*!< Length of data in bytes */
} flexcan_msgbuff_t;



/*! @brief FlexCAN bitrate related structures
 * Implements : flexcan_time_segment_t_Class
 */
typedef struct {
    uint32_t propSeg;         /*!< Propagation segment*/
    uint32_t phaseSeg1;       /*!< Phase segment 1*/
    uint32_t phaseSeg2;       /*!< Phase segment 2*/
    uint32_t preDivider;      /*!< Clock prescaler division factor*/
    uint32_t rJumpwidth;      /*!< Resync jump width*/
} flexcan_time_segment_t;


/*! @brief FlexCAN configuration
 * @internal gui name="Common configuration" id="flexcanCfg"
 * Implements : flexcan_user_config_t_Class
 */
typedef struct {
    uint32_t max_num_mb;                            /*!< The maximum number of Message Buffers
                                                         @internal gui name="Maximum number of message buffers" id="max_num_mb" */
    flexcan_rx_fifo_id_filter_num_t num_id_filters; /*!< The number of RX FIFO ID filters needed
                                                         @internal gui name="Number of RX FIFO ID filters" id="num_id_filters" */
    bool is_rx_fifo_needed;                         /*!< 1 if needed; 0 if not. This controls whether the Rx FIFO feature is enabled or not.
                                                         @internal gui name="Use rx fifo" id="is_rx_fifo_needed" */
    flexcan_operation_modes_t flexcanMode;          /*!< User configurable FlexCAN operation modes.
                                                         @internal gui name="Flexcan Operation Mode" id="flexcanMode"*/

    flexcan_fd_payload_size_t payload;              /*!< The payload size of the mailboxes specified in bytes. */
    bool fd_enable;                                 /*!< Enable/Disable the Flexible Data Rate feature. */


    flexcan_clk_source_t pe_clock;                  /*!< The clock source of the CAN Protocol Engine (PE). */

    flexcan_time_segment_t bitrate;                 /*!< The bitrate used for standard frames or for the arbitration phase of FD frames. */

    flexcan_time_segment_t bitrate_cbt;             /*!< The bitrate used for the data phase of FD frames. */

    flexcan_rxfifo_transfer_type_t transfer_type;   /*!< Specifies if the Rx FIFO uses interrupts or DMA. */

    uint8_t rxFifoDMAChannel;                       /*!< Specifies the DMA channel number to be used for DMA transfers. */

} flexcan_user_config_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for CAN instances. */
static CAN_Type * const g_flexcanBase[] = CAN_BASE_PTRS;

/**********************************************************************************************************************************************************
 *                                  Function Prototypes
 **********************************************************************************************************************************************************/
void FLEXCAN_DRV_GetDefaultConfig(flexcan_user_config_t *config);
status_t FlexCAN_Config_RxMB (CAN_Type* base, uint32_t msgId, uint8_t mbIdx);
status_t FlexCAN_Config_TxMB (CAN_Type* base, uint8_t mbIdx );
status_t FLEXCAN_DRV_Init(CAN_Type* base, const flexcan_user_config_t *data);
status_t FlexCAN_receive_frame (CAN_Type* base, standard_frame_t* frame, uint8_t mbIdx);
status_t FlexCAN_transmit_frame (CAN_Type* base, standard_frame_t* frame, uint8_t mbIdx);
#endif  /*CAN_H_*/