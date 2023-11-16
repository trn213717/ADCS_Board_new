/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"CAN.h"
#include "stm32f4xx_hal.h"
#include "sd_hal_mpu6050.h"
#include"stdio.h"
#include"string.h"
#include"GPS.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

CAN_HandleTypeDef hcan1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
 SD_MPU6050 mpu1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CAN1_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void Uart1( float a,float b , float c);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
CAN_TxHeaderTypeDef Txheader;
CAN_RxHeaderTypeDef Rxheader;

uint8_t Txdata[8];
uint8_t Rxdata[8];
uint8_t a_x;
uint8_t a_y;
uint8_t a_z;
uint8_t g_x;
uint8_t g_y;
uint8_t g_z;
uint8_t m_x, m_y, m_z;

uint32_t txmailbox;
char msg[20];
char msg1[20];
char msg2[20];
char message1[30];
uint8_t adc_value;
char hexChar ='A';
float floatValue = 1.234;
uint32_t hexValue;


//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin== GPIO_PIN_13){
//		Txdata[0] = 100;  //ms delay
//		Txdata[1] = 20;
//
//		HAL_CAN_AddTxMessage(&hcan1, &Txheader, Txdata, &txmailbox);
//	}
//}
//float convertBytesToFloat(uint8_t Rxdata[4]) {
//    uint32_t intVal = 0;
//
//    // Convert the received bytes back to a 32-bit integer
//    for (int i = 0; i < 4; i++) {
//        intVal |= (Rxdata[i] << (i * 8));
//    }
//
//    // Convert the integer back to a float
//    float receivedFloat = *((float*)&intVal);
//
//    return receivedFloat;
//}

