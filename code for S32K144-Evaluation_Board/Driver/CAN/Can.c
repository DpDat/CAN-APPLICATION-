#include"Can.h"



/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_Enable
 * Description   : Enable FlexCAN module.
 * This function will enable FlexCAN module.
 *
 *END**************************************************************************/
void FLEXCAN_Enable(CAN_Type * base)
{
    /* Check for low power mode */
    if((base->MCR_Bits.LPMACK) == 1U)
    {
        /* Enable clock */
        base->MCR_Bits.MDIS = 0;
        base->MCR_Bits.FRZ = 0;
        base->MCR_Bits.HALT = 0;
        /* Wait until enabled */
        while (base->MCR_Bits.NOTRDY != 0U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_IsEnabled
 * Description   : Checks if the FlexCAN is enabled.
 * This function will return true if enabled; false if disabled
 *
 *END**************************************************************************/
static inline bool FLEXCAN_IsEnabled(const CAN_Type * base)
{
    return ((base->MCR_Bits.MDIS != 0U) ? false : true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_Disable
 * Description   : Disable FlexCAN module.
 * This function will disable FlexCAN module.
 *
 *END**************************************************************************/
void FLEXCAN_Disable(CAN_Type * base)
{
    /* To access the memory mapped registers */
    /* Entre disable mode (hard reset). */
    if(base->MCR_Bits.MDIS == 0U)
    {
        /* Clock disable (module) */
        base->MCR_Bits.MDIS = 1;

        /* Wait until disable mode acknowledged */
        while (base->MCR_Bits.LPMACK == 0U);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_EnterFreezeMode
 * Description   : Enter the freeze mode.
 *
 *END**************************************************************************/
void FLEXCAN_EnterFreezeMode(CAN_Type * base)
{
    base->MCR_Bits.HALT = 1;/* Request freeze mode entry */
    base->MCR_Bits.FRZ = 1; /* Enter in freeze mode */   
    /* Block for freeze mode entry */
    while(base->MCR_Bits.FRZACK != 1u);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_ExitFreezeMode
 * Description   : Exit of freeze mode.
 *
 *END**************************************************************************/
void FLEXCAN_ExitFreezeMode(CAN_Type * base)
{
    base->MCR_Bits.HALT = 0; /* Request leave freeze mode */
    base->MCR_Bits.FRZ = 0;  /* Exit from freeze mode */

    /* Wait till exit freeze mode */
    while (base->MCR_Bits.FRZACK != 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_SelectClock
 * Description   : Selects the clock source for FlexCAN.
 *
 *END**************************************************************************/
static inline void FLEXCAN_SelectClock(CAN_Type * base, flexcan_clk_source_t clk)
{
    base->CTRL1_Bits.CLKSRC = clk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_SetSelfReception
 * Description   : Enables/Disables the Self Reception feature.
 *
 *END**************************************************************************/
static inline void FLEXCAN_SetSelfReception(CAN_Type * base, bool enable)
{
    base->MCR_Bits.SRXDIS = enable;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_GetMaxMbNum
 * Description   : Computes the maximum RAM size occupied by MBs.
 *
 *END**************************************************************************/
uint32_t FLEXCAN_GetMaxMbNum(const CAN_Type * base)
{
    uint32_t i, ret = 0;
    static CAN_Type * const flexcanBase[] = CAN_BASE_PTRS;
    static const uint32_t maxMbNum[] = FEATURE_CAN_MAX_MB_NUM_ARRAY;

    for (i = 0; i < CAN_INSTANCE_COUNT; i++)
    {
        if (base == flexcanBase[i])
        {
            ret = maxMbNum[i];
        }
    }

    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_ClearRAM
 * Description   : Clears FlexCAN memory positions that require initialization.
 *
 *END**************************************************************************/
static void FLEXCAN_ClearRAM(CAN_Type * base)
{
    uint32_t databyte;
    uint32_t RAM_size = FLEXCAN_GetMaxMbNum(base) * 4U;
    uint32_t RXIMR_size = FLEXCAN_GetMaxMbNum(base);
    //volatile uint32_t *RAM = base->RAMn;

    /* Clear MB region */
    for (databyte = 0; databyte < RAM_size; databyte++) {
        base->RAMn[databyte] = 0x0;
    }

    //RAM = base->RXIMR;

    /* Clear RXIMR region */
    for (databyte = 0; databyte < RXIMR_size; databyte++) {
        base->RXIMR[databyte] = 0x0;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_Init
 * Description   : Initialize FlexCAN module.
 * This function will reset FlexCAN module, set maximum number of message
 * buffers, initialize all message buffers as inactive, enable RX FIFO
 * if needed, mask all mask bits, and disable all MB interrupts.
 *
 *END**************************************************************************/
void FLEXCAN_Init(CAN_Type * base)
{
    /* Reset the FLEXCAN */
    base->MCR_Bits.SOFTRST = 1;

    /* Wait for reset cycle to complete */
    while(base->MCR_Bits.SOFTRST != 0u);

    /* Clear FlexCAN memory */
    FLEXCAN_ClearRAM(base);

    /* Rx global mask*/
    (base->RXMGMASK) = (uint32_t)(CAN_RXMGMASK_MG_MASK);

    /* Rx reg 14 mask*/
    (base->RX14MASK) =  (uint32_t)(CAN_RX14MASK_RX14M_MASK);

    /* Rx reg 15 mask*/
    (base->RX15MASK) = (uint32_t)(CAN_RX15MASK_RX15M_MASK);

    /* Disable all MB interrupts */
    (base->IMASK1) = 0x0;
    /* Clear all MB interrupt flags */
    (base->IFLAG1) = CAN_IMASK1_BUF31TO0M_MASK;

    /* Clear all error interrupt flags */
    (base->ESR1) = FLEXCAN_ALL_INT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_IsRxFifoEnabled
 * Description   : Checks if Rx FIFO is enabled.
 * RxFifo status (true = enabled / false = disabled).
 *
 *END**************************************************************************/
static inline bool FLEXCAN_IsRxFifoEnabled(const CAN_Type * base)
{
    return (base->MCR_Bits.RFEN != 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_SetRxFifoDMA
 * Description   : Enables/Disables the DMA support for RxFIFO.
 *
 *END**************************************************************************/
static inline void FLEXCAN_SetRxFifoDMA(CAN_Type * base, bool enable)
{
    base->MCR_Bits.DMA = enable;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_IsFDEnabled
 * Description   : Checks if the Flexible Data rate feature is enabled.
 * true if enabled; false if disabled.
 *
 *END**************************************************************************/
static inline bool FLEXCAN_IsFDEnabled(const CAN_Type * base)
{
    return (base->MCR_Bits.FDEN != 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_EnableRxFifo
 * Description   : Enable Rx FIFO feature.
 * This function will enable the Rx FIFO feature.
 *
 *END**************************************************************************/
status_t FLEXCAN_EnableRxFifo(CAN_Type * base, uint32_t numOfFilters)
{
    uint32_t i;
    uint16_t noOfMbx= (uint16_t)FLEXCAN_GetMaxMbNum(base);
    status_t stat = STATUS_SUCCESS;


    /* RxFIFO cannot be enabled if FD is enabled */
    if (FLEXCAN_IsFDEnabled(base))
    {
        stat = STATUS_ERROR;
    }

    if (stat == STATUS_SUCCESS)
    {
        /* Enable RX FIFO */
        base->MCR_Bits.RFEN =1U;
        /* Set the number of the RX FIFO filters needed */
        base->CTRL2_Bits.RFFN = numOfFilters;
        /* RX FIFO global mask, take in consideration all filter fields*/
        (base->RXFGMASK) = CAN_RXFGMASK_FGM_MASK;

        for (i = 0; i < noOfMbx; i++)
        {
            /* RX individual mask */
            base->RXIMR[i] = (CAN_RXIMR_MI_MASK << CAN_ID_EXT_SHIFT) & (CAN_ID_STD_MASK | CAN_ID_EXT_MASK);
        }
    }

    return stat;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_SetTimeSegments
 * Description   : Sets the FlexCAN time segments for setting up bit rate.
 *
 *END**************************************************************************/
static inline void FLEXCAN_SetTimeSegments(CAN_Type * base, const flexcan_time_segment_t *timeSeg)
{
    //DEV_ASSERT(timeSeg != NULL);

    base->CTRL1_Bits.PROPSEG = timeSeg->propSeg;
    base->CTRL1_Bits.PSEG1 = timeSeg->phaseSeg1;
    base->CTRL1_Bits.PSEG2 = timeSeg->phaseSeg2;
    base->CTRL1_Bits.PRESDIV = timeSeg->preDivider;
    base->CTRL1_Bits.RJW = timeSeg->rJumpwidth;

}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_SetOperationMode
 * Description   : Enable a FlexCAN operation mode.
 * This function will enable one of the modes listed in flexcan_operation_modes_t.
 *
 *END**************************************************************************/
void FLEXCAN_SetOperationMode(
    CAN_Type * base,
    flexcan_operation_modes_t mode)
{

	switch (mode)
	{
	case FLEXCAN_FREEZE_MODE:
        /* Debug mode, Halt and Freeze*/
        FLEXCAN_EnterFreezeMode(base);
	break;
	case FLEXCAN_DISABLE_MODE:
		/* Debug mode, Halt and Freeze */
		base->MCR_Bits.MDIS = 1;
	break;
	case FLEXCAN_NORMAL_MODE:
        base->MCR_Bits.SUPV = 0;
        base->CTRL1_Bits.LOM = 0;
        base->CTRL1_Bits.LPB = 0;
    break;
	case FLEXCAN_LISTEN_ONLY_MODE:
        base->CTRL1_Bits.LOM = 1;
    break;
	case FLEXCAN_LOOPBACK_MODE:
        base->CTRL1_Bits.LPB = 1;
        base->CTRL1_Bits.LOM = 0;
        /* Enable Self Reception */
        FLEXCAN_SetSelfReception(base, true);
    break;
	default :
		 /* Should not get here */
	break;
	}
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Init
 * Description   : Initialize FlexCAN driver.
 * This function will select a source clock, reset FlexCAN module, set maximum
 * number of message buffers, initialize all message buffers as inactive, enable
 * RX FIFO if needed, mask all mask bits, disable all MB interrupts, enable
 * FlexCAN normal mode, and enable all the error interrupts if needed.
 *
 * Implements    : FLEXCAN_DRV_Init_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_Init(
   CAN_Type* base,
   const flexcan_user_config_t *data)
{

    status_t result;
    flexcan_time_segment_t bitrate;
    //status_t osifStat;
    uint32_t i, j;

    if(FLEXCAN_IsEnabled(base))
    {
        /* To enter Disable Mode requires FreezMode first */
        FLEXCAN_EnterFreezeMode(base);
        FLEXCAN_Disable(base);
    }

    /* Select a source clock for the FlexCAN engine */
    FLEXCAN_SelectClock(base, data->pe_clock);

    /* Enable the CAN clock */
    FLEXCAN_Enable(base);

    FLEXCAN_EnterFreezeMode(base);

    /* Initialize FLEXCAN device */
    FLEXCAN_Init(base);

    /* Disable the self reception feature if FlexCAN is not in loopback mode. */
    if (data->flexcanMode != FLEXCAN_LOOPBACK_MODE)
    {
        FLEXCAN_SetSelfReception(base, false);
    }

    /* Enable RxFIFO feature, if requested. This might fail if the FD mode is
     * enabled. */
    if (data->is_rx_fifo_needed)
    {
        result = FLEXCAN_EnableRxFifo(base, (uint32_t)data->num_id_filters);
        if (result != STATUS_SUCCESS)
        {
            return result;
        }
    }

    /* Enable DMA support for RxFIFO transfer, if requested. */
    if (data->transfer_type == FLEXCAN_RXFIFO_USING_DMA)
    {
        if (FLEXCAN_IsRxFifoEnabled(base))
        {
            FLEXCAN_SetRxFifoDMA(base, true);
        }
        else
        {
            return STATUS_ERROR;
        }
    }
    if (data->transfer_type == FLEXCAN_RXFIFO_USING_INTERRUPTS)
    {
    	FLEXCAN_SetRxFifoDMA(base, false);
    }

// #if FEATURE_CAN_HAS_FD
//     /* Set payload size. */
//     FLEXCAN_SetPayloadSize(base, data->payload);
// #endif

    // result = FLEXCAN_SetMaxMsgBuffNum(base, data->max_num_mb);
    // if (result != STATUS_SUCCESS)
    // {
    //     return result;
    // }

// #if FEATURE_CAN_HAS_FD
//     /* Set bit rate. */
//     if (FLEXCAN_IsFDEnabled(base))
//     {
//         bitrate = data->bitrate;
//         FLEXCAN_SetExtendedTimeSegments(base, &bitrate);
//         bitrate = data->bitrate_cbt;
//         FLEXCAN_SetFDTimeSegments(base, &bitrate);
//     }
//     else
// #endif
    {
        bitrate = data->bitrate;
        FLEXCAN_SetTimeSegments(base, &bitrate);
    }

    /* Select mode */
    FLEXCAN_SetOperationMode(base, data->flexcanMode);

    if (data->flexcanMode != FLEXCAN_FREEZE_MODE)
    {
    	FLEXCAN_ExitFreezeMode(base);
    }


    /* Save runtime structure pointers so irq handler can point to the correct state structure */
    //g_flexcanStatePtr[instance] = state;

    return (STATUS_SUCCESS);
}



/*!
* @brief Setup a message buffer for reception of a specific ID
*
* @param [uint32_t id] Standard ID
*
* @return Success If the ID was installed correctly
*/
status_t FlexCAN_Config_RxMB (CAN_Type* base, uint32_t id, uint8_t mbIdx )
{
    FLEXCAN_EnterFreezeMode(base);
    /*Config interrupt for MB*/
    base->IMASK1 |= (1 << mbIdx);

    /* An "All-care" bits mask 0x7FF is used for the 11 bits of CAN Classic IDs,
     * Extended and Standard IDs are installed in the same register, but the Standard
     * ID section correspond to the 11 most significant bits of the whole 29-bit ID section,
     * thus, requiring a 18 left shift. Refer to "Message Buffer Structure" in RM for further detail */
    base -> RXIMR[mbIdx] = 0x7FF << 18;

    /* Configure reception message buffer. See "Message Buffer Structure" in RM */
    base -> Classic_MessageBuffer[mbIdx].EDL =  0;		/* No extended data length */
    base -> Classic_MessageBuffer[mbIdx].BRS =  0;		/* No bit-rate switch */
    base -> Classic_MessageBuffer[mbIdx].ESI =  0;		/* No applies */
    base -> Classic_MessageBuffer[mbIdx].CODE = 4;		/* When a frame is received successfully, this field is automatically updated to FULL */
    base -> Classic_MessageBuffer[mbIdx].SRR =  0;		/* No applies */
    base -> Classic_MessageBuffer[mbIdx].IDE =  0;		/* Standard ID */
    base -> Classic_MessageBuffer[mbIdx].RTR =  0;		/* No remote request made */
    base -> Classic_MessageBuffer[mbIdx].DLC = 0x8;  	/* 8 bytes of payload */

    /* Configure the ID */
    base -> Classic_MessageBuffer[mbIdx].STD_ID = id;

    FLEXCAN_ExitFreezeMode(base);

    /* Block for module ready flag */
    while(base -> MCR_Bits.NOTRDY);

    /* Success ID installation */
    return (STATUS_SUCCESS);
}


/*!
* @brief Receive a single CAN frame
*
* @param [frame]  A reference to a frame for transmitting
*
* @return Success If a frame was read successfully
* @return Failure If at least an error occurred
*/
status_t FlexCAN_receive_frame (CAN_Type* base, standard_frame_t* frame, uint8_t mbIdx)
{
    /* Default output and return values */
    status_t status = (STATUS_EEE_ERROR_DATA_NOT_FOUND);

    /* Check the RX message buffer */
    if(base -> IFLAG1 & (1 << mbIdx))
    {
        /* Harvest the ID */
        frame -> ID = base -> Classic_MessageBuffer[mbIdx].STD_ID;

        /* Harvest the payload */
        for(uint8_t i = 0; i < 4; i++)
            frame -> payload[i] = base -> Classic_MessageBuffer[mbIdx].payload[3-i];
        for(uint8_t i = 4; i < 8; i++)
            frame -> payload[i] = base -> Classic_MessageBuffer[mbIdx].payload[8-i+3];
        /* Dummy read of the timer for unlocking the MB */
        base -> TIMER;

        /* Clear the flag previously polled (W1C register) */
        base -> IFLAG1 = (1 << mbIdx);

        /* Return success status code */
        status = (STATUS_SUCCESS);
    }
    return status;
}


/*!
* @brief Transmit a single CAN frame
*
* @param [frame] 	 The reference to the frame that is going to be transmitted
*
* @return Success    If the frame was sent immediately
*/
status_t FlexCAN_transmit_frame (CAN_Type* base, standard_frame_t* frame, uint8_t mbIdx)
{
    /* Insert the payload for transmission. CAN Classic has 2 words (8 bytes) for payload */
    for(uint8_t i = 0; i < 4; i++)
    {
        base -> Classic_MessageBuffer[mbIdx].payload[3-i] = frame -> payload[i];
    }
    for(uint8_t i = 4; i < 8; i++)
    {
        base -> Classic_MessageBuffer[mbIdx].payload[8-i+3] = frame -> payload[i];
    }

    /* Set the frame's destination ID */
    base -> Classic_MessageBuffer[mbIdx].STD_ID = frame -> ID;

/* Set the transmission code to send the frame */
    base->Classic_MessageBuffer[mbIdx].CODE = 0xC; // TX request
    
    /* After a successful transmission the interrupt flag of the corresponding message buffer is set */
    while(!(base -> IFLAG1 & (1 << mbIdx)));

    /* Clear the flag previously polled (W1C register) */
    base -> IFLAG1 |= (1 << mbIdx);

    /* Return successful transmission request status */
    return STATUS_SUCCESS;
}

/*!
* @brief Setup a message buffer for reception of a specific ID
*
* @param [uint32_t id] Standard ID
*
* @return Success If the ID was installed correctly
*/
status_t FlexCAN_Config_TxMB (CAN_Type* base, uint8_t mbIdx )
{
    FLEXCAN_EnterFreezeMode(base);


/* Configure transmission message buffer. See "Message Buffer Structure" in RM */
    base -> Classic_MessageBuffer[mbIdx].EDL =  0;   	/* No extended data length */
    base -> Classic_MessageBuffer[mbIdx].BRS =  0;   	/* No bit-rate switch */
    base -> Classic_MessageBuffer[mbIdx].ESI =  0;		/* No applies */
    base -> Classic_MessageBuffer[mbIdx].SRR =  0;		/* No applies */
    base -> Classic_MessageBuffer[mbIdx].IDE =  0;   	/* Standard ID */
    base -> Classic_MessageBuffer[mbIdx].RTR =  0;		/* No remote request made */
    base -> Classic_MessageBuffer[mbIdx].DLC = 0x8;  	/* 8 bytes of payload */
    base -> Classic_MessageBuffer[mbIdx].CODE = 0xC; 	/* After TX, the MB automatically returns to the INACTIVE state */


    FLEXCAN_ExitFreezeMode(base);

    /* Block for module ready flag */
    while(base -> MCR_Bits.NOTRDY);

    /* Success ID installation */
    return (STATUS_SUCCESS);
}