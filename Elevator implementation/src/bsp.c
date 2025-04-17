//============================================================================
// Product: DPP example, STM32F4-Discovery board, QV kernel
// Last updated for version 8.0.0
// Last updated on  2024-09-18
//
//                   Q u a n t u m  L e a P s
//                   ------------------------
//                   Modern Embedded Software
//
// Copyright (C) 2005 Quantum Leaps, LLC. <state-machine.com>
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
#include "main.h"                 // main header
#include "bsp.h"                 // Board Support Package
#include "elevator.h"            // Elevator specifics
#include <stdio.h>


#include "stm32f4xx.h"  // CMSIS-compliant header file for the MCU used
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h" // if using USART
#include "stm32f4xx_hal_gpio.h"  // for GPIO
#include "stm32f4xx_hal_rcc.h"   // for RCC functions (usually included via main HAL)
#include "usb_device.h"
// add other drivers if necessary...

Q_DEFINE_THIS_FILE  // define the name of this file for assertions

// Local-scope defines -----------------------------------------------------
#define LED_GPIO_PORT     GPIOD
#define LED_GPIO_CLK      RCC_AHB1Periph_GPIOD


#define GREEN_PIN          GPIO_PIN_12
#define ORANGE_PIN         GPIO_PIN_13
#define RED_PIN            GPIO_PIN_14
#define BLUE_PIN           GPIO_PIN_15

#define LED_GPIO_PORT      GPIOD
#define BTN_GPIO_PORT      GPIOA
#define BTN_B1             GPIO_PIN_0



#define BTN_GPIO_PORT     GPIOA
#define BTN_GPIO_CLK      RCC_AHB1Periph_GPIOA

// USART Constants

#ifdef Q_SPY
    static QSTimeCtr QS_tickTime_;
    static QSTimeCtr QS_tickPeriod_;

    // QSpy source IDs
    static QSpyId const l_SysTick_Handler = { 0U };

    enum AppRecords { // application-specific trace records
        PHILO_STAT = QS_USER,
        PAUSED_STAT,
        CONTEXT_SW,
    };

#endif

//============================================================================


//............................................................................
void orangeOn()  { HAL_GPIO_WritePin(LED_GPIO_PORT, ORANGE_PIN, GPIO_PIN_SET); }
void orangeOff() { HAL_GPIO_WritePin(LED_GPIO_PORT, ORANGE_PIN, GPIO_PIN_RESET); }

void greenOn()   { HAL_GPIO_WritePin(LED_GPIO_PORT, GREEN_PIN, GPIO_PIN_SET); }
void greenOff()  { HAL_GPIO_WritePin(LED_GPIO_PORT, GREEN_PIN, GPIO_PIN_RESET); }

void redOn()     { HAL_GPIO_WritePin(LED_GPIO_PORT, RED_PIN, GPIO_PIN_SET); }
void redOff()    { HAL_GPIO_WritePin(LED_GPIO_PORT, RED_PIN, GPIO_PIN_RESET); }

void blueOn()    { HAL_GPIO_WritePin(LED_GPIO_PORT, BLUE_PIN, GPIO_PIN_SET); }
void blueOff()   { HAL_GPIO_WritePin(LED_GPIO_PORT, BLUE_PIN, GPIO_PIN_RESET); }

//.........................................................................
uint8_t already_requested(uint16_t level){
    QF_CRIT_STAT;
    QF_CRIT_ENTRY(); // lock the interrupts
    uint8_t ret = (requests & (1U<<level));
    QF_CRIT_EXIT(); // unlock the interrupts
    return ret;
}
//.........................................................................
void register_request(uint16_t level){
    static const QEvt ResumeEvt = QEVT_INITIALIZER(RESUME_SIG);
    if (registry_Empyt()){
        QACTIVE_POST(AOElevator, &ResumeEvt, (void)0U );
    }
    QF_CRIT_STAT;
    QF_CRIT_ENTRY(); // lock the interrupts
    requests |= (1U<<level);
    QF_CRIT_EXIT(); // unlock the interrupts


}
//.........................................................................
void unregister_request(uint16_t level){
    uint8_t assetion = already_requested(level);
    Q_ASSERT(assetion);
    QF_CRIT_STAT;
    QF_CRIT_ENTRY(); // lock the interrupts
    requests &= ~(1U<<level);
    QF_CRIT_EXIT(); // unlock the interrupts
}
//.........................................................................
uint8_t registry_Empyt(){
    QF_CRIT_STAT;
    QF_CRIT_ENTRY(); // lock the interrupts
    uint8_t ret = (requests == 0U);
    QF_CRIT_EXIT(); // unlock the interrupts
    return ret;
}

