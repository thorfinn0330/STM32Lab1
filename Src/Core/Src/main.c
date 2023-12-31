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
//#include "led7seg.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);


/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
char AnodeNumber[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x80}; //0 - 9,dp

void display7SEG(int num) {
	HAL_GPIO_WritePin(LED7SEG_A_GPIO_Port, LED7SEG_A_Pin, AnodeNumber[num]&0x01?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_B_GPIO_Port, LED7SEG_B_Pin, AnodeNumber[num]&0x02?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_C_GPIO_Port, LED7SEG_C_Pin, AnodeNumber[num]&0x04?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_D_GPIO_Port, LED7SEG_D_Pin, AnodeNumber[num]&0x08?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_E_GPIO_Port, LED7SEG_E_Pin, AnodeNumber[num]&0x10?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_F_GPIO_Port, LED7SEG_F_Pin, AnodeNumber[num]&0x20?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_G_GPIO_Port, LED7SEG_G_Pin, AnodeNumber[num]&0x40?SET:RESET);

}
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	void setLedOnWay1(char *led) {
	  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, led=="RED"?RESET:SET);
	  HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, led=="YELLOW"?RESET:SET);
	  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, led=="GREEN"?RESET:SET);
	}
	void setLedOnWay2(char *led) {
	  HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, led=="RED"?RESET:SET);
	  HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, led=="YELLOW"?RESET:SET);
	  HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, led=="GREEN"?RESET:SET);
	}
   int state = 0, counter = 300, led7_counter =0;;
   while (1)
   {
	   if(led7_counter >=10) led7_counter=0;
	   display7SEG(led7_counter);
	  switch(state) {
	  case 0:					//RED1_GREEN2 : 3s
		  setLedOnWay1("RED");
		  setLedOnWay2("GREEN");
		  if(counter <=0) {
			  state = 1;
			  counter = 200;
		  }
		  break;
	  case 1:					//RED1_YELLOW2 : 2s
		  setLedOnWay1("RED");
		  setLedOnWay2("YELLOW");
		  if(counter <=0) {
			  state = 2;
			  counter = 300;
		  }
		  break;
	  case 2:					//GREEN1_RED2 : 3s
		  setLedOnWay1("GREEN");
		  setLedOnWay2("RED");
		  if(counter <=0) {
			  state = 3;
			  counter = 200;
		  }
		  break;
	  case 3:					//YELLOW1_RED2 : 2s
		  setLedOnWay1("YELLOW");
		  setLedOnWay2("RED");
		  if(counter <=0) {
			  state = 0;
			  counter = 300;
		  }
		  break;
	  }
	  led7_counter++;
	  counter--;
	  HAL_Delay(10);
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED2_Pin|LED_YELLOW2_Pin|LED_GREEN2_Pin|LED_RED1_Pin
                          |LED_YELLOW1_Pin|LED_GREEN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED7SEG_A_Pin|LED7SEG_B_Pin|LED7SEG_C_Pin|LED7SEG_D_Pin
                          |LED7SEG_E_Pin|LED7SEG_F_Pin|LED7SEG_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED2_Pin LED_YELLOW2_Pin LED_GREEN2_Pin LED_RED1_Pin
                           LED_YELLOW1_Pin LED_GREEN1_Pin */
  GPIO_InitStruct.Pin = LED_RED2_Pin|LED_YELLOW2_Pin|LED_GREEN2_Pin|LED_RED1_Pin
                          |LED_YELLOW1_Pin|LED_GREEN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED7SEG_A_Pin LED7SEG_B_Pin LED7SEG_C_Pin LED7SEG_D_Pin
                           LED7SEG_E_Pin LED7SEG_F_Pin LED7SEG_G_Pin */
  GPIO_InitStruct.Pin = LED7SEG_A_Pin|LED7SEG_B_Pin|LED7SEG_C_Pin|LED7SEG_D_Pin
                          |LED7SEG_E_Pin|LED7SEG_F_Pin|LED7SEG_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
