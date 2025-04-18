/**
 * dvruntime Generated Interface Header File
 *
 * @file DVRunTime_interface.h
 * 
 * @ingroup dvruntime
 * 
 * @brief Contains the function pointers to the DV Run Time library component.
 *
 * @version dvruntime Version 1.0.0.
*/
/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/ 

#ifndef DVRT_INTERFACE_H
#define DVRT_INTERFACE_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
  Selecion: Data Type Definitions
*/
/**
 @ingroup dvruntime
 @struct DVRT_interface_t
 @brief Structure containing the function pointers to the DV Run Time driver APIs.
*/
typedef struct{
    void (*Initialize)(void);
    void (*Process)(void);	
}DVRT_interface_t;


#ifdef __cplusplus
}
#endif

#endif /* DVRT_INTERFACE_H */