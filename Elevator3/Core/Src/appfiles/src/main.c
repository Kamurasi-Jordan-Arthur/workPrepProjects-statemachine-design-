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
 #include "bsp.h"                 // Board Support Package
#include "elevator.h"
#include <stdio.h>             // standard I/O for printf()
#include "main.h"
#include "usbd_cdc_if.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "string.h"
//............................................................................
int main() {
     QF_init();       // initialize the framework and the underlying RT kernel
     BSP_init();      // initialize the BSP
     BSP_start();     // start the AOs/Threads
//     HAL_Delay(10000);
//     const char* msg =
//         "\t\t\tThe Elevator Operation System.\n"
//         "\tPress any of the digits (0-9) to send a request to the Operation System.\n"
//         "\tPress \"I\" to interrupt at a closing operation.\n"
//         "\tPress \"C\" to clear all requests.\n";
//
//     while (CDC_Transmit_FS((uint8_t*)msg, strlen(msg)) != USBD_OK) {
//         HAL_Delay(4);
//     }
//
//
//     char buffer[128];
//     snprintf(buffer, sizeof(buffer), "%-4s %-15s %-15s %-15s %-15s %-10s\n",
//              "ID", "Current-Level", "Next-Level", "Direction", "Door State", "REQUESTS");
//
//
//     while (CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer)) != USBD_OK) {
//         HAL_Delay(4);
//     }
//
//     refreshFeed();

     return QF_run(); // run the QF application
}
