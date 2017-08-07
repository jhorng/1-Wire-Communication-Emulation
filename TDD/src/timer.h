#ifndef _TIMER_H
#define _TIMER_H

typedef struct{
  uint32_t CR1;           
  uint32_t CR2;          
  uint32_t SMCR;          
  uint32_t DIER;        
  uint32_t SR;           
  uint32_t EGR;       
  uint32_t CCMR1;          
  uint32_t CCMR2;         
  uint32_t CCER;        
  uint32_t CNT;    
  uint32_t PSC;      
  uint32_t ARR;      
  uint32_t RCR;    
  uint32_t CCR1; 
  uint32_t CCR2;
  uint32_t CCR3;
  uint32_t CCR4;
  uint32_t BDTR;
  uint32_t DCR;            
  uint32_t DMAR;
  uint32_t OR;
}TIM_TypeDef;

typedef struct{
  uint32_t Prescaler;
  uint32_t CounterMode;
  uint32_t Period;
  uint32_t ClockDivision;
  uint32_t RepetitionCounter;
} TIM_Base_InitTypeDef;

typedef enum{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01, 
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02,
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04,   
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08,  
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00
}HAL_TIM_ActiveChannel;

typedef enum{
  HAL_TIM_STATE_RESET             = 0x00, 
  HAL_TIM_STATE_READY             = 0x01,    
  HAL_TIM_STATE_BUSY              = 0x02,
  HAL_TIM_STATE_TIMEOUT           = 0x03, 
  HAL_TIM_STATE_ERROR             = 0x04  
}HAL_TIM_StateTypeDef;

typedef struct{
  TIM_TypeDef              *Instance;
  TIM_Base_InitTypeDef     Init;
  HAL_TIM_ActiveChannel    Channel;
  DMA_HandleTypeDef        *hdma[7];
  HAL_LockTypeDef          Lock;
  HAL_TIM_StateTypeDef   State;
}TIM_HandleTypeDef;

#endif // _TIMER_H
