//$file${.::elevator.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: elevetor.qm
// File:  ${.::elevator.c}
//
// This code has been generated by QM 7.0.1 <www.state-machine.com/qm>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// Copyright (c) 2005 Quantum Leaps, LLC. All rights reserved.
//
//                 ____________________________________
//                /                                   /
//               /    GGGGGGG    PPPPPPPP   LL       /
//              /   GG     GG   PP     PP  LL       /
//             /   GG          PP     PP  LL       /
//            /   GG   GGGGG  PPPPPPPP   LL       /
//           /   GG      GG  PP         LL       /
//          /     GGGGGGG   PP         LLLLLLL  /
//         /___________________________________/
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// This generated code is open-source software licensed under the GNU
// General Public License (GPL) as published by the Free Software Foundation
// (see <https://www.gnu.org/licenses>).
//
// NOTE:
// The GPL does NOT permit the incorporation of this code into proprietary
// programs. Please contact Quantum Leaps for commercial licensing options,
// which expressly supersede the GPL and are designed explicitly for
// closed-source distribution.
//
// Quantum Leaps contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//
//$endhead${.::elevator.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "elevator.h"
#include "qpc.h"
#include "bsp.h"
#include "usbd_cdc_if.h"
#include "string.h"
#include <stdio.h>
Q_DEFINE_THIS_FILE

//$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// Check for the minimum required QP version
#if (QP_VERSION < 730U) || (QP_VERSION != ((QP_RELEASE^4294967295U)%0x2710U))
#error qpc version 7.3.0 or higher required
#endif
//$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//$define${AOs::Elevator} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::Elevator} ...........................................................

//${AOs::Elevator::SM} .......................................................
QState Elevator_initial(Elevator * const me, void const * const par) {
    //${AOs::Elevator::SM::initial}
    (void) par;


    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

    strcpy(me->doorState, "Closed");

    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''


    return Q_TRAN(&Elevator_operational);
}

//${AOs::Elevator::SM::operational} ..........................................
QState Elevator_operational(Elevator * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Elevator::SM::operational::initial}
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Elevator_Stationary);
            break;
        }
        //${AOs::Elevator::SM::operational::PRINT}
        case PRINT_SIG: {
                const char* msg =
                    "\n\rElevator Control System"
                    "\n\r1-5: Call for a Lift on your floor (1 to 5)"
                    "\n\rA-E: Select destination inside (A1, B2, C3, D4, E5)\n"
                    "\n\rO: Open door "
                    "\n\rN: Close door"
                    "\n\rM: Show menu";

                 while (CDC_Transmit_FS((uint8_t*)msg, strlen(msg)) != USBD_OK) {
                     HAL_Delay(4);
                 }


                 char buffer[40];
                 snprintf(buffer, sizeof(buffer), "\r\n\n\t%-15s %-15s",
                          "Current-Level","Door State\n" );


                 while (CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer)) != USBD_OK) {
                     HAL_Delay(4);
                 }

                 refreshFeed();
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

//${AOs::Elevator::SM::operational::Stationary} ..............................
QState Elevator_Stationary(Elevator * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Elevator::SM::operational::Stationary}
        case Q_ENTRY_SIG: {
            redOn();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary}
        case Q_EXIT_SIG: {
            redOff();

            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::initial}
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Elevator_closed);
            break;
        }
        default: {
            status_ = Q_SUPER(&Elevator_operational);
            break;
        }
    }
    return status_;
}

//${AOs::Elevator::SM::operational::Stationary::Closing} .....................
QState Elevator_Closing(Elevator * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Elevator::SM::operational::Stationary::Closing}
        case Q_ENTRY_SIG: {
            QTimeEvt_armX(&me->Timer_Evt, CLOSING_TIME, 0U); /*<== one shot */
            blueOn();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::Closing}
        case Q_EXIT_SIG: {
            blueOff();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::Closing::TIMEOUT}
        case TIMEOUT_SIG: {
            strcpy(me->doorState, "Closed");
            refreshFeed();
            status_ = Q_TRAN(&Elevator_closed);
            break;
        }
        default: {
            status_ = Q_SUPER(&Elevator_Stationary);
            break;
        }
    }
    return status_;
}

//${AOs::Elevator::SM::operational::Stationary::Openning} ....................
QState Elevator_Openning(Elevator * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Elevator::SM::operational::Stationary::Openning}
        case Q_ENTRY_SIG: {
            QTimeEvt_armX(&me->Timer_Evt, OPENNING_TIME, 0U); /*<== one shot */
            blueOn();

            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::Openning}
        case Q_EXIT_SIG: {
            blueOff();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::Openning::TIMEOUT}
        case TIMEOUT_SIG: {
            strcpy(me->doorState, "Opened");
            refreshFeed();
            status_ = Q_TRAN(&Elevator_Opened);
            break;
        }
        default: {
            status_ = Q_SUPER(&Elevator_Stationary);
            break;
        }
    }
    return status_;
}

