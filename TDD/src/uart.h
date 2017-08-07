#ifndef UART_H_
#define UART_H_

typedef struct{
  uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

typedef struct{
  uint32_t BaudRate;
  uint32_t WordLength;
  uint32_t StopBits;
  uint32_t Parity;
  uint32_t Mode; 
  uint32_t HwFlowCtl;
  uint32_t OverSampling;
}UART_InitTypeDef;

typedef enum{
  HAL_UNLOCKED = 0x00,
  HAL_LOCKED   = 0x01  
} HAL_LockTypeDef;

typedef enum{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

typedef struct{
  uint32_t CCR;
  uint32_t CNDTR;
  uint32_t CPAR;
  uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct{
  uint32_t Direction;
  uint32_t PeriphInc;
  uint32_t MemInc;
  uint32_t PeriphDataAlignment;
  uint32_t MemDataAlignment;                      
  uint32_t Mode;
  uint32_t Priority;
}DMA_InitTypeDef;

typedef enum{
  HAL_DMA_STATE_RESET             = 0x00,  
  HAL_DMA_STATE_READY             = 0x01,  
  HAL_DMA_STATE_READY_HALF        = 0x11,  
  HAL_DMA_STATE_BUSY              = 0x02,
  HAL_DMA_STATE_TIMEOUT           = 0x03, 
  HAL_DMA_STATE_ERROR             = 0x04,
}HAL_DMA_StateTypeDef;

typedef struct __DMA_HandleTypeDef{
  DMA_Channel_TypeDef   *Instance; 
  DMA_InitTypeDef       Init;
  HAL_LockTypeDef       Lock;
  HAL_DMA_StateTypeDef  State;
  void *Parent; 
  void (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);     
  void (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma); 
  void (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);    
  uint32_t ErrorCode;
} DMA_HandleTypeDef;   

typedef enum{
  HAL_UART_STATE_RESET             = 0x00,    /*!< Peripheral is not initialized                      */
  HAL_UART_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use           */
  HAL_UART_STATE_BUSY              = 0x02,    /*!< an internal process is ongoing                     */
  HAL_UART_STATE_BUSY_TX           = 0x12,    /*!< Data Transmission process is ongoing               */
  HAL_UART_STATE_BUSY_RX           = 0x22,    /*!< Data Reception process is ongoing                  */
  HAL_UART_STATE_BUSY_TX_RX        = 0x32,    /*!< Data Transmission and Reception process is ongoing */
  HAL_UART_STATE_TIMEOUT           = 0x03,    /*!< Timeout state                                      */
  HAL_UART_STATE_ERROR             = 0x04     /*!< Error                                              */
}HAL_UART_StateTypeDef;

typedef struct{
  USART_TypeDef                 *Instance;        /*!< UART registers base address        */
  UART_InitTypeDef              Init;             /*!< UART communication parameters      */
  uint8_t                       *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */
  uint16_t                      TxXferSize;       /*!< UART Tx Transfer size              */
  uint16_t                      TxXferCount;      /*!< UART Tx Transfer Counter           */
  uint8_t                       *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */
  uint16_t                      RxXferSize;       /*!< UART Rx Transfer size              */
  uint16_t                      RxXferCount;      /*!< UART Rx Transfer Counter           */  
  DMA_HandleTypeDef             *hdmatx;          /*!< UART Tx DMA Handle parameters      */
  DMA_HandleTypeDef             *hdmarx;          /*!< UART Rx DMA Handle parameters      */
  HAL_LockTypeDef               Lock;             /*!< Locking object                     */
  HAL_UART_StateTypeDef    State;            /*!< UART communication state           */
  uint32_t                 ErrorCode;        /*!< UART Error code                    */
}UART_HandleTypeDef;  

#endif /* UART_H_ */