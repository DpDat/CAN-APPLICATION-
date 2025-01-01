#include"nvic.h"


void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    NVIC->ISER[IRQn / 32] |= (1u << (IRQn % 32));
}
/********************************************************************/
void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    NVIC->ICER[IRQn / 32] |= (1u << (IRQn % 32));
}
/********************************************************************/
void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    NVIC->ISPR[IRQn / 32] |= (1u << (IRQn % 32));
}
/********************************************************************/
void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    NVIC->ICPR[IRQn / 32] |= (1u << (IRQn % 32));
}
/********************************************************************/
uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    return (NVIC->ISPR[IRQn / 32] & (1u << (IRQn % 32)));
}
/********************************************************************/
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    NVIC->IPR[IRQn / 4] |= (1u << (4*(IRQn / 4) + (IRQn % 4))) ;
}
/********************************************************************/
uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{
    return (NVIC->IPR[IRQn / 4] & (1u << (4*(IRQn / 4) + (IRQn % 4))));
}