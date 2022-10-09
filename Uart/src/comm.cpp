#include "comm.h"

String Buffer{""};
String value;
String OnHolder;
String OffHolder;

int32_t CountH;
int32_t CountL;

uint32_t i = 0;
int32_t LastCounterHolderH, LastCounterHolderL;

bool flag;
int32_t Time;
void uart0_rx_intr_handler(void *para)
{

  uint8_t uart_no = UART0;
  uint8_t fifo_len = 0;
  uint8_t buf_idx = 0;
  uint32_t uart_intr_status = READ_PERI_REG(UART_INT_ST(uart_no)); // get uart interrupt status
  while (uart_intr_status != 0x00)
  {
    if (UART_FRM_ERR_INT_ST == (uart_intr_status & UART_FRM_ERR_INT_ST))
    {
      WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_FRM_ERR_INT_CLR);
      Serial.println("caused by a frm_err interrupt");
    }
    else if (UART_RXFIFO_FULL_INT_ST == (uart_intr_status & UART_RXFIFO_FULL_INT_ST))
    {
      Serial.println("caused by fifo_full interrupt");
      fifo_len = (READ_PERI_REG(UART_STATUS(uart_no)) >> UART_RXFIFO_CNT_S) & UART_RXFIFO_CNT;
      char r[fifo_len];
      buf_idx = 0;
      while (buf_idx < fifo_len)
      {
        r[buf_idx] = READ_PERI_REG(UART_FIFO(uart_no)) & 0xFF;
        buf_idx++;
      }
      r[fifo_len] = '\0';
      WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_RXFIFO_FULL_INT_CLR);
    }
    else if (UART_RXFIFO_TOUT_INT_ST == (uart_intr_status & UART_RXFIFO_TOUT_INT_ST))
    {

      fifo_len = (READ_PERI_REG(UART_STATUS(uart_no)) >> UART_RXFIFO_CNT_S) & UART_RXFIFO_CNT; // read fifo length

      char r[fifo_len];

      buf_idx = 0;
      while (buf_idx < fifo_len) // read all the data in rx fifo
      {

        r[buf_idx] = READ_PERI_REG(UART_FIFO(uart_no)) & 0xFF;

        buf_idx++;
      }

      Buffer = "";

      r[fifo_len] = '\0';

      for (int i = 0; i < fifo_len - 2; i++)
      {
        Buffer = Buffer + "0" /*filling buffer with zeros*/;
      }

      for (int i = 0; i < fifo_len - 2; i++)
      {
        Buffer[i] = r[i] /*Updating buffer with incoming data*/;
        flag = 1;
      }

      WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_RXFIFO_TOUT_INT_CLR); // clear full interrupt state
    }
    else if (UART_TXFIFO_EMPTY_INT_ST == (uart_intr_status & UART_TXFIFO_EMPTY_INT_ST))
    {
      Serial.println("caused by a tx_empty interrupt");
      WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_TXFIFO_EMPTY_INT_CLR);
      CLEAR_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_TXFIFO_EMPTY_INT_ENA);
    }
    else
    {
    }
    uart_intr_status = READ_PERI_REG(UART_INT_ST(uart_no)); // update interrupt status
  }
}

void install_uart_tout()
{ // Setting uart interrupt
  ETS_UART_INTR_DISABLE();
  ETS_UART_INTR_ATTACH(uart0_rx_intr_handler, NULL);
  SET_PERI_REG_MASK(UART_INT_ENA(0), UART_RXFIFO_TOUT_INT_ENA);
  WRITE_PERI_REG(UART_CONF1(0), UART_RX_TOUT_EN |
                                    ((0x2 & UART_RX_TOUT_THRHD) << UART_RX_TOUT_THRHD_S));
  WRITE_PERI_REG(UART_INT_CLR(0), 0xffff);
  SET_PERI_REG_MASK(UART_INT_ENA(0), UART_RXFIFO_TOUT_INT_ENA);
  CLEAR_PERI_REG_MASK(UART_INT_ENA(0), UART_RXFIFO_FULL_INT_ENA);

  ETS_UART_INTR_ENABLE();
}

// Led ON-OFF Function
void OnOf(int32_t timeHigh, int32_t timeLow)
{
  digitalWrite(LED, HIGH);
  delay(timeHigh);
  digitalWrite(LED, LOW);
  delay(timeLow);
}

// Echo Function
uint8_t Echo(String Eword)
{
  if (Eword == "stop" || Eword == "")
    return 0;
  else
  {
    return 1;
  }
}

//  LastCountHolder
void LastCountHolder(int32_t &a, int32_t &b, int32_t &c, int32_t &d)
{

  a = c;
  b = d;
}

//Led state settings
void Led_State_Setting(String ReceivedData)
{

  if (ReceivedData != "stop" && ReceivedData != "start")
  {
    while (flag == 1) // anti-block
    {

      if (flag == 1)
      {
        value += ReceivedData[i++];

        if (value == "led")
        {

          value = "";
        }
        if (value == "on=")
        {
          OnHolder = value;
          value = "";
        }
        if (value == "off=")
        {
          OffHolder = value;
          value = "";
        }

        if (i == ReceivedData.length())
        {

          flag = 0;
          i = 0;

          if (value.length() == 4) //for four digit numbers
          {

            Time = ((1000 * (value[0] - 48)) + (100 * (value[1] - 48)) + (10 * (value[2] - 48)) + (value[3] - 48));
          }
          if (value.length() == 3) //for three digit numbers
          {

            Time = ((100 * (value[0] - 48)) + (10 * (value[1] - 48)) + (value[2] - 48));
          }

          value = "";
          break;
        }
      }
    }
  }

  if (OnHolder == "on=") // if received data is "on"
  {

    LastCountHolder(LastCounterHolderH, LastCounterHolderL, CountH, CountL);
    CountH = Time;
    OnHolder = "";
  }

  if (OffHolder == "off=") // if received data is "off"
  {
    LastCountHolder(LastCounterHolderH, LastCounterHolderL, CountH, CountL);
    CountL = Time;
    OffHolder = "";
  }
}