//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
//{
//
//}
int _write(int file, char *ptr, int len)
{

 int DataIdx;

 for (DataIdx = 0; DataIdx < len; DataIdx++)
 {
   ITM_SendChar(*ptr++);
 }
 return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */



	SD_MPU6050_Result result ;
		uint8_t mpu_ok[15] = {"MPU WORK FINE\n"};
		uint8_t mpu_not[17] = {"MPU NOT WORKING\n"};
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_CAN1_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_CAN_Start(&hcan1);
    //NOTIFY
//    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

//    Txheader.DLC =2;//DATA LENGTH
//    Txheader.IDE= CAN_ID_STD;
//    Txheader.RTR=CAN_RTR_DATA;
//    Txheader.StdId=0x446; //id

//    MyData Original ={1,3.4,"Hello"};
//    memcpy(Txdata, original,sizeof(original));

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  get_location();
	  printf("%f, %f", Latitude,Longitude);
      CAN_RX();
//Accelerometer Sensor Data
      CAN_TXU1Sensor(0x101, a_x);
      CAN_TXU1Sensor(0x102, a_y);
      CAN_TXU1Sensor(0x103, a_z);
//Gyroscope Sensor Data
      CAN_TXU1Sensor(0x105, g_x);
      CAN_TXU1Sensor(0x106, g_y);
      CAN_TXU1Sensor(0x107, g_z);
//Magnetometer Sensor Data
      CAN_TXU1Sensor(0x109, m_x);
      CAN_TXU1Sensor(0x110, m_y);
      CAN_TXU1Sensor(0x111, m_z);
//Global Positioning System(GPS)
      CAN_TXU1Sensor(0x113, Latitude);
      CAN_TXU1Sensor(0x114, Longitude);
      CAN_TXU1Sensor(0x115, altitude);
      CAN_TXU1Sensor(0x117, speed);
      CAN_TXU1Sensor(0x118, Hours);
      CAN_TXU1Sensor(0x118, Min);
      CAN_TXU1Sensor(0x118, Sec);

//Rough Work
//      CAN_TXU(0x116, Latitude, Longitude, altitude);
//	  	CAN_TXU(0x100,a_x,a_y,a_z); //Accelerometer data on can
//	  	CAN_TXU(0x102,g_x,g_y,g_z); //Gyroscope data on can
//	  	CAN_TXU(0x104, m_x, m_y, m_z);  // Magnetometer data on Can
//      CAN_TXU(0x106, 100, 0,0 );     // Latitude data on Can
//      CAN_TXU(0x108, 102, 0,0 ); 	// Longitude data on Can
//      CAN_TXU(0x110, 105, 0,0 ); 	// altitude data on Can
//      CAN_TXU(0x112, 106, 0,0 );	// timestamp data on Can

	  	  result = SD_MPU6050_Init(&hi2c1,&mpu1,SD_MPU6050_Device_0,SD_MPU6050_Accelerometer_2G,SD_MPU6050_Gyroscope_250s );
//	  	  	  HAL_Delay(100);
	  	  SD_MPU6050_SetAccelerometer(&hi2c1,&mpu1, SD_MPU6050_Accelerometer_2G);
	  	  SD_MPU6050_ReadAccelerometer(&hi2c1,&mpu1);
	  	  a_x = mpu1.Accelerometer_X;

	  	  printf( "X %d ",a_x);
//	  	  		  			  HAL_UART_Transmit(&huart2, (uint8_t*)msg, 2, 100);
	  	  a_y = mpu1.Accelerometer_Y;
	  	  printf("Y_Accelerometer = %d   ",a_y );
//	  	  		  		sprintf(msg1 ,"Y = %d ",a_y );
//	  	  		  			  	  		  			  HAL_UART_Transmit(&huart2, (uint8_t*)msg, 2, 100);
	  	  a_z = mpu1.Accelerometer_Z;
	  	  printf("Z_Accelerometer = %d m/s^2  Sensitivity set to 2g\n",a_z );
	  	  Uart1(a_x,a_y , a_z);
//	  	  		sprintf(msg2 ,"Z = %d ",a_z );
//	  	  	    HAL_UART_Transmit(&huart2, (uint8_t*)msg, 2, 100);
	  	  SD_MPU6050_SetGyroscope(&hi2c1,&mpu1, SD_MPU6050_Gyroscope_250s);
	  	  SD_MPU6050_ReadGyroscope(&hi2c1,&mpu1);

	  	  g_x = mpu1.Gyroscope_X;
	  	  printf("Gyroscope_X = %d   ",g_x );

	  	  g_y = mpu1.Gyroscope_Y;
	  	  printf("Gyroscope_Y = %d   ",g_y );

	  	  g_z = mpu1.Gyroscope_Z;
	  	  printf("Gyroscope_Z = %d  degree/s  Sensitivity set to +/- 250degree/s\n",g_z );
	  	  Uart1(g_x,g_y , g_z);
//	  	  		  		 HAL_Delay(500);

//	  if(datacheck)
//	  	  {
//	  		  for(int i=0;i<Rxdata[1];i++){
//	  			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
////	  			  HAL_Delay(Rxdata[0]);
//	  			 sprintf(msg , " %d \r\n", Rxdata[i]);
//       HAL_UART_Transmit(&huart2, (uint8_t*)msg, sizeof(msg), 100);
//
//	  		  }
//	  		  datacheck=0;
//	  	  }
//	  if (datacheck1) {
//		  float result = convertBytesToFloat(Rxdata);
//		     printf("%f",result);
//		     Uart( Rxheader.StdId ,result);
//datacheck1 =0;
//
//	}
//	  if (datacheck2) {
//		  float result = convertBytesToFloat(Rxdata);
//				     printf("%f",result);
//				     Uart( Rxheader.StdId ,result);
//	 		 datacheck2 =0;
//
//	 	}

//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 100);
//	 adc_value =  HAL_ADC_GetValue(&hadc1);
//	  HAL_ADC_Stop(&hadc1);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 18;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_2TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
        CAN_FilterTypeDef can1_filter_init;
    	can1_filter_init.FilterActivation = CAN_FILTER_ENABLE;
    	can1_filter_init.FilterBank = 18;
    	can1_filter_init.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    	can1_filter_init.FilterIdHigh = 0x103<<5;
    	can1_filter_init.FilterIdLow = 0;
    	can1_filter_init.FilterMaskIdHigh = 0x1<<14;
    	can1_filter_init.FilterMaskIdLow = 0x0000;
    	can1_filter_init.FilterMode  = CAN_FILTERMODE_IDMASK;
    	can1_filter_init.FilterScale = CAN_FILTERSCALE_32BIT;
    	can1_filter_init.SlaveStartFilterBank= 20;

    	HAL_CAN_ConfigFilter(&hcan1, &can1_filter_init);

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void Uart1( float a, float b , float c){


	sprintf(message1," %f, %f , %f ",a,b,c);
	strcat(message1, "\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)message1, sizeof(message1), 100);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
