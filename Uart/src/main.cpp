#include <Arduino.h>
#include "Temp.h"

#define RX_BUFFER_SIZE      10

bool flag;
String EchoWord;
uint8_t GPIO_Pin3 = D9;
uint8_t rxbuffer[RX_BUFFER_SIZE];
int CountH=300;
int CountL=700;

// String Buffer;
////////////////////////////////////////////

enum eSerialStates {
  Action = 0,
  TX_SEND_DATA,
};

enum eSerialStates eSerialState;

/////////////////////////////////////////////


void setup() {

  Serial.begin(115200);
  install_uart_tout();
  pinMode(LED, OUTPUT);

}

void loop() {


  switch ( eSerialState )
  {
case Action:
          OnOf(CountH,CountL);
         
             eSerialState = TX_SEND_DATA;

          
                   
      break;
    
case TX_SEND_DATA:
      

      if (Buffer == "Stop")
      {
        CountH=1000;  CountL=1000;
        Serial.println("burdası stop");
        memset(&Buffer, 0, sizeof(Buffer));

      }
       else if (Buffer == "start")
      {
        CountH=1000;  CountL=1000;

        Serial.println("Burası start");
        memset(&Buffer, 0, sizeof(Buffer));

      }
       else if (Buffer == "ledon=500")
      {
        CountH=500;  

        Serial.println("Burası LedOn");
        memset(&Buffer, 0, sizeof(Buffer));

      }
        else if (Buffer == "ledoff=500")
      {
        CountL=500;

        Serial.println("Burası LedOff");
        memset(&Buffer, 0, sizeof(Buffer));

      }
      
        eSerialState = Action;
      break;
    
default:
      break;
  }
}




