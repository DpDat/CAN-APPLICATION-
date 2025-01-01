#include "port.h"

void PORT_init (void)
{
	/*!
	*           Pins Definitions
	* =====================================
	*
	*    Pin Number     |    Function
	* ----------------- |------------------
	* PTE4              | CAN0 [Rx]
	* PTE5			 	| CAN0 [Tx]
    * PTC6              | UART1 RX
	* PTC7              | UART1 TX
	*/

	/* Pin multiplexing for FlexCAN */
    PCC -> PCC_PORTE = (1 << 30u);   	/* Clock gating to PORT E */
    PORTE -> PCR[4] |= (1 << 10) | (1 << 8); 	/* CAN0_RX at PORT E pin 4 */
    PORTE -> PCR[5] |= (1 << 10) | (1 << 8); 	/* CAN0_TX at PORT E pin 5 */

    /* Pin multiplexing for Green LED */
    PCC -> PCC_PORTD = (1 << 30u); 		/* Clock gating to PORT D*/
    PORTD -> PCR[16] = (1 << 8); 	/* GPIO multiplexing */
    //GPIOD->PDDR |= 1 << PTD16; 					/* Direction as output */

    PCC -> PCC_PORTC = (1 << 30u);
    PORTC->PCR[6]|= (1 << 9u);	/* Port C6: MUX = ALT2, UART1 RX */
    PORTC->PCR[7]|= (1 << 9u);   /* Port C7: MUX = ALT2, UART1 TX */
}