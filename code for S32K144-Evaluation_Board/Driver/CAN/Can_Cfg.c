#include "Can.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_CheckDsample
 * Description   : Check the Sample value
 *
 *END**************************************************************************/
static inline uint32_t FLEXCAN_CheckDsample(uint32_t tmpSample, uint32_t samplePoint)
{
    if (tmpSample > samplePoint)
    {
        return (tmpSample - samplePoint);
    }
    return (samplePoint - tmpSample);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_CheckdBitrate
 * Description   : Check the Bitrate value
 *
 *END**************************************************************************/
static inline uint32_t FLEXCAN_CheckdBitrate(uint32_t tmpBitrate, uint32_t bitrate)
{
    if (tmpBitrate > bitrate)
    {
        return (tmpBitrate - bitrate);
    }
    return (bitrate - tmpBitrate);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_CheckJumpwidth
 * Description   : Check the JumpWidth value
 *
 *END**************************************************************************/
static inline uint32_t FLEXCAN_CheckJumpwidth(uint32_t pseg1)
{
    if (pseg1 < FLEXCAN_RJW_MAX)
    {
        return pseg1;
    }
    return FLEXCAN_RJW_MAX;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_ProccessTSeg
 * Description   : Calculate Tseg value
 *
 *END**************************************************************************/
static inline void FLEXCAN_ProccessTSeg(uint32_t * tSeg1, uint32_t * tSeg2)
{
    /* Adjust time segment 1 and time segment 2 */
    while ((*tSeg1 >= FLEXCAN_TSEG1_MAX) || (*tSeg2 < FLEXCAN_TSEG2_MIN))
    {
        *tSeg2 = *tSeg2 + 1U;
        *tSeg1 = *tSeg1 - 1U;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_ProccessPSeg
 * Description   : Calculate Pseg value
 *
 *END**************************************************************************/
static inline void FLEXCAN_ProccessPSeg(uint32_t * tmpPropseg, uint32_t * tmpPseg1)
{
    while (*tmpPropseg <= 0U)
    {
        *tmpPropseg = *tmpPropseg + 1U;
        *tmpPseg1 = *tmpPseg1 - 1U;
    }
    
    while (*tmpPropseg >= FLEXCAN_PROPSEG_MAX)
    {
        *tmpPropseg = *tmpPropseg - 1U;
        *tmpPseg1 = *tmpPseg1 + 1U;
    }
}    
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_BitrateToTimeSeg
 * Description   : Converts a bitrate (kbit/s) in time segment values for
 *                 standard CAN frame.
 *
 *END**************************************************************************/
static void FLEXCAN_BitrateToTimeSeg(uint32_t bitrate,
                                     uint32_t clkFreq,
                                     flexcan_time_segment_t *timeSeg)
{
    uint32_t dBitrate, tmpBitrate, dBitrateMin, tmpPresdiv, tmpSample,
             dSampleMin, dSample, samplePoint, numTq, pseg1, pseg2, propseg,
             presdiv, tSeg1, tSeg2, tmpPseg1, tmpPseg2, tmpPropseg;

    presdiv = 0U;
    propseg = 0U;
    pseg1 = 0U;
    pseg2 = 0U;

    dSampleMin = 100U;
    dBitrateMin = 1000000U;
    samplePoint = 88U;

    for (tmpPresdiv = 0U; tmpPresdiv < FLEXCAN_PRESDIV_MAX; tmpPresdiv++) {

        /* Compute the number of time quanta in 1 bit time */
        numTq = clkFreq / ((tmpPresdiv + 1U) * bitrate);
        /* Compute the real bitrate resulted */
        tmpBitrate = clkFreq / ((tmpPresdiv + 1U) * numTq);

        /* The number of time quanta in 1 bit time must be lower than the one supported */
        if ((numTq >= FLEXCAN_NUM_TQ_MIN) && (numTq < FLEXCAN_NUM_TQ_MAX))
        {
            /* Compute time segments based on the value of the sampling point */
            tSeg1 = (numTq * samplePoint / 100U) - 1U;
            tSeg2 = numTq - 1U - tSeg1;

            /* Adjust time segment 1 and time segment 2 */
            FLEXCAN_ProccessTSeg(&tSeg1, &tSeg2);

            tmpPseg2 = tSeg2 - 1U;

            /* Start from pseg1 = pseg2 and adjust until propseg is valid */
            tmpPseg1 = tmpPseg2;
            tmpPropseg = tSeg1 - tmpPseg1 - 2U;

            FLEXCAN_ProccessPSeg(&tmpPropseg, &tmpPseg1);
            

            if (((tSeg1 >= FLEXCAN_TSEG1_MAX) || (tSeg2 >= FLEXCAN_TSEG2_MAX) || (tSeg2 < FLEXCAN_TSEG2_MIN) || (tSeg1 < FLEXCAN_TSEG1_MIN)) ||
               ((tmpPropseg >= FLEXCAN_PROPSEG_MAX) || (tmpPseg1 >= FLEXCAN_PSEG1_MAX) || (tmpPseg2 < FLEXCAN_PSEG2_MIN) || (tmpPseg2 >= FLEXCAN_PSEG2_MAX)))
            {
                continue;
            }

            tmpSample = ((tSeg1 + 1U) * 100U) / numTq;
            dSample = FLEXCAN_CheckDsample(tmpSample , samplePoint);
            dBitrate = FLEXCAN_CheckdBitrate(tmpBitrate , bitrate);

            if ((dBitrate < dBitrateMin) ||
                ((dBitrate == dBitrateMin) && (dSample < dSampleMin)))
            {
                dSampleMin = dSample;
                dBitrateMin = dBitrate;
                pseg1 = tmpPseg1;
                pseg2 = tmpPseg2;
                presdiv = tmpPresdiv;
                propseg = tmpPropseg;

                if ((dBitrate == 0U) && (dSample <= 1U))
                {
                    break;
                }
            }
        }
    }

    timeSeg->phaseSeg1 = pseg1;
    timeSeg->phaseSeg2 = pseg2;
    timeSeg->preDivider = presdiv;
    timeSeg->propSeg = propseg;
    timeSeg->rJumpwidth = FLEXCAN_CheckJumpwidth(pseg1);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_GetDefaultConfig
 * Description   : Gets the default configuration structure
 *
 * Implements    : FLEXCAN_DRV_GetDefaultConfig_Activity
 *END**************************************************************************/
void FLEXCAN_DRV_GetDefaultConfig(flexcan_user_config_t *config)
{
    /* Checks input parameter. */
    //DEV_ASSERT(config != NULL);

    uint32_t clkFreq = 48000000U;
    flexcan_time_segment_t timeSeg = {
        .propSeg = 6,         /*!< Propagation segment*/
        .phaseSeg1 = 3,       /*!< Phase segment 1*/
        .phaseSeg2 = 3,       /*!< Phase segment 2*/
        .preDivider = 0,      /*!< Clock prescaler division factor*/
        .rJumpwidth = 3,      /*!< Resync jump width*/
    };

    /* Get the PE clock frequency */
    //(void) CLOCK_SYS_GetFreq(FEATURE_CAN_PE_OSC_CLK_NAME, &clkFreq);

    /* Time segments computed for PE bitrate = 500 Kbit/s, sample point = 87.5 */
    //FLEXCAN_BitrateToTimeSeg(500000U, clkFreq, &timeSeg);



    /* Maximum number of message buffers */
    config->max_num_mb = 16;
    /* Rx FIFO is disabled */
    config->is_rx_fifo_needed = false;
    /* Number of Rx FIFO ID filters */
    config->num_id_filters = FLEXCAN_RX_FIFO_ID_FILTERS_8;
    /* Normal operation mode */
    config->flexcanMode = FLEXCAN_NORMAL_MODE;

    /* Protocol engine clock is System Oscillator div 2 */
    config->pe_clock = FLEXCAN_CLK_SOURCE_OSC;

    /* Time segments for the arbitration phase */
    config->bitrate = timeSeg;

    /* Payload size */
    config->payload = FLEXCAN_PAYLOAD_SIZE_8;
    /* Flexible data rate is disabled */
    config->fd_enable = false;
    /* Time segments for the data phase of FD frames */
    config->bitrate_cbt = timeSeg;

    /* Rx FIFO transfer type */
    config->transfer_type = FLEXCAN_RXFIFO_USING_INTERRUPTS;

    /* Rx FIFO DMA channel */
    config->rxFifoDMAChannel = 0U;
}