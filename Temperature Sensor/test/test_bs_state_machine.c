#include "unity.h"
#include <stdio.h>
#include "bs_state_machine.h"
#include "ow_state_machine.h"
#include "mock_hardware_interface.h"
#include "event.h"

extern BitSearchInfo bsInfo;
extern uint8_t responsePulse[2];
int status=0;

void setUp(void){}

void tearDown(void){}

void test_COMMAND_STATE_received_START_EVT_performs_search_ROM_and_go_to_BIT_SEARCH_STATE(void){
  searchROM_Expect();
  
  status = bitSearchSM(START_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(BIT_SEARCH_STATE, bsInfo.bsState);
}

void test_COMMAND_STATE_received_other_event_like_UART_TX_CPL_EVT_will_not_jump_to_the_next_state(void){
  bsInfo.bsState = COMMAND_STATE;
  
  status = bitSearchSM(UART_TX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(COMMAND_STATE, bsInfo.bsState);
}

void test_BIT_SEARCH_STATE_received_UART_TX_CPL_EVT_will_send_out_read_slot_to_device_and_jump_to_BIT_SELECT_STATE(void){
  bsInfo.bsState = BIT_SEARCH_STATE;
  
  owReceive_Expect(responsePulse, sizeof(responsePulse));
  owReadSlot_Expect(_2Bytes);
  
  status = bitSearchSM(UART_TX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(BIT_SELECT_STATE, bsInfo.bsState);
}

void test_BIT_SEARCH_STATE_received_other_event_like_UART_RX_CPL_EVT_with_go_back_to_the_COMMAND_STATE(void){
  bsInfo.bsState = BIT_SEARCH_STATE;
  
  status = bitSearchSM(UART_RX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(COMMAND_STATE, bsInfo.bsState);
}

void test_BIT_SELECT_STATE_received_UART_RX_CPL_EVT_will_transmit_byte0_given_responsePulse_received_f0_f0(void){
  uint8_t bitSelect = BYTE0;
  bsInfo.bsState = BIT_SELECT_STATE;
  
  responsePulse[0] = 0xf8;
  responsePulse[1] = 0xf8;
  owTransmit_Expect(&bitSelect, _1Byte);
  
  status = bitSearchSM(UART_RX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(BIT_SEARCH_STATE, bsInfo.bsState);
}

void test_BIT_SELECT_STATE_received_UART_RX_CPL_EVT_will_transmit_byte0_given_responsePulse_received_f0_f1(void){
  uint8_t bitSelect = BYTE0;
  bsInfo.bsState = BIT_SELECT_STATE;
  
  responsePulse[0] = 0xf8;
  responsePulse[1] = 0xff;
  owTransmit_Expect(&bitSelect, _1Byte);
  
  status = bitSearchSM(UART_RX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(BIT_SEARCH_STATE, bsInfo.bsState);
}

void test_BIT_SELECT_STATE_received_UART_RX_CPL_EVT_will_transmit_byte0_given_responsePulse_received_ff_f8(void){
  uint8_t bitSelect = BYTE1;
  bsInfo.bsState = BIT_SELECT_STATE;
  
  responsePulse[0] = 0xff;
  responsePulse[1] = 0xf8;
  owTransmit_Expect(&bitSelect, _1Byte);
  
  status = bitSearchSM(UART_RX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(BIT_SEARCH_STATE, bsInfo.bsState);
}

void test_BIT_SELECT_STATE_received_UART_RX_CPL_EVT_will_transmit_byte0_given_responsePulse_received_ff_ff(void){
  bsInfo.bsState = BIT_SELECT_STATE;
  
  responsePulse[0] = 0xff;
  responsePulse[1] = 0xff;
  
  status = bitSearchSM(UART_RX_CPL_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(COMMAND_STATE, bsInfo.bsState);
}

void test_BIT_SELECT_STATE_received_other_event_like_START_EVT_will_jump_back_to_COMMAND_STATE(void){
  bsInfo.bsState = BIT_SELECT_STATE;
  
  status = bitSearchSM(START_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(COMMAND_STATE, bsInfo.bsState);
}
