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
// #include "dpp.h"                 // DPP Application interface
#include "bsp.h"                 // Board Support Package
#include "elevator.h"            // Elevator specifics


#include "stm32f4xx.h"  // CMSIS-compliant header file for the MCU used
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
// #include "stm32f4xx.h"  // CMSIS-compliant header file for the MCU used
// #include "stm32f4xx_exti.h"
// #include "stm32f4xx_gpio.h"
// #include "stm32f4xx_rcc.h"
// #include "stm32f4xx_usart.h"

// #define LED_GPIO_PORT     GPIOD
// #define LED_GPIO_CLK      RCC_AHB1Periph_GPIOD

// #define GREEN_PIN          GPIO_Pin_12
// #define ORANGE_PIN          GPIO_Pin_13
// #define RED_PIN          GPIO_Pin_14
// #define BLUE_PIN          GPIO_Pin_15

// #define BTN_GPIO_PORT     GPIOA
// #define BTN_GPIO_CLK      RCC_AHB1Periph_GPIOA
// #define BTN_B1            GPIO_Pin_0

// add other drivers if necessary...

Q_DEFINE_THIS_FILE  // define the name of this file for assertions

// Local-scope defines -----------------------------------------------------
#define LED_GPIO_PORT     GPIOD
#define LED_GPIO_CLK      RCC_AHB1Periph_GPIOD

#define DOWN_PIN           GPIO_Pin_2
#define INTERUPT_PIN       GPIO_Pin_3
#define GREEN_PIN          GPIO_Pin_12
#define ORANGE_PIN         GPIO_Pin_13
#define RED_PIN            GPIO_Pin_14
#define BLUE_PIN           GPIO_Pin_15


#define BTN_GPIO_PORT     GPIOA
#define BTN_GPIO_CLK      RCC_AHB1Periph_GPIOA
#define BTN_B1            GPIO_Pin_0

static uint32_t l_rndSeed;

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
// request function for when buttons are pressed
void request(uint16_t SIG){
    volatile uint32_t rad = BSP_random();
    rad %= (uint32_t) MAX_LEVELS;

    if(rad){
        requestEvt * RequestEve = Q_NEW(requestEvt ,SIG);
        RequestEve->level = rad;

        if (!already_requested(rad)){
            register_request(rad);
            QACTIVE_POST(AOElevator, (QEvtPtr)RequestEve, (void)0U );
        }

        rad %= (MAX_LEVELS / (uint32_t)2);
        if(rad){
            RequestEve = Q_NEW(requestEvt ,SIG);
            RequestEve->level = rad;

            if (!already_requested(rad)){
                register_request(rad);
                QACTIVE_POST(AOElevator, (QEvtPtr)RequestEve, (void)0U );
            }
            rad %= (uint32_t)2;

            if(rad){
                RequestEve = Q_NEW(requestEvt ,SIG);
                RequestEve->level = rad;
                if (!already_requested(rad)){
                    register_request(rad);
                    QACTIVE_POST(AOElevator, (QEvtPtr)RequestEve, (void)0U );
                }
            }
        }
    }
}


//..........................................................................


