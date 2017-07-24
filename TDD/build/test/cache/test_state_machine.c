#include "functions.h"
#include "state_machine.h"
#include "unity.h"


extern BitSearchingInfo bsi;



void setUp(void){}



void tearDown(void){}



void test_init_state_machine(void){

  UnityAssertEqualNumber((_U_SINT)((IDLE_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(12), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((12)), (_U_SINT)((bsi.data1)), (((void *)0)), (_U_UINT)(13), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((42)), (_U_SINT)((bsi.data2)), (((void *)0)), (_U_UINT)(14), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_no_change_state_from_IDLE_STATE_to_RESET_STATE_given_other_events(){

  BitSearchingFSM(UART_TX_CPL_EVT);



  UnityAssertEqualNumber((_U_SINT)((IDLE_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(20), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_changes_state_from_IDLE_STATE_to_RESET_STATE_given_START_EVT_occurred(){

  BitSearchingFSM(START_EVT);



  UnityAssertEqualNumber((_U_SINT)((RESET_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(26), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_changes_state_from_RESET_STATE_to_RESPONSE_STATE_given_UART_TX_CPL_EVT_occurred(){

  bsi.state = RESET_STATE;

  BitSearchingFSM(UART_TX_CPL_EVT);



  UnityAssertEqualNumber((_U_SINT)((RESPONSE_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(33), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_no_change_state_from_RESET_STATE_to_RESET_STATE_given_other_events(){

  bsi.state = RESET_STATE;

  BitSearchingFSM(START_EVT);



  UnityAssertEqualNumber((_U_SINT)((RESET_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(40), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_changes_state_from_RESPONSE_STATE_to_COMMAND_STATE_given_UART_RX_CPL_EVT_occurred(){

  bsi.state = RESPONSE_STATE;

  BitSearchingFSM(UART_RX_CPL_EVT);



  UnityAssertEqualNumber((_U_SINT)((COMMAND_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(47), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_changes_state_from_RESPONSE_STATE_to_RESET_STATE_given_other_events(){

  bsi.state = RESPONSE_STATE;

  BitSearchingFSM(START_EVT);



  UnityAssertEqualNumber((_U_SINT)((RESET_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(54), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_changes_state_from_COMMAND_STATE_to_RESET_STATE_directly(){

  bsi.state = COMMAND_STATE;

  BitSearchingFSM(START_EVT);



  UnityAssertEqualNumber((_U_SINT)((RESET_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(61), UNITY_DISPLAY_STYLE_INT);

}



void test_dummy(){

  int *buff;

  buff = (int *)buffer(2, 5);



  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((buff[0])), (((void *)0)), (_U_UINT)(68), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((buff[1])), (((void *)0)), (_U_UINT)(69), UNITY_DISPLAY_STYLE_INT);

}
