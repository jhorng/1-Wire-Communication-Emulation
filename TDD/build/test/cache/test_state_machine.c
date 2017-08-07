#include "uart.h"
#include "mock_callback.h"
#include "mock_functions.h"
#include "state_machine.h"
#include "unity.h"


extern BitSearchingInfo bsi;

extern UART_HandleTypeDef huart1;

extern TIM_HandleTypeDef htim2;

extern uint8_t presencePulse;



void setUp(void){}



void tearDown(void){}



void test_state_machine_receives_START_EVT_will_init_in_IDLE_STATE_and_jump_into_RESET_STATE(void){

  bsi.state = IDLE_STATE;

  HAL_HalfDuplex_EnableTxRx_CMockExpectAndReturn(18, &huart1, HAL_OK);

  timerStart_CMockExpect(19, &htim2);

  HAL_UART_Receive_IT_CMockExpectAndReturn(20, &huart1, &presencePulse, sizeof(presencePulse), HAL_OK);

  resetPulse_CMockExpect(21);



  bitSearchingFSM(START_EVT);

  UnityAssertEqualNumber((_U_SINT)((RESET_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(24), UNITY_DISPLAY_STYLE_INT);

}



void test_state_machine_receives_other_event_will_remain_in_IDLE_STATE(void){

  bsi.state = IDLE_STATE;











  bitSearchingFSM(UART_TX_CPL_EVT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(35), UNITY_DISPLAY_STYLE_INT);

}



void test_RESET_STATE_receives_UART_TX_CPL_EVT_will_jump_to_RESPONSE_STATE(void){

  bsi.state = RESET_STATE;



  bitSearchingFSM(UART_TX_CPL_EVT);

  UnityAssertEqualNumber((_U_SINT)((RESPONSE_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(42), UNITY_DISPLAY_STYLE_INT);

}



void test_RESET_STATE_receives_START_EVT_will_go_back_IDLE_STATE(void){

  bsi.state = RESET_STATE;



  bitSearchingFSM(START_EVT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(49), UNITY_DISPLAY_STYLE_INT);

}



void test_RESPONSE_STATE_receives_UART_RX_CPL_EVT_will_go_to_FINISH_INIT_STATE(void){

  bsi.state = RESPONSE_STATE;



  bitSearchingFSM(UART_RX_CPL_EVT);

  UnityAssertEqualNumber((_U_SINT)((FINISH_INIT_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(56), UNITY_DISPLAY_STYLE_INT);

}



void test_RESPONSE_STATE_receives_UART_TX_CPL_EVT_will_go_back_IDLE_STATE(void){

  bsi.state = RESPONSE_STATE;



  bitSearchingFSM(UART_TX_CPL_EVT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_STATE)), (_U_SINT)((bsi.state)), (((void *)0)), (_U_UINT)(63), UNITY_DISPLAY_STYLE_INT);

}
