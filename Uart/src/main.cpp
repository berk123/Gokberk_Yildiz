//##------- ESP8266 MCU --------##//

#include <Arduino.h>
#include "comm.h"

enum eSerialStates
{
  Action = 0,
  Settings,
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

    eSerialState = Settings;
    break;

  case Settings: // Second task

    Led_State_Setting(Buffer);
    if (Echo(Buffer))
    {
      Serial.println(Buffer);
    }

    if (Buffer == "stop" && flag == 1) //  if received data is "stop"
    {

      LastCountHolder(LastCounterHolderH, LastCounterHolderL, CountH, CountL);
      CountH = 1000;
      CountL = 1000;
      flag = 0;
    }
    else if (Buffer == "start") // if received data is "start"
    {

      CountH = LastCounterHolderH;
      CountL = LastCounterHolderL;
    }

    eSerialState = Action;
    break;

  default:
    break;
  }
}