#include <Arduino.h>
#include "main.h"

bool flag;
uint8_t GPIO_Pin3 = D9;
#define RX_BUFFER_SIZE      10
#define LED D5
uint8_t rxbuffer[RX_BUFFER_SIZE];
int CountH, CountL;

////////////////////////////////////////////

enum eSerialStates {
  Action = 0,
  TX_SEND_DATA,
};

enum eSerialStates eSerialState;

/////////////////////////////////////////////
void ICACHE_RAM_ATTR INTCALLBACK()
{
  if ( Serial.available() )
    {
        Serial.readBytes(rxbuffer, RX_BUFFER_SIZE);     
    }

 
}

void setup() {

  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin3), INTCALLBACK, RISING);

}

void loop() {


  switch ( eSerialState )
  {
case Action:
      
          OnOf(CountH,CountL);
          if (flag==1)
          {
             eSerialState = TX_SEND_DATA;

          }
                   
      break;
    
case TX_SEND_DATA:

      
        eSerialState = Action;
      break;
    
default:
      break;
  }
}


void OnOf(int timeHigh, int timeLow ){

        digitalWrite(LED,HIGH);
        delay(timeHigh);
        digitalWrite(LED,LOW);
        delay(timeLow);



}