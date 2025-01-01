#ifndef CLOCKS_AND_MODES_H_
#define CLOCKS_AND_MODES_H_


#include<stdint.h>

typedef struct 
{
    volatile uint32_t   VERID;              /** 0x00 **/  /** Version ID Register **/
    volatile uint32_t   PARAM;              /** 0x04 **/  /** Parameter Register **/
        uint8_t RESERVE_1[8];
    volatile uint32_t   CSR;                /** 0x10 **/  /** Clock Status Register **/
    volatile uint32_t   RCCR;               /** 0x14 **/  /** Run Clock Control Register **/
    volatile uint32_t   VCCR;               /** 0x18 **/  /** VLPR Clock Control Register **/
    volatile uint32_t   HCCR;               /** 0x1C **/  /** HSRUN Clock Control Register **/
    volatile uint32_t   CLKOUTCNFG;         /** 0x20 **/  /** SCG CLKOUT Configuration Register **/
        uint8_t RESERVE_2[220];
    volatile uint32_t   SOSCCSR;            /** 0x100 **/ /** System OSC Control Status Register **/
    volatile uint32_t   SOSCDIV;            /** 0x104 **/ /** System OSC Divide Register **/
    volatile uint32_t   SOSCCFG;            /** 0x108 **/ /** System Oscillator Configuration Register **/
        uint8_t RESERVE_3[244];
    volatile uint32_t   SIRCCSR;            /** 0x200 **/ /** Slow IRC Control Status Register  **/
    volatile uint32_t   SIRCDIV;            /** 0x204 **/ /** Slow IRC Divide Register  **/
    volatile uint32_t   SIRCCFG;            /** 0x208 **/ /** Slow IRC Configuration Register  **/
        uint8_t RESERVE_4[244];
    volatile uint32_t   FIRCCSR;            /** 0x300 **/ /** Fast IRC Control Status Register **/
    volatile uint32_t   FIRCDIV;            /** 0x304 **/ /** Fast IRC Divide Register **/
    volatile uint32_t   FIRCCFG;            /** 0x308 **/ /** Fast IRC Configuration Register **/
        uint8_t RESERVE_5[756];
    volatile uint32_t   SPLLCSR;            /** 0x600 **/ /** System PLL Control Status Register **/
    volatile uint32_t   SPLLDIV;            /** 0x604 **/ /** System PLL Divide Register **/
    volatile uint32_t   SPLLCFG;            /** 0x608 **/ /** System PLL Configuration Register **/
}SCG_Type;

#define    SCG_BASE     (0x40064000u)
#define    SCG          ((SCG_Type *)SCG_BASE)

/* ----------------------------------------------------------------------------
   -- SCG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCG_Register_Masks SCG Register Masks
 * @{
 */

