#include "unity.h"
#include "state_machine.h"
#include "mock_functions.h"
#include "mock_callback.h"
#include "uart.h"

extern BitSearchingInfo bsi;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim2;
extern uint8_t presencePulse;

void setUp(void){}

void tearDown(void){}

void test_state_machine_receives_START_EVT_will_init_in_IDLE_STATE_and_jump_into_RESET_STATE(void){
  bsi.state = IDLE_STATE;
  HAL_HalfDuplex_EnableTxRx_ExpectAndReturn(&huart1, HAL_OK);
  timerStart_Expect(&htim2);
  HAL_UART_Receive_IT_ExpectAndReturn(&huart1, &presencePulse, sizeof(presencePulse), HAL_OK);
  resetPulse_Expect();
  
  bitSearchingFSM(START_EVT);
  TEST_ASSERT_EQUAL(RESET_STATE, bsi.state);
}

void test_state_machine_receives_other_event_will_remain_in_IDLE_STATE(void){
  bsi.state = IDLE_STATE;
  // HAL_HalfDuplex_EnableTxRx_ExpectAndReturn(&huart1, HAL_OK);
  // timerStart_Expect(&htim2);
  // HAL_UART_Receive_IT_ExpectAndReturn(&huart1, &presencePulse, sizeof(presencePulse), HAL_OK);
  // resetPulse_Expect();
  
  bitSearchingFSM(UART_TX_CPL_EVT);
  TEST_ASSERT_EQUAL(IDLE_STATE, bsi.state);
}

void test_RESET_STATE_receives_UART_TX_CPL_EVT_will_jump_to_RESPONSE_STATE(void){
  bsi.state = RESET_STATE;
  
  bitSearchingFSM(UART_TX_CPL_EVT);
  TEST_ASSERT_EQUAL(RESPONSE_STATE, bsi.state);
}

void test_RESET_STATE_receives_START_EVT_will_go_back_IDLE_STATE(void){
  bsi.state = RESET_STATE;
  
  bitSearchingFSM(START_EVT);
  TEST_ASSERT_EQUAL(IDLE_STATE, bsi.state);
}

void test_RESPONSE_STATE_receives_UART_RX_CPL_EVT_will_go_to_FINISH_INIT_STATE(void){
  bsi.state = RESPONSE_STATE;
  
  bitSearchingFSM(UART_RX_CPL_EVT);
  TEST_ASSERT_EQUAL(FINISH_INIT_STATE, bsi.state);
}

void test_RESPONSE_STATE_receives_UART_TX_CPL_EVT_will_go_back_IDLE_STATE(void){
  bsi.state = RESPONSE_STATE;
  
  bitSearchingFSM(UART_TX_CPL_EVT);
  TEST_ASSERT_EQUAL(IDLE_STATE, bsi.state);
}