//..........................................................................
uint16_t getLowestRequest(uint16_t base){
    QF_CRIT_STAT;
    QF_CRIT_ENTRY(); // lock the interrupts
    uint16_t ret = 0U;
    for (uint16_t i = base; i < MAX_LEVELS; ++i){
        if (requests & (1U<<i)){
            ret = i;
            break;
        }
    }

    QF_CRIT_EXIT(); // unlock the interrupts
    return ret;
}

//.........................................................................

uint16_t getHighestRequest(uint16_t base){
    QF_CRIT_STAT;
    QF_CRIT_ENTRY(); // lock the interrupts
    uint16_t ret = MAX_LEVELS;
    for (uint16_t i = base; i > 0U; --i){
        if (requests & (1U<<i)){
            ret = i;
            break;
        }
    }

    QF_CRIT_EXIT(); // unlock the interrupts
    return ret;
}


//..........................................................................





// ISRs used in the application ==========================================
void SysTick_Handler(void); // prototype
void SysTick_Handler(void) {
    HAL_IncTick();

    QTIMEEVT_TICK_X(0U, &l_SysTick_Handler); // time events at rate 0

#ifdef Q_SPY
    tmp = SysTick->CTRL; // clear CTRL_COUNTFLAG
    QS_tickTime_ += QS_tickPeriod_; // account for the clock rollover
#endif

    QV_ARM_ERRATUM_838869();
}


//............................................................................
#ifdef Q_SPY
// ISR for receiving bytes from the QSPY Back-End
// NOTE: This ISR is "QF-unaware" meaning that it does not interact with
// the QF/QK and is not disabled. Such ISRs don't need to call
// QK_ISR_ENTRY/QK_ISR_EXIT and they cannot post or publish events.

void USART2_IRQHandler(void); // prototype
void USART2_IRQHandler(void) { // used in QS-RX (kernel UNAWARE interrutp)
    // is RX register NOT empty?
    if ((USART2->SR & USART_SR_RXNE) != 0U) {
        uint32_t b = USART2->DR;
        QS_RX_PUT(b);
    }

    QV_ARM_ERRATUM_838869();
}
#endif // Q_SPY

//............................................................................
#ifdef QF_ON_CONTEXT_SW
// NOTE: the context-switch callback is called with interrupts DISABLED
void QF_onContextSw(QActive *prev, QActive *next) {
    QS_BEGIN_INCRIT(CONTEXT_SW, 0U) // in critical section!
        QS_OBJ(prev);
        QS_OBJ(next);
    QS_END_INCRIT()
}
#endif // QF_ON_CONTEXT_SW

//============================================================================
// BSP functions...
//............................................................................

//............................................................................
void BSP_init(void) {
    Q_ASSERT(MAX_LEVELS <= 16U);

    // Configure the MPU to prevent NULL-pointer dereferencing ...
    MPU->RBAR = 0x0U                          // base address (NULL)
                | MPU_RBAR_VALID_Msk          // valid region
                | (MPU_RBAR_REGION_Msk & 7U); // region #7
    MPU->RASR = (7U << MPU_RASR_SIZE_Pos)     // 2^(7+1) region
                | (0x0U << MPU_RASR_AP_Pos)   // no-access region
                | MPU_RASR_ENABLE_Msk;        // region enable
    MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk       // enable background region
                | MPU_CTRL_ENABLE_Msk;        // enable the MPU
    __ISB();
    __DSB();

    // NOTE: SystemInit() has been already called from the startup code
    // but SystemCoreClock needs to be updated
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config(); 
    //configure the system clock update
    // SystemCoreClockUpdate();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USB_DEVICE_Init();

    // Initialize thr port for the LEDs
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = ORANGE_PIN | GREEN_PIN | RED_PIN | BLUE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(LED_GPIO_PORT, ORANGE_PIN | GREEN_PIN | RED_PIN | BLUE_PIN, GPIO_PIN_RESET);


    // initialize the QS software tracing...
    if (!QS_INIT((void *)0)) {
        Q_ERROR();
    }

    // dictionaries...
    QS_OBJ_DICTIONARY(&l_SysTick_Handler);
    QS_USR_DICTIONARY(PHILO_STAT);
    QS_USR_DICTIONARY(PAUSED_STAT);
    QS_USR_DICTIONARY(CONTEXT_SW);

    QS_ONLY(produce_sig_dict());

    // setup the QS filters...
    QS_GLB_FILTER(QS_ALL_RECORDS);   // all records
    QS_GLB_FILTER(-QS_QF_TICK);      // exclude the clock tick
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
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
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
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
    }
    
    /**
     * @brief GPIO Initialization Function
     * @param None
     * @retval None
     */
    void MX_GPIO_Init(void)
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
  