//${AOs::Elevator::SM::operational::Stationary::Opened} ......................
QState Elevator_Opened(Elevator * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Elevator::SM::operational::Stationary::Opened}
        case Q_ENTRY_SIG: {
            redOn();

            //QTimeEvt_armX(&me->stationaryTEvt, OPENED_WAIT_TIME, 0U); /*<== one shot */
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::Opened}
        case Q_EXIT_SIG: {
            redOff();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::Opened::CLOSE}
        case CLOSE_SIG: {
            //unregister_request(me->current);
            strcpy(me->doorState, "Closing");
            refreshFeed();
            status_ = Q_TRAN(&Elevator_Closing);
            break;
        }
        default: {
            status_ = Q_SUPER(&Elevator_Stationary);
            break;
        }
    }
    return status_;
}

//${AOs::Elevator::SM::operational::Stationary::closed} ......................
QState Elevator_closed(Elevator * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Elevator::SM::operational::Stationary::closed::REQUEST}
        case REQUEST_SIG: {
            //${AOs::Elevator::SM::operational::Stationary::closed::REQUEST::[me->current==Q_EVT_CAST(request~}
            if (me->current ==  Q_EVT_CAST(requestEvt)->level) {
                status_ = Q_HANDLED();
            }
            //${AOs::Elevator::SM::operational::Stationary::closed::REQUEST::[else]}
            else {
                me->next = Q_EVT_CAST(requestEvt)->level;

                status_ = Q_TRAN(&Elevator_motion);
            }
            break;
        }
        //${AOs::Elevator::SM::operational::Stationary::closed::OPEN}
        case OPEN_SIG: {
            strcpy(me->doorState, "Openning");
            refreshFeed();
            status_ = Q_TRAN(&Elevator_Openning);
            break;
        }
        default: {
            status_ = Q_SUPER(&Elevator_Stationary);
            break;
        }
    }
    return status_;
}

//${AOs::Elevator::SM::operational::motion} ..................................
QState Elevator_motion(Elevator * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Elevator::SM::operational::motion}
        case Q_ENTRY_SIG: {
            greenOn();
            QTimeEvt_armX(&me->Timer_Evt, TRANSITION_INTERVAL, TRANSITION_INTERVAL);

            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::motion}
        case Q_EXIT_SIG: {
            QTimeEvt_disarm(&me->Timer_Evt);
            greenOff();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Elevator::SM::operational::motion::TIMEOUT}
        case TIMEOUT_SIG: {
            (me->current < me->next) ? me->current++ : me->current--;
            refreshFeed();
            //${AOs::Elevator::SM::operational::motion::TIMEOUT::[me->current==me->next]}
            if (me->current == me->next) {
                //strcpy(me->dir, "STATIC");
                //strcpy(me->doorState, "Openning");
                //refreshFeed();

                status_ = Q_TRAN(&Elevator_closed);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Elevator_operational);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::Elevator} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${AOs::Elevator_inst} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::Elevator_inst} ......................................................
static Elevator Elevator_inst;
//$enddef${AOs::Elevator_inst} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${AOs::Elevator_Ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::Elevator_Ctor} ......................................................
void Elevator_Ctor(void) {
    Elevator * me = &Elevator_inst;
    QActive_ctor(&me->super, Q_STATE_CAST(&Elevator_initial));
    QTimeEvt_ctorX(&me->Timer_Evt, &me->super, TIMEOUT_SIG, 0U);
    me->current = 1U;
}
//$enddef${AOs::Elevator_Ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${AOs::AOElevator} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::AOElevator} .........................................................
QActive * AOElevator = &Elevator_inst.super;
//$enddef${AOs::AOElevator} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${AOs::Requestor}

//$define${AOs::Requestor_inst}

//$define${AOs::Requestor_Ctor}

//$define${AOs::AORequestor}

void refreshFeed(void){

    char buffer[40];
    snprintf(buffer, sizeof(buffer),
             "\r%s %-14d %-15s\n",
             "L",
             Elevator_inst.current,
             Elevator_inst.doorState);


    while (CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer)) != USBD_OK) {
        HAL_Delay(4); // or use busy wait
    }
}



//$define${shared::requests} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${shared::requests} ........................................................
volatile uint16_t requests =0U;
//$enddef${shared::requests} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

