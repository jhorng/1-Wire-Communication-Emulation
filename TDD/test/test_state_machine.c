#include "unity.h"
#include "state_machine.h"

extern BitSearchingInfo bsi;

void setUp(void){}

void tearDown(void){}

void test_init_state_machine(void){
  
  TEST_ASSERT_EQUAL(IDLE_STATE, bsi.state);
  TEST_ASSERT_EQUAL(12, bsi.data1);
  TEST_ASSERT_EQUAL(42, bsi.data2);
}