//............................................................................
void BSP_start(void) {
    // initialize event pools
    // HAL_ResumeTick(); // resume the SysTick interrupt
    static QF_MPOOL_EL(requestEvt) smlPoolSto[MAX_LEVELS];
    QF_poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

    // static QF_MPOOL_EL(printDataEvt) mediumlPoolSto[MAX_LEVELS];
    // QF_poolInit(mediumlPoolSto, sizeof(mediumlPoolSto), sizeof(mediumlPoolSto[0]));
        static QEvtPtr elevatorQueueSto[MAX_LEVELS];
    Elevator_Ctor();
    QActive_start(AOElevator,
        4U,                // QP prio. of the Elevator I dont know why we skip the first 2
        elevatorQueueSto,               // event queue storage
        Q_DIM(elevatorQueueSto),        // queue length [events]
        (void *)0, 0U,               // no stack storage
        (void *)0);                  // no initialization param
}

// Error handler and ISRs...

Q_NORETURN Q_onError(char const * const module, int_t const id) {
    // NOTE: this implementation of the assertion handler is intended only
    // for debugging and MUST be changed for deployment of the application
    // (assuming that you ship your production code with assertions enabled).
    Q_UNUSED_PAR(module);
    Q_UNUSED_PAR(id);
    QS_ASSERTION(module, id, 10000U);

#ifndef NDEBUG
    // for debugging, hang on in an endless loop...
    for (;;) {
    }
#endif

    NVIC_SystemReset();
}
//............................................................................
void assert_failed(char const * const module, int_t const id); // prototype
void assert_failed(char const * const module, int_t const id) {
    Q_onError(module, id);
}

//.............................................................................
void Error_Handler(void) {
    // NOTE: this implementation of the error handler is intended only
    // for debugging and MUST be changed for deployment of the application
    // (assuming that you ship your production code with assertions enabled).
    Q_onError("Error_Handler", 10000);
}
//.............................................................................
// QF callbacks...
void QF_onStartup(void) {
    // set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate
    __enable_irq(); 
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    // assign all priority bits for preemption-prio. and none to sub-prio.
    NVIC_SetPriorityGrouping(0U);

    // set priorities of ALL ISRs used in the system, see NOTE1
    // HAL_NVIC_SetPriority(USART2_IRQn, QF_AWARE_ISR_CMSIS_PRI+1U , 0); 

    HAL_NVIC_SetPriority(OTG_FS_IRQn, QF_AWARE_ISR_CMSIS_PRI + 1U, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
    HAL_NVIC_SetPriority(SysTick_IRQn,   QF_AWARE_ISR_CMSIS_PRI + 2U, 0);
    HAL_NVIC_EnableIRQ(SysTick_IRQn);

    // ...........................................................

    // enable IRQs...
#ifdef Q_SPY
    NVIC_EnableIRQ(USART2_IRQn); // USART2 interrupt used for QS-RX
#endif
}
//............................................................................
void QF_onCleanup(void) {
}
//............................................................................
void QV_onIdle(void) { // CATION: called with interrupts DISABLED, see NOTE0

    // // toggle an LED on and then off (not enough LEDs, see NOTE02)
    // LED_GPIO_PORT->BSRRL = BLUE_PIN; // turn LED on
    // __NOP(); // wait a little to actually see the LED glow
    // __NOP();
    // __NOP();
    // __NOP();
    // LED_GPIO_PORT->BSRRH = BLUE_PIN; // turn LED off

#ifdef Q_SPY
    QF_INT_ENABLE();
    QS_rxParse();  // parse all the received bytes

    if ((USART2->SR & USART_FLAG_TXE) != 0) { // TXE empty?
        QF_INT_DISABLE();
        uint16_t b = QS_getByte();
        QF_INT_ENABLE();

        if (b != QS_EOD) {  // not End-Of-Data?
            USART2->DR = b; // put into the DR register
        }
    }
#elif defined NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M MCU.
    //
    // !!!CAUTION!!!
    // The WFI instruction stops the CPU clock, which unfortunately disables
    // the JTAG port, so the ST-Link debugger can no longer connect to the
    // board. For that reason, the call to __WFI() has to be used with CAUTION.
    //
    // NOTE: If you find your board "frozen" like this, strap BOOT0 to VDD and
    // reset the board, then connect with ST-Link Utilities and erase the part.
    // The trick with BOOT(0) is that it gets the part to run the System Loader
    // instead of your broken code. When done disconnect BOOT0, and start over.
    //
    QV_CPU_SLEEP(); // atomically go to sleep and enable interrupts
    QF_INT_ENABLE(); // for now, just enable interrupts
#else
    QF_INT_ENABLE(); // just enable interrupts
#endif
}

//============================================================================
// QS callbacks...
#ifdef Q_SPY

//............................................................................
#define __DIV(__PCLK, __BAUD)       (((__PCLK / 4) *25)/(__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100)
#define __DIVFRAQ(__PCLK, __BAUD)   \
    (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100)) \
        * 16 + 50) / 100)
