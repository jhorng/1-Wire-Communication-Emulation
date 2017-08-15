#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "unity.h"
#include "state_machine.h"
#include "mock_hardware_interface.h"
#include "event.h"

extern BitSearchingInfo bsi;
extern uint8_t responsePulse[100] = {0};

void setUp(void){}

void tearDown(void){}

void test_state_machine_receives_START_EVT_will_init_in_IDLE_STATE_and_jump_into_RESET_STATE(void){
  bsi.state = IDLE_STATE;
  HAL_HalfDuplex_EnableTxRx_Expect();
  timerStart_Expect();
  masterTransmitReceive_Expect(RECEIVE, &presencePulse, sizeof(presencePulse));
  resetPulse_Expect();
  
  bitSearchingFSM(START_EVT);
  TEST_ASSERT_EQUAL(RESET_STATE, bsi.state);
}