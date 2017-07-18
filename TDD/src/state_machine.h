#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

typedef enum{
  START_EVT,
  UART_TX_CPL_EVT,
  UART_RX_CPL_EVT,
  TIMEOUT_EVT
}Event;

typedef enum{
  IDLE_STATE,
  RESET_STATE,
  RESPONSE_STATE,
  COMMAND_STATE
}State;

typedef struct BitSearchingInfo BitSearchingInfo;
struct BitSearchingInfo{
  State state;
  int data1;
  int data2;
};

void BitSearchingFSM(Event evt);

#endif // _STATE_MACHINE_H