// ISRs used in the application ==========================================
void SysTick_Handler(void); // prototype
void SysTick_Handler(void) {

    QTIMEEVT_TICK_X(0U, &l_SysTick_Handler); // time events at rate 0

    // Perform the debouncing of buttons. The algorithm for debouncing
    // adapted from the book "Embedded Systems Dictionary" by Jack Ganssle
    // and Michael Barr, page 71.
    //
    // state of the button debouncing
    static struct {
        uint32_t depressed;
        uint32_t previous;
    } buttons = { 0U, 0U };

    uint32_t current = BTN_GPIO_PORT->IDR; // read BTN GPIO
    uint32_t tmp = buttons.depressed; // save the depressed buttons
    buttons.depressed |= (buttons.previous & current); // set depressed
    buttons.depressed &= (buttons.previous | current); // clear released
    buttons.previous   = current; // update the history
    tmp ^= buttons.depressed;     // changed debounced depressed
    current = buttons.depressed;

    if ((tmp & BTN_B1) != 0U) { // debounced B1 state changed?
        if ((current & BTN_B1) != 0U) { // is B1 depressed?
            static QEvt const enterEvt = QEVT_INITIALIZER(ENTER_REQUEST_SIG);
            QACTIVE_POST(AORequestor, &enterEvt, (void)0 );
        }
        else { // the button is released
            static QEvt const exitEvt = QEVT_INITIALIZER(EXIT_REQUEST_SIG);
            QACTIVE_POST(AORequestor, &exitEvt, (void)0 );
        }
        // if ((current & DOWN_PIN) != 0U) { // is B1 depressed?
        //     static QEvt const dowEvt = QEVT_INITIALIZER(DOWN_REQUEST_SIG);
        //     QACTIVE_POST(AORequestor, &dowEvt, (void)0 );
        // }
        if ((current & INTERUPT_PIN) != 0U) { // is B1 depressed?
            static QEvt const intPress = QEVT_INITIALIZER(CLOSE_INTERRUPT_SIG);
            QACTIVE_POST(AOElevator, &intPress, (void)0 );
        }
    }

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
    SystemCoreClockUpdate();

    // NOTE The VFP (Floating Point Unit) unit is configured by QK-port

    // Initialize thr port for the LEDs
    RCC_AHB1PeriphClockCmd(LED_GPIO_CLK , ENABLE);

    // GPIO Configuration for the LEDs...
    GPIO_InitTypeDef GPIO_struct;
    GPIO_struct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_struct.GPIO_OType = GPIO_OType_PP;
    GPIO_struct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_struct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_struct.GPIO_Pin = ORANGE_PIN;
    GPIO_Init(LED_GPIO_PORT, &GPIO_struct);
    LED_GPIO_PORT->BSRRH = ORANGE_PIN; // turn LED off

    GPIO_struct.GPIO_Pin = GREEN_PIN;
    GPIO_Init(LED_GPIO_PORT, &GPIO_struct);
    LED_GPIO_PORT->BSRRH = GREEN_PIN; // turn LED off

    GPIO_struct.GPIO_Pin = RED_PIN;
    GPIO_Init(LED_GPIO_PORT, &GPIO_struct);
    LED_GPIO_PORT->BSRRH = RED_PIN; // turn LED off

    GPIO_struct.GPIO_Pin = BLUE_PIN;
    GPIO_Init(LED_GPIO_PORT, &GPIO_struct);
    LED_GPIO_PORT->BSRRH = BLUE_PIN; // turn LED off



    // Initialize thr port for Button
    RCC_AHB1PeriphClockCmd(BTN_GPIO_CLK , ENABLE);

    // GPIO Configuration for the Button...
    GPIO_struct.GPIO_Pin   = BTN_B1;
    GPIO_struct.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_struct.GPIO_OType = GPIO_OType_PP;
    GPIO_struct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BTN_GPIO_PORT, &GPIO_struct);

    GPIO_struct.GPIO_Pin = INTERUPT_PIN;
    GPIO_Init(BTN_GPIO_PORT, &GPIO_struct);

    GPIO_struct.GPIO_Pin = DOWN_PIN;
    GPIO_Init(BTN_GPIO_PORT, &GPIO_struct);

    BSP_randomSeed(1234U); // seed the random number generator

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
//............................................................................
void BSP_start(void) {
    // initialize event pools
    static QF_MPOOL_EL(requestEvt) smlPoolSto[MAX_LEVELS];
    QF_poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

    // initialize publish-subscribe
    // static QSubscrList subscrSto[MAX_PUB_SIG];   // not used in my application
    // QActive_psInit(subscrSto, Q_DIM(subscrSto));

    // instantiate and start AOs/threads...

    static QEvtPtr RequestorQueueSto[4];
    Requestor_Ctor();
    QActive_start(AORequestor,
        3U,                // QP prio. of the Requestor I dont know why we skip the first 2
        RequestorQueueSto,               // event queue storage
        Q_DIM(RequestorQueueSto),        // queue length [events]
        (void *)0, 0U,               // no stack storage
        (void *)0);                  // no initialization param


    static QEvtPtr elevatorQueueSto[MAX_LEVELS];
    Elevator_Ctor();
    QActive_start(AOElevator,
        4U,                // QP prio. of the Elevator I dont know why we skip the first 2
        elevatorQueueSto,               // event queue storage
        Q_DIM(elevatorQueueSto),        // queue length [events]
        (void *)0, 0U,               // no stack storage
        (void *)0);                  // no initialization param
}
//............................................................................
void orangeOn(){
    LED_GPIO_PORT->BSRRL = ORANGE_PIN;
}

void orangeOff(){
    LED_GPIO_PORT->BSRRH = ORANGE_PIN;
}

void greenOn(){
    LED_GPIO_PORT->BSRRL = GREEN_PIN;
}

void greenOff(){
    LED_GPIO_PORT->BSRRH = GREEN_PIN;
}

void redOn(){
    LED_GPIO_PORT->BSRRL = RED_PIN;
}

void redOff(){
    LED_GPIO_PORT->BSRRH = RED_PIN;
}

void blueOn(){
    LED_GPIO_PORT->BSRRL = BLUE_PIN;
}

void blueOff(){
    LED_GPIO_PORT->BSRRH = BLUE_PIN;
}
//.........................................................................

// void BSP_displayPhilStat(uint8_t n, char const *stat) {
//     Q_UNUSED_PAR(n);

//     if (stat[0] == 'h') {
//         LED_GPIO_PORT->BSRRL = ORANGE_PIN; // turn LED on
//     }
//     else {
//         LED_GPIO_PORT->BSRRH = ORANGE_PIN; // turn LED off
//     }
//     if (stat[0] == 'e') {
//         LED_GPIO_PORT->BSRRL = RED_PIN; // turn LED on
//     }
//     else {
//         LED_GPIO_PORT->BSRRH = RED_PIN; // turn LED off
//     }

//     // app-specific trace record...
//     QS_BEGIN_ID(PHILO_STAT, AO_Table->prio)
//         QS_U8(1, n);  // Philosopher number
//         QS_STR(stat); // Philosopher status
//     QS_END()
// }

//............................................................................

void BSP_randomSeed(uint32_t seed) {
    l_rndSeed = seed;
}
//............................................................................
uint32_t BSP_random(void) { // a very cheap pseudo-random-number generator

    // Some flating point code is to exercise the FPU...
    float volatile x = 3.1415926F;
    x = x + 2.7182818F;

    // "Super-Duper" Linear Congruential Generator (LCG)
    // LCG(2^32, 3*7*11*13*23, 0, seed)
    //
    uint32_t rnd = l_rndSeed * (3U*7U*11U*13U*23U);
    l_rndSeed = rnd; // set for the next time

    return (rnd >> 8U);


}
//............................................................................
// QF callbacks...
void QF_onStartup(void) {
    // set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    // assign all priority bits for preemption-prio. and none to sub-prio.
    NVIC_SetPriorityGrouping(0U);

    // set priorities of ALL ISRs used in the system, see NOTE1
    NVIC_SetPriority(USART2_IRQn,    0U); // kernel UNAWARE interrupt
    NVIC_SetPriority(SysTick_IRQn,   QF_AWARE_ISR_CMSIS_PRI + 1U);
    // ...

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

