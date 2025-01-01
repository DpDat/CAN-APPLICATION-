#include "lpuart_register.h"
#include "pcc.h"

void LPUART1_Baudrate_Config(uint32_t baudrate);
void LPUART1_Control_Config();

void LPUART1_transmit_char(char send) ;
void LPUART1_transmit_string(char data_string[]);
char LPUART1_receive_char(void);
void LPUART1_receive_and_echo_char(void);
void LPUART1_receive_string(char *buffer, uint32_t fixed_length);

void LPUART1_init();