#include "lpuart.h"

#define BAUD_CLOCK      48000000

// void LPUART0_Baudrate_Config(uint32_t baudrate)
// {
//     LPUART0->BAUD_Register &= ~(0xFFFFFFFF);                         /*Clear 32 bit*/

//     LPUART0->BAUD_Register |= 0xF000000;                             /* Config OSR ratio 16 */
//     LPUART0->BAUD_Register = (BAUD_CLOCK/((OSR + 1) * baudrate));
//     LPUART0->BAUD_Register &= ~(1u << 13); 					        /* Select stop bit is 1(SBNS) */ 
//     //LPUART0->BAUD |= (1u << 29);                            /* Select 10 bit data characters */
// }

void LPUART1_Baudrate_Config(uint32_t baudrate)
{
    LPUART1->BAUD_Register &= ~(0xFFFFFFFF);                         /* Clear 32 bit */

    LPUART1->BAUD_Bits.OSR = 15;                            	/* Config OSR ratio 16 */
    LPUART1->BAUD_Register = (BAUD_CLOCK/((15+ 1) * baudrate));    /* Config SBR */
    LPUART1->BAUD_Register &= ~(1u << 13); 					        /* Select stop bit is 1(SBNS) */ 
    //LPUART1->BAUD |= (1u << 29);                            /* Select 10 bit data characters */
}


/*===========================================================================================================================

=============================================================================================================================*/
// void LPUART0_Control_Config()
// {
//     LPUART0->CTRL_Register &= ~(0xFFFFFFFF);

//     LPUART0->CTRL_Bits &= ~( 1u<< 4); 				            /* Select data characters number is 8(M)*/ 
// 	LPUART0->CTRL |= ( 1u<< 1); 					        /* Enable parity(PE) */
//     LPUART0->CTRL &= ~( 1u<< 0);                            /* Parity Even */

//     LPUART1->CTRL |= (1u << 11);
// 	LPUART0->CTRL |= (1u << 21);				            /* Enable Receiver interrupt*/
// 	LPUART0->CTRL |= (1u << 19); 				            /* Enable transmitter(TE) */
// 	LPUART0->CTRL |= (1u << 18); 			                /* Enable receiver */ 
// }

void LPUART1_Control_Config()
{
    LPUART1->CTRL_Register &= ~(0xFFFFFFFF);

    LPUART1->CTRL_Bits.M = 0; 				            /* Select data characters number is 8(M)*/
	LPUART1->CTRL_Bits.PE = 0; 					        /* disable parity(PE) */
    LPUART1->CTRL_Bits.PT = 0;                             /* Parity even */

    //LPUART1->CTRL |= (1u << 11);
	LPUART1->CTRL_Bits.RIE = 1;				            /* Enable Receiver interrupt*/
	LPUART1->CTRL_Bits.TE = 1; 				            /* Enable transmitter(TE) */
	LPUART1->CTRL_Bits.RE = 1; 			                /* Enable receiver */ 
}

/*===========================================================================================================================

=============================================================================================================================*/

void LPUART1_transmit_char(char send) {    /* Function to Transmit single Char */
	while((LPUART1->STAT_Bits.TDRE) == 0);
	/* Wait for transmit buffer to be empty */
	LPUART1->DATA_Register = send;              /* Send data */
}

void LPUART1_transmit_string(char data_string[])  {  /* Function to Transmit whole string */
	uint32_t index = 0;
	while(data_string[index] != '\0')  {           /* Send chars one at a time */
		LPUART1_transmit_char(data_string[index]);
		index++;
	}
}

char LPUART1_receive_char(void) {    /* Function to Receive single Char */
	char receive;
	while((LPUART1->STAT_Bits.RDRF) == 0);
	/* Wait for received buffer to be full */
	receive= LPUART1->DATA_Register;            /* Read received data*/
	return receive;
}

void LPUART1_receive_and_echo_char(void)  {  /* Function to echo received char back */
	char send = LPUART1_receive_char();        /* Receive Char */
	LPUART1_transmit_char(send);               /* Transmit same char back to the sender */
	//LPUART1_transmit_char('\n');               /* New line */
	LPUART1_transmit_char('\r');               /* Return */
}

void LPUART1_receive_string(char *buffer, uint32_t fixed_length) {
    uint32_t i = 0; // Index to track the position in the buffer
    char received_char;
	
    // Loop to receive characters
    while (i < fixed_length - 1) { // Leave space for the null terminator '\0'
        received_char = LPUART1_receive_char(); // Call function to receive a single character

        if (received_char == '\n' || received_char == '\r') {
            break; // Stop if an end-of-line character is received
        }

        buffer[i++] = received_char; // Store the character in the buffer
    }

    buffer[i] = '\0'; // Add null terminator to mark the end of the string
}

void LPUART1_init(){
    PCC->PCC_LPUART1 |= (1 << 30) | (1 << 25);

	LPUART1->BAUD_Bits.SBR = 0x34; 	/* Initialize for 9600 baud, 1 stop: */
    LPUART1->BAUD_Bits.OSR = 15;  	/* SBR=52 (0x34): baud divisor = 8M/9600/16 = ~52 */
											/* OSR=15: Over sampling ratio = 15+1=16 */
											/* SBNS=0: One stop bit */
											/* BOTHEDGE=0: receiver samples only on rising edge */
											/* M10=0: Rx and Tx use 7 to 9 bit data characters */
											/* RESYNCDIS=0: Resync during rec'd data word supported */
											/* LBKDIE, RXEDGIE=0: interrupts disable */
											/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
											/* MAEN1, MAEN2,  MATCFG=0: Match disabled */
	LPUART1->CTRL_Bits.RIE = 1;				            /* Enable Receiver interrupt*/
	LPUART1->CTRL_Bits.RE =	1;
	LPUART1->CTRL_Bits.TE = 1;   	/* Enable transmitter & receiver, no parity, 8 bit char: */
												/* RE=1: Receiver enabled */
												/* TE=1: Transmitter enabled */
												/* PE,PT=0: No hw parity generation or checking */
												/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
												/* DOZEEN=0: LPUART enabled in Doze mode */
												/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
												/* TxDIR=0: TxD pin is input if in single-wire mode */
												/* TXINV=0: TRansmit data not inverted */
												/* RWU,WAKE=0: normal operation; rcvr not in statndby */
												/* IDLCFG=0: one idle character */
												/* ILT=0: Idle char bit count starts after start bit */
												/* SBK=0: Normal transmitter operation - no break char */
												/* LOOPS,RSRC=0: no loop back */
}