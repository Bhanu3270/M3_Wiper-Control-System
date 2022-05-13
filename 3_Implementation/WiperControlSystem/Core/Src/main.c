
#include "main.h"
#include "stm32f4xx_hal_def.h"
#define GPIO_PIN_12             ((uint16_t)0x1000)
#define GPIO_PIN_13             ((uint16_t)0x2000)
#define GPIO_PIN_14             ((uint16_t)0x4000)
#define GPIO_PIN_15             ((uint16_t)0x8000)
#define GPIO_PIN_0               ((uint16_t)0x0001)
#define LED_NUMBER               4
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Error_Handler(void);
 void Delay_ms(volatile int time_ms);




int main(void)
{


  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
    void  pinMode();

  int LEDPinArray[LED_NUMBER]= {GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_12, GPIO_PIN_13};

 unsigned long debounceDuration = 2000; // mills
 unsigned long lastTimeButtonStateChanged = 0;

 char lastButtonState = SET;

 int LEDIndex = 0;


 void initALLLEDs()
 {

	 int i, OUTPUT;

	 for (i =0; i <  LED_NUMBER; i++)
	 {
		 pinMode(LEDPinArray[i],  OUTPUT);
	 }
 }


 void  powerOnSelectedLEDOnly(int index)
 {
     int i;
	 for(  i = 0; i < LED_NUMBER; i++ )
	 {
		 if (i == index){

			 digitalWrite(LEDPinArray[i], SET);

		 }
		 else
		 {
			 digitalWrite(LEDPinArray[i] , RESET);
		 }
	 }
 }

 void setup()
 {
	 initALLLEDs();
	 pinMode(GPIO_PIN_0, GPIO_MODE_INPUT);
	 digitalWrite(LEDPinArray[LEDIndex], RESET);
 }


 void loop()
 {

	 unsigned long timeNow = mills();
	 if (timeNow - lastTimeButtonStateChanged > debounceDuration)
	 {
		 int  buttonState = digitalWrite(GPIO_PIN_0);
		 if (buttonState != lastButtonState){
			 lastTimeButtonStateChanged = timeNow;
			 lastButtonState =  buttonState;

			 if (buttonState == SET)
			 {
				 LEDIndex++;
				 if (LEDIndex >= LED_NUMBER)
				 {
					 LEDIndex = 0;
				 }

				 powerOnSelectedLEDOnly(LEDIndex);
			 }
		 }
	 }

 }

 void Delay_ms(volatile int time_ms)
 {
 	int j;
 	for(j = 0; j < time_ms*4000; j++)
 	{

 	}
 }
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
