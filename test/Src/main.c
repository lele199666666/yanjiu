
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdlib.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t aTxBuffer1[] = "+++\r\n";
uint8_t aTxBuffer2[] = "AT+SAVETRANSLINK=1,\"47.106.143.61\",8080,\"TCP\"\r\n";
uint8_t aTxBuffer3[] = "AT+CIPSTART=\"TCP\",\"47.106.143.61\",8080\r\n";
uint8_t aTxBuffer4[] = "AT+CIPMODE=1\r\n";
uint8_t aTxBuffer5[] = "AT+CIPSEND\r\n";
uint8_t aTxBuffer6[] = "POST / HTTP/1.1\r\n"
"Host: 45.40.240.159:6969\r\n"
"Connection: keep-alive\r\n"
"Pragma: no-cache\r\n"
"Cache-Control: no-cache\r\n"
"Upgrade-Insecure-Requests: 1\r\n"
"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Accept-Language: zh-CN,zh;q=0.9\r\n"
"Content-Type: application/x-www-form-urlencoded\r\n"
"Content-Length: 30\r\n"
"\r\n"
"tempureture=1&humidity=2";


char * stringTemplate1 = "POST /airSensor/servlet/regServlet HTTP/1.1\r\n"
//"Host: 45.40.240.159:6969\r\n"
"Host: 47.106.143.61:8080\r\n"
"Connection: keep-alive\r\n"
"Pragma: no-cache\r\n"
"Cache-Control: no-cache\r\n"
"Upgrade-Insecure-Requests: 1\r\n"
"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Accept-Language: zh-CN,zh;q=0.9\r\n"
"Content-Type: application/x-www-form-urlencoded\r\n"
"Content-Length: ";

char *stringTemplate2 = "\r\n"
"\r\n"
"tmp=";

char *stringTemplate3 = "&hum=";

char *stringTemplate4 = "&sensor_id=";

char stringTemplateX[1000] ;

char stringTemplateParams[100];

#define TXBUFFERSIZE                      sizeof(aTxBuffer)-1

#define RXBUFFERSIZE                       99
uint8_t aRxBuffer[RXBUFFERSIZE];
uint32_t TimingDelay;
uint32_t Timer1Delay;      //定时器1延时变量
typedef enum{
	GPIOA12_INPUT = 0,
	GPIOA12_OUTPUT = 1
}GPIOA12_MODE;
ITStatus UartReady = RESET; //串口发送标志位
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void systickDelay(uint32_t ms);
void timer1Delay(uint32_t us);
void changePA12mode(GPIOA12_MODE mode);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_TIM1_Init();
  MX_USART1_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  unsigned char data[] = {0,0,0,0,0,0,0,0,0,0};
		unsigned char data1[] = {0,0,0,0,0,0,0,0,0,0};
		/*HAL_UART_Receive_IT(&huart1 , (uint8_t*)aRxBuffer , RXBUFFERSIZE);
		while(UartReady != SET);
		UartReady = RESET;*/
		
		//初始化DHT11引脚 PA12为输出
		changePA12mode(GPIOA12_OUTPUT);
		__nop();
		timer1Delay(5);
		__nop();
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
		systickDelay(1000);

		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		systickDelay(1000);
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
		systickDelay(18);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
		changePA12mode(GPIOA12_INPUT);
		
		
		//检测DHT11开始信号
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_SET);
		
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET);
		
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_SET);

		//数据传输开始
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET);
		//__nop();
		
		for(int i=0;i<5;i++){
			for(int j=0;j<8;j++){
				timer1Delay(5);
				if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET){
				//代表数字0
					data[i] = data[i] << 1;
					data[i] = data[i] || 0; 
					data1[i] <<= 1;
					data1[i] |= 0;
					while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET);
				}			
				else{
				//代表数字1
					data[i] = data[i] << 1;
					data[i] = data[i] || 1;
					data1[i] <<= 1;
					data1[i] |= 1;
					while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_SET);
					while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET);
				}
			}
		}
		__nop();
		// DHT11接受结束， 接受数据存放在data1中
		sprintf(stringTemplateParams,"%s%d%s%d%s%d",stringTemplate2,data1[2],stringTemplate3,data1[0],stringTemplate4,1);
		int size1 = strlen(stringTemplateParams)-4;
		sprintf(stringTemplateX,"%s%d%s",stringTemplate1,size1,stringTemplateParams);
		int size2 = strlen(stringTemplateX);
		
		//uint8_t *aTxBuffer = (uint8_t*)malloc(500);
		//strcpy(aTxBuffer,stringTemplateX);
		
		//开始ESP8266发送
		HAL_UART_Transmit_IT(&huart1, (uint8_t*)stringTemplateX, size2); //指针强制转换
		while(UartReady != SET);
		UartReady = RESET;
		//HAL_UART_Transmit_IT(&huart1, (uint8_t*)aTxBuffer2, sizeof(aTxBuffer2)-1); //指针强制转换
		//while(UartReady != SET);
		//UartReady = RESET;
		//HAL_UART_Receive_IT(&huart1 , (uint8_t*)aRxBuffer , RXBUFFERSIZE);
		//while(UartReady != SET);
		//UartReady = RESET;
		__nop();
		
		systickDelay(28000);
		
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM1_UP_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_DOWN;
  htim1.Init.Period = 720-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

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
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_12, GPIO_PIN_SET);

  /*Configure GPIO pins : PA8 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void systickDelay(uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}
void timer1Delay(uint32_t us)
{
	HAL_TIM_Base_Start_IT(&htim1);
	Timer1Delay = us;
	while(Timer1Delay !=0);
	HAL_TIM_Base_Stop_IT(&htim1);
}
void changePA12mode(GPIOA12_MODE mode){
	 GPIO_InitTypeDef GPIO_InitStruct;

	if(mode == GPIOA12_INPUT){
		/*Configure GPIO pins : PA8 PA12 */
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	else{
		  /*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, GPIO_PIN_SET);

		/*Configure GPIO pins : PA8 PA12 */
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}

//串口发送处理
 void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  UartReady = SET;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  UartReady = SET;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
