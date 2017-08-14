#include "unity.h"
#include "state_machine.h"

extern BitSearchingInfo bsi;

void setUp(void){}

void tearDown(void){}

void test_state_machine_receives_START_EVT_will_init_in_IDLE_STATE_and_jump_into_RESET_STATE(void){
  TEST_IGNORE_MESSAGE("Please implement state machine!");
  // bsi.state = IDLE_STATE;
  // HAL_HalfDuplex_EnableTxRx_ExpectAndReturn(&huart1, HAL_OK);
  // timerStart_Expect(&htim2);
  // HAL_UART_Receive_IT_ExpectAndReturn(&huart1, &presencePulse, sizeof(presencePulse), HAL_OK);
  // resetPulse_Expect();
  
  // bitSearchingFSM(START_EVT);
  // TEST_ASSERT_EQUAL(RESET_STATE, bsi.state);
}