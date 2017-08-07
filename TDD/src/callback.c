#include <stdlib.h>
#include "callback.h"
#include "state_machine.h"
#include "event.h"

void HAL_UART_TxCpltCallback(int *huart){
  BitSearchingFSM(UART_TX_CPL_EVT);
}