//============================================================================
// APP example
// Last updated for version 7.3.0
// Last updated on  2023-08-09
//
//                   Q u a n t u m  L e a P s
//                   ------------------------
//                   Modern Embedded Software
//
// Copyright (C) 2005 Quantum Leaps, LLC. <www.state-machine.com>
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alternatively, this program may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GNU General Public License and are specifically designed for
// licensees interested in retaining the proprietary status of their code.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <www.gnu.org/licenses/>.
//
// Contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//============================================================================
#include "qpc.h"                 // QP/C real-time embedded framework
// #include "bsp.h"                 // Board Support Package
#include "elevator.h"
#include <stdio.h>             // standard I/O for printf()
#include "main.h"
#include "stm32f4xx.h"  // CMSIS-compliant header file for the MCU used
#include "stm32f4xx_hal.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "string.h"
//............................................................................
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

static void MX_GPIO_Init(void)
    {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    
    /* USER CODE END MX_GPIO_Init_1 */
    
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
    
    /*Configure GPIO pin : PC0 */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    /* USER CODE BEGIN MX_GPIO_Init_2 */
    
    /* USER CODE END MX_GPIO_Init_2 */
    }
  

int main() {
    // QF_init();       // initialize the framework and the underlying RT kernel
    // BSP_init();      // initialize the BSP
    // BSP_start();     // start the AOs/Threads
    HAL_Init();
    // printf("Heloo World!\n");
    // return QF_run(); // run the QF application
    /* Configure the system clock */
    SystemClock_Config(); 
    //configure the system clock update
    // SystemCoreClockUpdate();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USB_DEVICE_Init();
    char* data = "Jordan JOJO\n";
    /* USER CODE END 2 */
  
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
      /* USER CODE END WHILE */
        CDC_Transmit_FS((uint8_t*) data, (uint16_t) strlen(data));
      /* USER CODE BEGIN 3 */
    }
}

// void SystemClock_Config(void)
//     {
//     RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//     RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    
//     /** Configure the main internal regulator output voltage
//      */
//     __HAL_RCC_PWR_CLK_ENABLE();
//     __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    
//     /** Initializes the RCC Oscillators according to the specified parameters
//      * in the RCC_OscInitTypeDef structure.
//      */
//     RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//     RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//     RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//     RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//     RCC_OscInitStruct.PLL.PLLM = 8;
//     RCC_OscInitStruct.PLL.PLLN = 336;
//     RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//     RCC_OscInitStruct.PLL.PLLQ = 7;
//     if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//     {
//         Error_Handler();
//     }
    
//     /** Initializes the CPU, AHB and APB buses clocks
//      */
//     RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                                 |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//     RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//     RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//     RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//     RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    
//     if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
//     {
//         Error_Handler();
//     }
//     }
    