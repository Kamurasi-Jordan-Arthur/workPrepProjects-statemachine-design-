#include "qpc.h"
#include "bsp.h"
#include "pelican.h"

#include "safe_std.h" // portable "safe" <stdio.h>/<string.h> facilities
#include <stdlib.h>   // for exit()

Q_DEFINE_THIS_FILE

#ifdef Q_SPY
static uint8_t const l_QF_onClockTick = 0;
#endif

//............................................................................
//trfica call_backs

#define DISP_WIDTH 13
char car_SMS[DISP_WIDTH] = "RED";
char peds_SMS[DISP_WIDTH] = "DONT_WALK";

#define UPDATE_SCREEN() PRINTF_S("%s\t\t\t%s\n", car_SMS, peds_SMS)
#define CAR_SMS_UPDATE(x) strncpy(car_SMS, (x),DISP_WIDTH-2)
#define PEDS_SMS_UPDATE(x) strncpy(peds_SMS, (x), DISP_WIDTH-2)


void BSP_UP_DATE(){
    UPDATE_SCREEN();
}

void bspCarsGreen(){
    CAR_SMS_UPDATE("GREEN");
    UPDATE_SCREEN();
}
void bspCarsYellow(){
    CAR_SMS_UPDATE("YELLOW");
    UPDATE_SCREEN();
}
void bspCarsRed(){
    CAR_SMS_UPDATE("RED");
    UPDATE_SCREEN();
}

void bspWalk(){
    strcpy(peds_SMS, "WALK");
    UPDATE_SCREEN();
}
void bspDontWalk(){
    strcpy(peds_SMS, "DONT_WALK");
    UPDATE_SCREEN();
}
void bspDontWalkFlash(uint8_t flash){
    if(flash){
        PEDS_SMS_UPDATE("DONT-WALK");
        UPDATE_SCREEN();
    }else{
        PEDS_SMS_UPDATE("         ");
        UPDATE_SCREEN();
    }
}



//............................................................................
void BSP_init(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    if (QS_INIT((argc > 1) ? argv[1] : (void *)0) == 0U) {
        Q_ERROR();
    }
    QS_OBJ_DICTIONARY(&l_QF_onClockTick);

    // setup the QS filters...
    QS_GLB_FILTER(QS_ALL_RECORDS);
    QS_GLB_FILTER(-QS_QF_TICK);
}

inline void BSP_onKeyboardInput(uint8_t key) {
    (void) key;
    switch (key) {

        case 'P':                   //intetioanl fall though
        case 'p': {                 // ESC pressed?
            static QEvt const peds_button_press = QEVT_INITIALIZER(PEDS_SIG);
            QACTIVE_POST((QActive *)Pelican_AO, &peds_button_press, (void *)0);
            break;
        }
        case '1': {                 // 1 pressed?
            static QEvt const onEvt = QEVT_INITIALIZER(ON_SIG);
            QACTIVE_POST((QActive *)Pelican_AO, &onEvt, (void *)0);
            break;
        }
        case '0': {                 // 0 pressed?
            static QEvt const offEvt = QEVT_INITIALIZER(OFF_SIG);
            QACTIVE_POST((QActive *)Pelican_AO, &offEvt, (void *)0);
            break;
        }
        default: {
            PRINTF_S("%s\n" ,"###\t INVAILD_INPUT \t ###");
            WELCOME_SMS;
            break;
        }
    }
}

//............................................................................
void QF_onStartup(void) {
    QF_setTickRate(BSP_TICKS_PER_SEC, 30); // set the desired tick rate
    QF_consoleSetup();
}
//............................................................................
void QF_onCleanup(void) {
    PRINTF_S("\n%s\n", "Bye! Bye!");
    QF_consoleCleanup();
}
//............................................................................
void QF_onClockTick(void) {
    QTIMEEVT_TICK_X(0U, &l_QF_onClockTick); // perform QF clock tick processing

    QS_RX_INPUT(); // handle the QS-RX input
    QS_OUTPUT();   // handle the QS output

    int key = QF_consoleGetKey();
    if (key != 0) { // any key pressed?
        BSP_onKeyboardInput((uint8_t)key);
    }
}
//----------------------------------------------------------------------------
#ifdef Q_SPY // define QS callbacks

//............................................................................
//! callback function to execute user commands
void QS_onCommand(uint8_t cmdId,
                  uint32_t param1, uint32_t param2, uint32_t param3)
{
    switch (cmdId) {
       case 0U: {
           break;
       }
       default:
           break;
    }

    // unused parameters
    (void)param1;
    (void)param2;
    (void)param3;
}

#endif // Q_SPY
//----------------------------------------------------------------------------

//............................................................................
Q_NORETURN Q_onError(char const * const module, int_t const id) {
    FPRINTF_S(stderr, "ERROR in %s:%d", module, id);
    QF_onCleanup();
    exit(-1);
}
//............................................................................
void assert_failed(char const * const module, int_t const id); // prototype
void assert_failed(char const * const module, int_t const id) {
    Q_onError(module, id);
}

