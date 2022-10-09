#ifndef _COMM_H_
#define _COMM_H_

#include <Arduino.h>
#include "uart_register.h"

#define LED D5

extern String Buffer;
extern int32_t CountH ;
extern int32_t CountL ;
extern int32_t LastCounterHolderH, LastCounterHolderL;
extern bool flag;

void uart0_rx_intr_handler(void *para);

void install_uart_tout();

void OnOf(int timeHigh, int timeLow);

uint8_t Echo(String Eword);

void LastCountHolder(int32_t &a, int32_t &b, int32_t &c, int32_t &d);

void Led_State_Setting (String ReceivedData);

#endif // _COMM_H_