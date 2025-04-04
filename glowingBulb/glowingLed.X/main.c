 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

void PWM3_Initialize2(void)
 {
    // Set the PWM3 to the options selected in the User Interface
    
    // PWMPOL active_hi; PWMEN enabled; 
    ANSELAbits.ANSA2 = 0; // Set only RA2 to digital mode  
    TRISAbits.TRISA2 = 1U; // First Set the RA2 for into input 
    PWM3CON = 0; // first disable PWM3
    
    TMR2_PeriodCountSet((0x7F) >> 0); 
//    PWM3_LoadDutyValue(80U);
//    PWM3_LoadDutyValue((PWM3_INITIALIZE_DUTY_VALUE >> 0U) -1U);
    PIR1bits.TMR2IF = 0;
    T2CLKCON = (1 << _T2CLKCON_T2CS_POSN);  // T2CS FOSC/4
    T2CON = (2 << _T2CON_T2CKPS_POSN)   // T2CKPS 1:4
    | (1 << _T2CON_TMR2ON_POSN)   // TMR2ON on
    | (0 << _T2CON_T2OUTPS_POSN);  // T2OUTPS 1:1
    RA2PPS = 0x03;  //RA2->PWM3:PWM3OUT;
    TRISAbits.TRISA2 = 0; //Output mode
    PWM3CON = 0x90U;  //now set the PWM3
    
//     PWMDCH 25; 
//    PWM3DCH &= ~(0x19);
//    PWM3DCH |= 0x19;
//
//    // PWMDCL 1; 
//    PWM3DCL &= ~(0x40);
//    PWM3DCL |= 0x40;
    


 }


extern uint8_t xwaitPeriod;
uint8_t dutyValue = 0;

int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 
    PWM3_Initialize2();



    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    
    INTERRUPT_PeripheralInterruptEnable(); 
//        PWM3_LoadDutyValue(20U);
//        PWM3_LoadDutyValue(40);
//        PWM3_LoadDutyValue(60);

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 


    while(1)
    {
        static uint8_t increment = 1U;
        
        if ((xwaitPeriod & 15U) == 0U){

            PWM3_LoadDutyValue(dutyValue);
            DVRT_Process();
            
            //when to swtch to the other logic
            if(dutyValue == 100U){
                increment = 0;
            }else if(dutyValue == 0U){
                increment = 1;
            }
            
            // Decision to decrement of increment
            (increment) ?
                dutyValue++
            :
                dutyValue--;
               
        }

    }    
}