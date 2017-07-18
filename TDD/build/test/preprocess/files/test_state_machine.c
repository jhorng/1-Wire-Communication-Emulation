#include "build/temp/_test_state_machine.c"
#include "state_machine.h"
#include "unity.h"


extern BitSearchingInfo bsi;



void setUp(void){}



void tearDown(void){}



void test_init_state_machine(void){



  UnityAssertEqualNumber((UNITY_INT)((IDLE_STATE)), (UNITY_INT)((bsi.state)), (

 ((void *)0)

 ), (UNITY_UINT)(12), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((12)), (UNITY_INT)((bsi.data1)), (

 ((void *)0)

 ), (UNITY_UINT)(13), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((42)), (UNITY_INT)((bsi.data2)), (

 ((void *)0)

 ), (UNITY_UINT)(14), UNITY_DISPLAY_STYLE_INT);

}
