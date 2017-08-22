#include <stdlib.h>
#include <stdio.h>
#include "unity.h"
#include "ow_state_machine.h"
#include "bs_state_machine.h"
#include "mock_hardware_interface.h"
#include "event.h"

extern OneWireInfo owInfo;
extern uint8_t presencePulse;
extern uint8_t responsePulse[72];
int status;

void setUp(void){}

void tearDown(void){}

void test_IDLE_STATE_receives_START_EVT_will_enable_tx_rx_start_timer_send_reset_pulse_and_jump_into_RESET_STATE(void){
  owInfo.owState = IDLE_STATE;
  halfDuplex_EnableTxRx_Expect();
  timerStart_Expect(1920);
  owReceive_Expect(&presencePulse, sizeof(presencePulse));
  resetPulse_Expect();
  
  status = oneWireSM(START_EVT);
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(RESET_STATE, owInfo.owState);
}

void test_IDLE_STATE_receives_UART_TX_CPL_EVT_will_remain_in_IDLE_STATE(void){
  owInfo.owState = IDLE_STATE;
  
  status = oneWireSM(UART_TX_CPL_EVT);
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(IDLE_STATE, owInfo.owState);
}

void test_RESET_STATE_receives_UART_TX_CPL_EVT_will_jump_to_IDLE_STATE(void){
  owInfo.owState = RESET_STATE;
  
  status = oneWireSM(UART_TX_CPL_EVT);
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(RESET_STATE, owInfo.owState);
}

void test_RESET_STATE_receives_UART_RX_CPL_EVT_will_jump_to_RESPONSE_STATE(void){
  owInfo.owState = RESET_STATE;
  
  timerStop_Expect();
  timerStart_Expect(200);
  status = oneWireSM(UART_RX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(RESPONSE_STATE, owInfo.owState);
}

void test_RESET_STATE_receives_TIMEOUT_EVT_will_jump_to_IDLE_STATE(void){
  owInfo.owState = RESET_STATE;
  
  timerStop_Expect();
  status = oneWireSM(TIMEOUT_EVT);
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(IDLE_STATE, owInfo.owState);
}

void test_RESET_STATE_receives_START_EVT_will_jump_to_IDLE_STATE(void){
  owInfo.owState = RESET_STATE;
  
  status = oneWireSM(START_EVT);
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(IDLE_STATE, owInfo.owState);
}

void test_RESPONSE_STATE_receives_TIMEOUT_EVT_will_stop_timer_and_send_read_rom_command_and_go_to_RESPONSE_STATE(void){
  owInfo.owState = RESPONSE_STATE;
  
  timerStop_Expect();
  
  status = oneWireSM(TIMEOUT_EVT);
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(RESPONSE_STATE, owInfo.owState);
}

void test_RESPONSE_STATE_receives_UART_RX_CPL_EVT_will_go_to_IDLE_STATE(void){
  owInfo.owState = RESPONSE_STATE;
  
  status = oneWireSM(UART_RX_CPL_EVT);
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(IDLE_STATE, owInfo.owState);
}



