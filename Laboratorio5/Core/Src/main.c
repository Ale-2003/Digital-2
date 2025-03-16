/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
uint16_t state = 0;
uint16_t nextstate = 1;
uint8_t Jugador1 = 0;
uint8_t Jugador2 = 0;
uint8_t Ganador = 0;
int numero[6] = {0, 1, 2, 4, 8, 15};
uint8_t bloqueoJ1 = 0;
uint8_t bloqueoJ2 = 0;
uint8_t display7Seg[11] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
	0b00000000
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void No_Jugar(void);
void Si_Jugar(void);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
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
  while (1) {
	  switch (state) {
	  	  case 0: No_Jugar(); nextstate = 1;break;
	      case 1: Si_Jugar(); nextstate = 0; break;
	      default: state = 0; break;
	  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A_Pin|B_Pin|L2J2_Pin|L1J2_Pin
                          |L4J1_Pin|L1J1_Pin|C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, G_Pin|D_Pin|F_Pin|E_Pin
                          |L3J1_Pin|L4J2_Pin|L3J2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(L2J1_GPIO_Port, L2J1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : J1_Pin J2_Pin Iniciar_Pin */
  GPIO_InitStruct.Pin = J1_Pin|J2_Pin|Iniciar_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : A_Pin B_Pin L2J2_Pin L1J2_Pin
                           L4J1_Pin L1J1_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|L2J2_Pin|L1J2_Pin
                          |L4J1_Pin|L1J1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : G_Pin D_Pin F_Pin E_Pin */
  GPIO_InitStruct.Pin = G_Pin|D_Pin|F_Pin|E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : L2J1_Pin */
  GPIO_InitStruct.Pin = L2J1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(L2J1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : C_Pin */
  GPIO_InitStruct.Pin = C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(C_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : L3J1_Pin L4J2_Pin L3J2_Pin */
  GPIO_InitStruct.Pin = L3J1_Pin|L4J2_Pin|L3J2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Mascara(uint8_t number1, uint8_t number2);
void displaySegments(uint8_t value);

#define DEBOUNCE_DELAY 200 // Tiempo de antirrebote en milisegundos

uint32_t lastDebounceTimeJ1 = 0;
uint32_t lastDebounceTimeJ2 = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    uint32_t currentTime = HAL_GetTick();

    if (GPIO_Pin == Iniciar_Pin) {
        if (state == 0) {
            displaySegments(display7Seg[5]);
            HAL_Delay(500);
            displaySegments(display7Seg[4]);
            HAL_Delay(500);
            displaySegments(display7Seg[3]);
            HAL_Delay(500);
            displaySegments(display7Seg[2]);
            HAL_Delay(500);
            displaySegments(display7Seg[1]);
            HAL_Delay(500);
            displaySegments(display7Seg[0]);
            HAL_Delay(500);
        } else {
            Jugador1 = 0;
            Jugador2 = 0;
            Ganador = 0;
        }
        state = nextstate;
    }

    // Jugador 1 con antirrebote
    if (GPIO_Pin == J1_Pin) {
        if ((currentTime - lastDebounceTimeJ1) > DEBOUNCE_DELAY) {
            if (state != 0 && Jugador1 < 4) {
                Jugador1++;
                if (Jugador1 == 4) {
                    Ganador = 1;
                }
            }
            lastDebounceTimeJ1 = currentTime;
        }
    }

    // Jugador 2 con antirrebote
    if (GPIO_Pin == J2_Pin) {
        if ((currentTime - lastDebounceTimeJ2) > DEBOUNCE_DELAY) {
            if (state != 0 && Jugador2 < 4) {
                Jugador2++;
                if (Jugador2 == 4) {
                    Ganador = 2;
                }
            }
            lastDebounceTimeJ2 = currentTime;
        }
    }
}


//0b01101101, // 5
void displaySegments(uint8_t value) {
    // Segmento A - PA1
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (value & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // Segmento B - PA0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, (value & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // Segmento C - PA10
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, (value & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // Segmento D - PB3
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (value & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // Segmento E - PB5
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (value & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // Segmento F - PB4
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (value & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // Segmento G - PB10
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (value & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void No_Jugar(void){
	state = 0;
	Ganador = 0;
	Jugador1 = 0;
	Jugador2 = 0;
}

void Si_Jugar(void){
	Mascara(numero[Jugador1], numero[Jugador2]);
	if (Ganador == 2){
		displaySegments(display7Seg[2]);
		Jugador1 = 0;
		Mascara(numero[0], numero[5]);
	}
	if (Ganador == 1){
		displaySegments(display7Seg[1]);
		Jugador2 = 0;
		Mascara(numero[5], numero[0]);
	}
}


void Mascara(uint8_t number1, uint8_t number2) {
    // Configuramos cada bit por separado

    // Para number1
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, (number1 & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, (number1 & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (number1 & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (number1 & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // Para number2
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (number2 & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (number2 & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (number2 & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (number2 & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
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