/* VERID Bit Fields */
#define SCG_VERID_VERSION_MASK                   0xFFFFFFFFu
#define SCG_VERID_VERSION_SHIFT                  0u
#define SCG_VERID_VERSION_WIDTH                  32u
#define SCG_VERID_VERSION(x)                     (((uint32_t)(((uint32_t)(x))<<SCG_VERID_VERSION_SHIFT))&SCG_VERID_VERSION_MASK)
/* PARAM Bit Fields */
#define SCG_PARAM_CLKPRES_MASK                   0xFFu
#define SCG_PARAM_CLKPRES_SHIFT                  0u
#define SCG_PARAM_CLKPRES_WIDTH                  8u
#define SCG_PARAM_CLKPRES(x)                     (((uint32_t)(((uint32_t)(x))<<SCG_PARAM_CLKPRES_SHIFT))&SCG_PARAM_CLKPRES_MASK)
#define SCG_PARAM_DIVPRES_MASK                   0xF8000000u
#define SCG_PARAM_DIVPRES_SHIFT                  27u
#define SCG_PARAM_DIVPRES_WIDTH                  5u
#define SCG_PARAM_DIVPRES(x)                     (((uint32_t)(((uint32_t)(x))<<SCG_PARAM_DIVPRES_SHIFT))&SCG_PARAM_DIVPRES_MASK)
/* CSR Bit Fields */
#define SCG_CSR_DIVSLOW_MASK                     0xFu
#define SCG_CSR_DIVSLOW_SHIFT                    0u
#define SCG_CSR_DIVSLOW_WIDTH                    4u
#define SCG_CSR_DIVSLOW(x)                       (((uint32_t)(((uint32_t)(x))<<SCG_CSR_DIVSLOW_SHIFT))&SCG_CSR_DIVSLOW_MASK)
#define SCG_CSR_DIVBUS_MASK                      0xF0u
#define SCG_CSR_DIVBUS_SHIFT                     4u
#define SCG_CSR_DIVBUS_WIDTH                     4u
#define SCG_CSR_DIVBUS(x)                        (((uint32_t)(((uint32_t)(x))<<SCG_CSR_DIVBUS_SHIFT))&SCG_CSR_DIVBUS_MASK)
#define SCG_CSR_DIVCORE_MASK                     0xF0000u
#define SCG_CSR_DIVCORE_SHIFT                    16u
#define SCG_CSR_DIVCORE_WIDTH                    4u
#define SCG_CSR_DIVCORE(x)                       (((uint32_t)(((uint32_t)(x))<<SCG_CSR_DIVCORE_SHIFT))&SCG_CSR_DIVCORE_MASK)
#define SCG_CSR_SCS_MASK                         0xF000000u
#define SCG_CSR_SCS_SHIFT                        24u
#define SCG_CSR_SCS_WIDTH                        4u
#define SCG_CSR_SCS(x)                           (((uint32_t)(((uint32_t)(x))<<SCG_CSR_SCS_SHIFT))&SCG_CSR_SCS_MASK)
/* RCCR Bit Fields */
#define SCG_RCCR_DIVSLOW_MASK                    0xFu
#define SCG_RCCR_DIVSLOW_SHIFT                   0u
#define SCG_RCCR_DIVSLOW_WIDTH                   4u
#define SCG_RCCR_DIVSLOW(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_DIVSLOW_SHIFT))&SCG_RCCR_DIVSLOW_MASK)
#define SCG_RCCR_DIVBUS_MASK                     0xF0u
#define SCG_RCCR_DIVBUS_SHIFT                    4u
#define SCG_RCCR_DIVBUS_WIDTH                    4u
#define SCG_RCCR_DIVBUS(x)                       (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_DIVBUS_SHIFT))&SCG_RCCR_DIVBUS_MASK)
#define SCG_RCCR_DIVCORE_MASK                    0xF0000u
#define SCG_RCCR_DIVCORE_SHIFT                   16u
#define SCG_RCCR_DIVCORE_WIDTH                   4u
#define SCG_RCCR_DIVCORE(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_DIVCORE_SHIFT))&SCG_RCCR_DIVCORE_MASK)
#define SCG_RCCR_SCS_MASK                        0xF000000u
#define SCG_RCCR_SCS_SHIFT                       24u
#define SCG_RCCR_SCS_WIDTH                       4u
#define SCG_RCCR_SCS(x)                          (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_SCS_SHIFT))&SCG_RCCR_SCS_MASK)
/* VCCR Bit Fields */
#define SCG_VCCR_DIVSLOW_MASK                    0xFu
#define SCG_VCCR_DIVSLOW_SHIFT                   0u
#define SCG_VCCR_DIVSLOW_WIDTH                   4u
#define SCG_VCCR_DIVSLOW(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_VCCR_DIVSLOW_SHIFT))&SCG_VCCR_DIVSLOW_MASK)
#define SCG_VCCR_DIVBUS_MASK                     0xF0u
#define SCG_VCCR_DIVBUS_SHIFT                    4u
#define SCG_VCCR_DIVBUS_WIDTH                    4u
#define SCG_VCCR_DIVBUS(x)                       (((uint32_t)(((uint32_t)(x))<<SCG_VCCR_DIVBUS_SHIFT))&SCG_VCCR_DIVBUS_MASK)
#define SCG_VCCR_DIVCORE_MASK                    0xF0000u
#define SCG_VCCR_DIVCORE_SHIFT                   16u
#define SCG_VCCR_DIVCORE_WIDTH                   4u
#define SCG_VCCR_DIVCORE(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_VCCR_DIVCORE_SHIFT))&SCG_VCCR_DIVCORE_MASK)
#define SCG_VCCR_SCS_MASK                        0xF000000u
#define SCG_VCCR_SCS_SHIFT                       24u
#define SCG_VCCR_SCS_WIDTH                       4u
#define SCG_VCCR_SCS(x)                          (((uint32_t)(((uint32_t)(x))<<SCG_VCCR_SCS_SHIFT))&SCG_VCCR_SCS_MASK)
/* HCCR Bit Fields */
#define SCG_HCCR_DIVSLOW_MASK                    0xFu
#define SCG_HCCR_DIVSLOW_SHIFT                   0u
#define SCG_HCCR_DIVSLOW_WIDTH                   4u
#define SCG_HCCR_DIVSLOW(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_HCCR_DIVSLOW_SHIFT))&SCG_HCCR_DIVSLOW_MASK)
#define SCG_HCCR_DIVBUS_MASK                     0xF0u
#define SCG_HCCR_DIVBUS_SHIFT                    4u
#define SCG_HCCR_DIVBUS_WIDTH                    4u
#define SCG_HCCR_DIVBUS(x)                       (((uint32_t)(((uint32_t)(x))<<SCG_HCCR_DIVBUS_SHIFT))&SCG_HCCR_DIVBUS_MASK)
#define SCG_HCCR_DIVCORE_MASK                    0xF0000u
#define SCG_HCCR_DIVCORE_SHIFT                   16u
#define SCG_HCCR_DIVCORE_WIDTH                   4u
#define SCG_HCCR_DIVCORE(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_HCCR_DIVCORE_SHIFT))&SCG_HCCR_DIVCORE_MASK)
#define SCG_HCCR_SCS_MASK                        0xF000000u
#define SCG_HCCR_SCS_SHIFT                       24u
#define SCG_HCCR_SCS_WIDTH                       4u
#define SCG_HCCR_SCS(x)                          (((uint32_t)(((uint32_t)(x))<<SCG_HCCR_SCS_SHIFT))&SCG_HCCR_SCS_MASK)
/* CLKOUTCNFG Bit Fields */
#define SCG_CLKOUTCNFG_CLKOUTSEL_MASK            0xF000000u
#define SCG_CLKOUTCNFG_CLKOUTSEL_SHIFT           24u
#define SCG_CLKOUTCNFG_CLKOUTSEL_WIDTH           4u
#define SCG_CLKOUTCNFG_CLKOUTSEL(x)              (((uint32_t)(((uint32_t)(x))<<SCG_CLKOUTCNFG_CLKOUTSEL_SHIFT))&SCG_CLKOUTCNFG_CLKOUTSEL_MASK)
/* SOSCCSR Bit Fields */
#define SCG_SOSCCSR_SOSCEN_MASK                  0x1u
#define SCG_SOSCCSR_SOSCEN_SHIFT                 0u
#define SCG_SOSCCSR_SOSCEN_WIDTH                 1u
#define SCG_SOSCCSR_SOSCEN(x)                    (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_SOSCEN_SHIFT))&SCG_SOSCCSR_SOSCEN_MASK)
#define SCG_SOSCCSR_SOSCCM_MASK                  0x10000u
#define SCG_SOSCCSR_SOSCCM_SHIFT                 16u
#define SCG_SOSCCSR_SOSCCM_WIDTH                 1u
#define SCG_SOSCCSR_SOSCCM(x)                    (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_SOSCCM_SHIFT))&SCG_SOSCCSR_SOSCCM_MASK)
#define SCG_SOSCCSR_SOSCCMRE_MASK                0x20000u
#define SCG_SOSCCSR_SOSCCMRE_SHIFT               17u
#define SCG_SOSCCSR_SOSCCMRE_WIDTH               1u
#define SCG_SOSCCSR_SOSCCMRE(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_SOSCCMRE_SHIFT))&SCG_SOSCCSR_SOSCCMRE_MASK)
#define SCG_SOSCCSR_LK_MASK                      0x800000u
#define SCG_SOSCCSR_LK_SHIFT                     23u
#define SCG_SOSCCSR_LK_WIDTH                     1u
#define SCG_SOSCCSR_LK(x)                        (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_LK_SHIFT))&SCG_SOSCCSR_LK_MASK)
#define SCG_SOSCCSR_SOSCVLD_MASK                 0x1000000u
#define SCG_SOSCCSR_SOSCVLD_SHIFT                24u
#define SCG_SOSCCSR_SOSCVLD_WIDTH                1u
#define SCG_SOSCCSR_SOSCVLD(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_SOSCVLD_SHIFT))&SCG_SOSCCSR_SOSCVLD_MASK)
#define SCG_SOSCCSR_SOSCSEL_MASK                 0x2000000u
#define SCG_SOSCCSR_SOSCSEL_SHIFT                25u
#define SCG_SOSCCSR_SOSCSEL_WIDTH                1u
#define SCG_SOSCCSR_SOSCSEL(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_SOSCSEL_SHIFT))&SCG_SOSCCSR_SOSCSEL_MASK)
#define SCG_SOSCCSR_SOSCERR_MASK                 0x4000000u
#define SCG_SOSCCSR_SOSCERR_SHIFT                26u
#define SCG_SOSCCSR_SOSCERR_WIDTH                1u
#define SCG_SOSCCSR_SOSCERR(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_SOSCERR_SHIFT))&SCG_SOSCCSR_SOSCERR_MASK)
/* SOSCDIV Bit Fields */
#define SCG_SOSCDIV_SOSCDIV1_MASK                0x7u
#define SCG_SOSCDIV_SOSCDIV1_SHIFT               0u
#define SCG_SOSCDIV_SOSCDIV1_WIDTH               3u
#define SCG_SOSCDIV_SOSCDIV1(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SOSCDIV_SOSCDIV1_SHIFT))&SCG_SOSCDIV_SOSCDIV1_MASK)
#define SCG_SOSCDIV_SOSCDIV2_MASK                0x700u
#define SCG_SOSCDIV_SOSCDIV2_SHIFT               8u
#define SCG_SOSCDIV_SOSCDIV2_WIDTH               3u
#define SCG_SOSCDIV_SOSCDIV2(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SOSCDIV_SOSCDIV2_SHIFT))&SCG_SOSCDIV_SOSCDIV2_MASK)
/* SOSCCFG Bit Fields */
#define SCG_SOSCCFG_EREFS_MASK                   0x4u
#define SCG_SOSCCFG_EREFS_SHIFT                  2u
#define SCG_SOSCCFG_EREFS_WIDTH                  1u
#define SCG_SOSCCFG_EREFS(x)                     (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCFG_EREFS_SHIFT))&SCG_SOSCCFG_EREFS_MASK)
#define SCG_SOSCCFG_HGO_MASK                     0x8u
#define SCG_SOSCCFG_HGO_SHIFT                    3u
#define SCG_SOSCCFG_HGO_WIDTH                    1u
#define SCG_SOSCCFG_HGO(x)                       (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCFG_HGO_SHIFT))&SCG_SOSCCFG_HGO_MASK)
#define SCG_SOSCCFG_RANGE_MASK                   0x30u
#define SCG_SOSCCFG_RANGE_SHIFT                  4u
#define SCG_SOSCCFG_RANGE_WIDTH                  2u
#define SCG_SOSCCFG_RANGE(x)                     (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCFG_RANGE_SHIFT))&SCG_SOSCCFG_RANGE_MASK)
/* SIRCCSR Bit Fields */
#define SCG_SIRCCSR_SIRCEN_MASK                  0x1u
#define SCG_SIRCCSR_SIRCEN_SHIFT                 0u
#define SCG_SIRCCSR_SIRCEN_WIDTH                 1u
#define SCG_SIRCCSR_SIRCEN(x)                    (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_SIRCEN_SHIFT))&SCG_SIRCCSR_SIRCEN_MASK)
#define SCG_SIRCCSR_SIRCSTEN_MASK                0x2u
#define SCG_SIRCCSR_SIRCSTEN_SHIFT               1u
#define SCG_SIRCCSR_SIRCSTEN_WIDTH               1u
#define SCG_SIRCCSR_SIRCSTEN(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_SIRCSTEN_SHIFT))&SCG_SIRCCSR_SIRCSTEN_MASK)
#define SCG_SIRCCSR_SIRCLPEN_MASK                0x4u
#define SCG_SIRCCSR_SIRCLPEN_SHIFT               2u
#define SCG_SIRCCSR_SIRCLPEN_WIDTH               1u
#define SCG_SIRCCSR_SIRCLPEN(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_SIRCLPEN_SHIFT))&SCG_SIRCCSR_SIRCLPEN_MASK)
#define SCG_SIRCCSR_LK_MASK                      0x800000u
#define SCG_SIRCCSR_LK_SHIFT                     23u
#define SCG_SIRCCSR_LK_WIDTH                     1u
#define SCG_SIRCCSR_LK(x)                        (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_LK_SHIFT))&SCG_SIRCCSR_LK_MASK)
#define SCG_SIRCCSR_SIRCVLD_MASK                 0x1000000u
#define SCG_SIRCCSR_SIRCVLD_SHIFT                24u
#define SCG_SIRCCSR_SIRCVLD_WIDTH                1u
#define SCG_SIRCCSR_SIRCVLD(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_SIRCVLD_SHIFT))&SCG_SIRCCSR_SIRCVLD_MASK)
#define SCG_SIRCCSR_SIRCSEL_MASK                 0x2000000u
#define SCG_SIRCCSR_SIRCSEL_SHIFT                25u
#define SCG_SIRCCSR_SIRCSEL_WIDTH                1u
#define SCG_SIRCCSR_SIRCSEL(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_SIRCSEL_SHIFT))&SCG_SIRCCSR_SIRCSEL_MASK)
/* SIRCDIV Bit Fields */
#define SCG_SIRCDIV_SIRCDIV1_MASK                0x7u
#define SCG_SIRCDIV_SIRCDIV1_SHIFT               0u
#define SCG_SIRCDIV_SIRCDIV1_WIDTH               3u
#define SCG_SIRCDIV_SIRCDIV1(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_SIRCDIV1_SHIFT))&SCG_SIRCDIV_SIRCDIV1_MASK)
#define SCG_SIRCDIV_SIRCDIV2_MASK                0x700u
#define SCG_SIRCDIV_SIRCDIV2_SHIFT               8u
#define SCG_SIRCDIV_SIRCDIV2_WIDTH               3u
#define SCG_SIRCDIV_SIRCDIV2(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_SIRCDIV2_SHIFT))&SCG_SIRCDIV_SIRCDIV2_MASK)
/* SIRCCFG Bit Fields */
#define SCG_SIRCCFG_RANGE_MASK                   0x1u
#define SCG_SIRCCFG_RANGE_SHIFT                  0u
#define SCG_SIRCCFG_RANGE_WIDTH                  1u
#define SCG_SIRCCFG_RANGE(x)                     (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCFG_RANGE_SHIFT))&SCG_SIRCCFG_RANGE_MASK)
/* FIRCCSR Bit Fields */
#define SCG_FIRCCSR_FIRCEN_MASK                  0x1u
#define SCG_FIRCCSR_FIRCEN_SHIFT                 0u
#define SCG_FIRCCSR_FIRCEN_WIDTH                 1u
#define SCG_FIRCCSR_FIRCEN(x)                    (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_FIRCEN_SHIFT))&SCG_FIRCCSR_FIRCEN_MASK)
#define SCG_FIRCCSR_FIRCREGOFF_MASK              0x8u
#define SCG_FIRCCSR_FIRCREGOFF_SHIFT             3u
#define SCG_FIRCCSR_FIRCREGOFF_WIDTH             1u
#define SCG_FIRCCSR_FIRCREGOFF(x)                (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_FIRCREGOFF_SHIFT))&SCG_FIRCCSR_FIRCREGOFF_MASK)
#define SCG_FIRCCSR_LK_MASK                      0x800000u
#define SCG_FIRCCSR_LK_SHIFT                     23u
#define SCG_FIRCCSR_LK_WIDTH                     1u
#define SCG_FIRCCSR_LK(x)                        (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_LK_SHIFT))&SCG_FIRCCSR_LK_MASK)
#define SCG_FIRCCSR_FIRCVLD_MASK                 0x1000000u
#define SCG_FIRCCSR_FIRCVLD_SHIFT                24u
#define SCG_FIRCCSR_FIRCVLD_WIDTH                1u
#define SCG_FIRCCSR_FIRCVLD(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_FIRCVLD_SHIFT))&SCG_FIRCCSR_FIRCVLD_MASK)
#define SCG_FIRCCSR_FIRCSEL_MASK                 0x2000000u
#define SCG_FIRCCSR_FIRCSEL_SHIFT                25u
#define SCG_FIRCCSR_FIRCSEL_WIDTH                1u
#define SCG_FIRCCSR_FIRCSEL(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_FIRCSEL_SHIFT))&SCG_FIRCCSR_FIRCSEL_MASK)
#define SCG_FIRCCSR_FIRCERR_MASK                 0x4000000u
#define SCG_FIRCCSR_FIRCERR_SHIFT                26u
#define SCG_FIRCCSR_FIRCERR_WIDTH                1u
#define SCG_FIRCCSR_FIRCERR(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_FIRCERR_SHIFT))&SCG_FIRCCSR_FIRCERR_MASK)
/* FIRCDIV Bit Fields */
#define SCG_FIRCDIV_FIRCDIV1_MASK                0x7u
#define SCG_FIRCDIV_FIRCDIV1_SHIFT               0u
#define SCG_FIRCDIV_FIRCDIV1_WIDTH               3u
#define SCG_FIRCDIV_FIRCDIV1(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_FIRCDIV1_SHIFT))&SCG_FIRCDIV_FIRCDIV1_MASK)
#define SCG_FIRCDIV_FIRCDIV2_MASK                0x700u
#define SCG_FIRCDIV_FIRCDIV2_SHIFT               8u
#define SCG_FIRCDIV_FIRCDIV2_WIDTH               3u
#define SCG_FIRCDIV_FIRCDIV2(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_FIRCDIV2_SHIFT))&SCG_FIRCDIV_FIRCDIV2_MASK)
/* FIRCCFG Bit Fields */
#define SCG_FIRCCFG_RANGE_MASK                   0x3u
#define SCG_FIRCCFG_RANGE_SHIFT                  0u
#define SCG_FIRCCFG_RANGE_WIDTH                  2u
#define SCG_FIRCCFG_RANGE(x)                     (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCFG_RANGE_SHIFT))&SCG_FIRCCFG_RANGE_MASK)
/* SPLLCSR Bit Fields */
#define SCG_SPLLCSR_SPLLEN_MASK                  0x1u
#define SCG_SPLLCSR_SPLLEN_SHIFT                 0u
#define SCG_SPLLCSR_SPLLEN_WIDTH                 1u
#define SCG_SPLLCSR_SPLLEN(x)                    (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCSR_SPLLEN_SHIFT))&SCG_SPLLCSR_SPLLEN_MASK)
#define SCG_SPLLCSR_SPLLCM_MASK                  0x10000u
#define SCG_SPLLCSR_SPLLCM_SHIFT                 16u
#define SCG_SPLLCSR_SPLLCM_WIDTH                 1u
#define SCG_SPLLCSR_SPLLCM(x)                    (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCSR_SPLLCM_SHIFT))&SCG_SPLLCSR_SPLLCM_MASK)
#define SCG_SPLLCSR_SPLLCMRE_MASK                0x20000u
#define SCG_SPLLCSR_SPLLCMRE_SHIFT               17u
#define SCG_SPLLCSR_SPLLCMRE_WIDTH               1u
#define SCG_SPLLCSR_SPLLCMRE(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCSR_SPLLCMRE_SHIFT))&SCG_SPLLCSR_SPLLCMRE_MASK)
#define SCG_SPLLCSR_LK_MASK                      0x800000u
#define SCG_SPLLCSR_LK_SHIFT                     23u
#define SCG_SPLLCSR_LK_WIDTH                     1u
#define SCG_SPLLCSR_LK(x)                        (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCSR_LK_SHIFT))&SCG_SPLLCSR_LK_MASK)
#define SCG_SPLLCSR_SPLLVLD_MASK                 0x1000000u
#define SCG_SPLLCSR_SPLLVLD_SHIFT                24u
#define SCG_SPLLCSR_SPLLVLD_WIDTH                1u
#define SCG_SPLLCSR_SPLLVLD(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCSR_SPLLVLD_SHIFT))&SCG_SPLLCSR_SPLLVLD_MASK)
#define SCG_SPLLCSR_SPLLSEL_MASK                 0x2000000u
#define SCG_SPLLCSR_SPLLSEL_SHIFT                25u
#define SCG_SPLLCSR_SPLLSEL_WIDTH                1u
#define SCG_SPLLCSR_SPLLSEL(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCSR_SPLLSEL_SHIFT))&SCG_SPLLCSR_SPLLSEL_MASK)
#define SCG_SPLLCSR_SPLLERR_MASK                 0x4000000u
#define SCG_SPLLCSR_SPLLERR_SHIFT                26u
#define SCG_SPLLCSR_SPLLERR_WIDTH                1u
#define SCG_SPLLCSR_SPLLERR(x)                   (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCSR_SPLLERR_SHIFT))&SCG_SPLLCSR_SPLLERR_MASK)
/* SPLLDIV Bit Fields */
#define SCG_SPLLDIV_SPLLDIV1_MASK                0x7u
#define SCG_SPLLDIV_SPLLDIV1_SHIFT               0u
#define SCG_SPLLDIV_SPLLDIV1_WIDTH               3u
#define SCG_SPLLDIV_SPLLDIV1(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SPLLDIV_SPLLDIV1_SHIFT))&SCG_SPLLDIV_SPLLDIV1_MASK)
#define SCG_SPLLDIV_SPLLDIV2_MASK                0x700u
#define SCG_SPLLDIV_SPLLDIV2_SHIFT               8u
#define SCG_SPLLDIV_SPLLDIV2_WIDTH               3u
#define SCG_SPLLDIV_SPLLDIV2(x)                  (((uint32_t)(((uint32_t)(x))<<SCG_SPLLDIV_SPLLDIV2_SHIFT))&SCG_SPLLDIV_SPLLDIV2_MASK)
/* SPLLCFG Bit Fields */
#define SCG_SPLLCFG_PREDIV_MASK                  0x700u
#define SCG_SPLLCFG_PREDIV_SHIFT                 8u
#define SCG_SPLLCFG_PREDIV_WIDTH                 3u
#define SCG_SPLLCFG_PREDIV(x)                    (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCFG_PREDIV_SHIFT))&SCG_SPLLCFG_PREDIV_MASK)
#define SCG_SPLLCFG_MULT_MASK                    0x1F0000u
#define SCG_SPLLCFG_MULT_SHIFT                   16u
#define SCG_SPLLCFG_MULT_WIDTH                   5u
#define SCG_SPLLCFG_MULT(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_SPLLCFG_MULT_SHIFT))&SCG_SPLLCFG_MULT_MASK)

/*!
 * @}
 */ /* end of group SCG_Register_Masks */

void SOSC_init_8MHz (void);
void SPLL_init_160MHz (void);
void NormalRUNmode_80MHz (void);

#endif /* CLOCKS_AND_MODES_H_ */