#define __USART_BRR(__PCLK, __BAUD) \
    ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0F))

// USART2 pins PA.2 and PA.3
#define USART2_TX_PIN 2U
#define USART2_RX_PIN 3U

//............................................................................
uint8_t QS_onStartup(void const *arg) {
    Q_UNUSED_PAR(arg);

    static uint8_t qsTxBuf[2*1024]; // buffer for QS-TX channel
    QS_initBuf(qsTxBuf, sizeof(qsTxBuf));

    static uint8_t qsRxBuf[100];    // buffer for QS-RX channel
    QS_rxInitBuf(qsRxBuf, sizeof(qsRxBuf));

    // enable peripheral clock for USART2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // GPIOA clock enable
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // GPIOA Configuration:  USART2 TX on PA2 and RX on PA3
    GPIO_InitTypeDef GPIO_struct;
    GPIO_struct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_struct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_struct.GPIO_OType = GPIO_OType_PP;
    GPIO_struct.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOA, &GPIO_struct);

    // Connect USART2 pins to AF2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); // TX = PA2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); // RX = PA3

    USART_InitTypeDef USART_struct;
    USART_struct.USART_BaudRate = 115200;
    USART_struct.USART_WordLength = USART_WordLength_8b;
    USART_struct.USART_StopBits = USART_StopBits_1;
    USART_struct.USART_Parity = USART_Parity_No;
    USART_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_struct);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // enable RX interrupt
    USART_Cmd(USART2, ENABLE); // enable USART2

    QS_tickPeriod_ = SystemCoreClock / BSP_TICKS_PER_SEC;
    QS_tickTime_ = QS_tickPeriod_; // to start the timestamp at zero

    return 1U; // return success
}
//............................................................................
void QS_onCleanup(void) {
}
//............................................................................
QSTimeCtr QS_onGetTime(void) { // NOTE: invoked with interrupts DISABLED
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U) { // not set?
        return QS_tickTime_ - (QSTimeCtr)SysTick->VAL;
    }
    else { // the rollover occurred, but the SysTick_ISR did not run yet
        return QS_tickTime_ + QS_tickPeriod_ - (QSTimeCtr)SysTick->VAL;
    }
}
//............................................................................
// NOTE:
// No critical section in QS_onFlush() to avoid nesting of critical sections
// in case QS_onFlush() is called from Q_onError().
void QS_onFlush(void) {
    for (;;) {
        uint16_t b = QS_getByte();
        if (b != QS_EOD) {
            while ((USART2->SR & USART_FLAG_TXE) == 0U) { // while TXE not empty
            }
            USART2->DR = b; // put into the DR register
        }
        else {
            break;
        }
    }
}
//............................................................................
void QS_onReset(void) {
    NVIC_SystemReset();
}
//............................................................................
void QS_onCommand(uint8_t cmdId,
                  uint32_t param1, uint32_t param2, uint32_t param3)
{
    Q_UNUSED_PAR(cmdId);
    Q_UNUSED_PAR(param1);
    Q_UNUSED_PAR(param2);
    Q_UNUSED_PAR(param3);
}

#endif // Q_SPY
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

//============================================================================
// NOTE0:
// The QV_onIdle() callback is called with interrupts disabled, because the
// determination of the idle condition might change by any interrupt posting
// an event. QV_onIdle() must internally enable interrupts, ideally
// atomically with putting the CPU to the power-saving mode.
//
// NOTE1:
// The QF_AWARE_ISR_CMSIS_PRI constant from the QF port specifies the highest
// ISR priority that is disabled by the QF framework. The value is suitable
// for the NVIC_SetPriority() CMSIS function.
//
// Only ISRs prioritized at or below the QF_AWARE_ISR_CMSIS_PRI level (i.e.,
// with the numerical values of priorities equal or higher than
// QF_AWARE_ISR_CMSIS_PRI) are allowed to call the QV_ISR_ENTRY/
// QV_ISR_ENTRY macros or any other QF/QV services. These ISRs are
// "QF-aware".
//
// Conversely, any ISRs prioritized above the QF_AWARE_ISR_CMSIS_PRI priority
// level (i.e., with the numerical values of priorities less than
// QF_AWARE_ISR_CMSIS_PRI) are never disabled and are not aware of the kernel.
// Such "QF-unaware" ISRs cannot call ANY QF/QV services. In particular they
// can NOT call the macros QV_ISR_ENTRY/QV_ISR_ENTRY. The only mechanism
// by which a "QF-unaware" ISR can communicate with the QF framework is by
// triggering a "QF-aware" ISR, which can post/publish events.
//
// NOTE2:
// The User LED is used to visualize the idle loop activity. The brightness
// of the LED is proportional to the frequency of the idle loop.
// Please note that the LED is toggled with interrupts locked, so no interrupt
// execution time contributes to the brightness of the User LED.
//

