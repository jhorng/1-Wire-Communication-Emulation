#include "unity.h"
#include "state_machine.h"
#include "functions.h"

extern BitSearchingInfo bsi;

void setUp(void){}

void tearDown(void){}

void test_init_state_machine(void){
  TEST_ASSERT_EQUAL(IDLE_STATE, bsi.state);
  TEST_ASSERT_EQUAL(12, bsi.data1);
  TEST_ASSERT_EQUAL(42, bsi.data2);
}

void test_state_machine_no_change_state_from_IDLE_STATE_to_RESET_STATE_given_other_events(){
  BitSearchingFSM(UART_TX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(IDLE_STATE, bsi.state);
}

void test_state_machine_changes_state_from_IDLE_STATE_to_RESET_STATE_given_START_EVT_occurred(){
  BitSearchingFSM(START_EVT);
  
  TEST_ASSERT_EQUAL(RESET_STATE, bsi.state);
}

void test_state_machine_changes_state_from_RESET_STATE_to_RESPONSE_STATE_given_UART_TX_CPL_EVT_occurred(){
  bsi.state = RESET_STATE;  
  BitSearchingFSM(UART_TX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(RESPONSE_STATE, bsi.state);
}

void test_state_machine_no_change_state_from_RESET_STATE_to_RESET_STATE_given_other_events(){
  bsi.state = RESET_STATE;  
  BitSearchingFSM(START_EVT);
  
  TEST_ASSERT_EQUAL(RESET_STATE, bsi.state);
}

void test_state_machine_changes_state_from_RESPONSE_STATE_to_COMMAND_STATE_given_UART_RX_CPL_EVT_occurred(){
  bsi.state = RESPONSE_STATE;  
  BitSearchingFSM(UART_RX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(COMMAND_STATE, bsi.state);
}

void test_state_machine_changes_state_from_RESPONSE_STATE_to_RESET_STATE_given_other_events(){
  bsi.state = RESPONSE_STATE;  
  BitSearchingFSM(START_EVT);
  
  TEST_ASSERT_EQUAL(RESET_STATE, bsi.state);
}

void test_state_machine_changes_state_from_COMMAND_STATE_to_RESET_STATE_directly(){
  bsi.state = COMMAND_STATE;  
  BitSearchingFSM(START_EVT);
  
  TEST_ASSERT_EQUAL(RESET_STATE, bsi.state);
}

void test_dummy(){
  int *buff;
  buff = (int *)buffer(2, 5);
  
  TEST_ASSERT_EQUAL(2, buff[0]);
  TEST_ASSERT_EQUAL(5, buff[1]);
}




