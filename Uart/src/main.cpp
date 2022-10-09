//##------- ESP8266 MCU --------##//
#include <Arduino.h>
#include "comm.h"



int32_t LastCounterHolderH, LastCounterHolderL;

enum eSerialStates
{
  Action = 0,
  TX_SEND_DATA,
};

enum eSerialStates eSerialState;

void setup()
{

  Serial.begin(115200);
  install_uart_tout();
  pinMode(LED, OUTPUT);
}

void loop()
{
  
  switch (eSerialState)
  {
  case Action: // First task 

    OnOf(CountH, CountL);
    
    eSerialState = TX_SEND_DATA;
    break;

  case TX_SEND_DATA: // Second task

    
      deneme (Buffer);
      
    // if (Buffer == "stop") //  if received data is "stop"
    // {
      
    //   Buffer ="";

    //   LastCountHolder(LastCounterHolderH, LastCounterHolderL, CountH, CountL);

    //   CountH = 1000;
    //   CountL = 1000;


    // }
    // else if (Buffer == "start") // if received data is "start"
    // {
    //   Echo(Buffer);
    //   CountH = LastCounterHolderH;
    //   CountL = LastCounterHolderL;
      

    // }
    // else if (Buffer == "ledon=500") // if received data is "ledon"
    // {
    //   CountH = 500;

    //   LastCountHolder(LastCounterHolderH, LastCounterHolderL, CountH, CountL);

    //   Echo(Buffer);
    // }
    // else if (Buffer == "ledoff=500") // if received data is "ledoff"
    // {
    //   CountL = 500;

    //   LastCountHolder(LastCounterHolderH, LastCounterHolderL, CountH, CountL);

    //   Echo(Buffer);
    // }

    eSerialState = Action;
    break;

  default:
    break;
  }

}