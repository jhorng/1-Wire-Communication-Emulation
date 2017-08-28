#include "unity.h"
#include <stdio.h>
#include "bs_state_machine.h"
#include "ow_state_machine.h"
#include "mock_hardware_interface.h"
#include "event.h"

extern BitSearchInfo bsInfo;
int status=0;

void setUp(void){}

void tearDown(void){}

void test_COMMAND_STATE_received_START_EVT_performs_search_ROM_and_go_to_BIT_SEARCH_STATE(void){
  searchROM_Expect();
  
  status = bitSearchSM(START_EVT);
  
  TEST_ASSERT_EQUAL(1, status);
  TEST_ASSERT_EQUAL(BIT_SEARCH_STATE, bsInfo.bsState);
}