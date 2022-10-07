#ifndef _TEMP_H_
#define _TEMP_H_

#include <Arduino.h>
#include "uart_register.h"
#define LED D5

extern String Buffer;

void uart0_rx_intr_handler(void *para);
void install_uart_tout();
void OnOf(int timeHigh, int timeLow );
uint8_t Echo (String Eword);


#endif // _TEMP_H_