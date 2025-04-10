//============================================================================
// Product: Board Support Package example
// Last Updated for Version: 7.3.0
// Date of the Last Update:  2023-08-12
//
//                   Q u a n t u m  L e a P s
//                   ------------------------
//                   Modern Embedded Software
//
// Copyright (C) 2005 Quantum Leaps, LLC. All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-QL-commercial
//
// This software is dual-licensed under the terms of the open source GNU
// General Public License version 3 (or any later version), or alternatively,
// under the terms of one of the closed source Quantum Leaps commercial
// licenses.
//
// The terms of the open source GNU General Public License version 3
// can be found at: <www.gnu.org/licenses/gpl-3.0>
//
// The terms of the closed source Quantum Leaps commercial licenses
// can be found at: <www.state-machine.com/licensing>
//
// Redistributions in source code must retain this top-level comment block.
// Plagiarizing this software to sidestep the license obligations is illegal.
//
// Contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//============================================================================
#ifndef BSP_H_
#define BSP_H_

#define BSP_TICKS_PER_SEC    100U

void BSP_init(void);
void BSP_start(void);

//......................................................................

uint8_t already_requested(uint16_t level);
uint8_t registry_Empyt(void);

uint16_t getHighestRequest(uint16_t base);
uint16_t getLowestRequest(uint16_t base);

void register_request(uint16_t level);
void unregister_request(uint16_t level);
//.......................................................................

void orangeOn(void);
void orangeOff(void);
void greenOn(void);
void greenOff(void);
void redOn(void);
void redOff(void);
void blueOn(void);
void blueOff(void);

//.........................................................................

void request(uint16_t SIG);

//.........................................................................

void BSP_randomSeed(uint32_t seed); // random seed
uint32_t BSP_random(void);          // pseudo-random generator

//..........................................................................

#endif // BSP_H_
