/* ************************************************************************** */
/** Descriptive File Name

  @Company
 CPEG 222 Team #1
 * Alex Chacko & Matias Saavedra

  @File Name
 proj1.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
// PIC32MX370F512L Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // Shadow Register Set Priority Select (SRS Priority 7)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2        // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (24x Multiplier)
#pragma config FPLLODIV = DIV_1       // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = XT            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT Enabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is Disabled)
#pragma config JTAGEN = OFF              // JTAG Enable (JTAG Port Enabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

#define DELAY 7813              //200 ms

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING
#endif

#include <stdlib.h>     //include C standard library for rand() function
#include <math.h>       //include C math library for floor() function
#include <xc.h>         //include Microchip XC compiler header
#include <plib.h>       //include Microchip peripheral libraries for timers, adc, etc...
#include "config.h"     //include Digilent Basys MX3 configuration file
#include "lcd.h"        //include Digilent LCD (liquid crsytal display) library
#include "adc.h"        //include Digilent ADC (analog to digital converter) library
#include "btn.h"        //include Digilent BTN (push button) library
#include "led.h"        //include Digilent LED (light emmitting diode) library
//#include "ssd.h"        //include Digilent SSD (seven segment display) library
#include "rgbled.h"     //include Digilent RGBLED (red/green/blue LED) library
/* TODO:  Include other files here if needed. */
int main(void){
    int btnState=0; //Default value of 0 so the lights don't move, 1 means shift right, 2 will shift left.
    int WAIT = 200;
    TRISA = 0xF00;
    ANSELA = 0x0;
    LATA = 0x1;
    TRISF = 0x1;
    ANSELF = 0x0;
    TRISB = 0x101;
    ANSELB = 0x0;
    T1CON = 0x8030;
    LCD_Init();
    LCD_WriteStringAtPos("Team 1", 0, 0);
    LCD_WriteStringAtPos("Matias & Alex", 1, 0);
    while(1){
        if(PORTFbits.RF0){
            delay_ms();
            btnState = 0;
        }
        else if(PORTBbits.RB8){
            btnState = 1;
        }
        else if(PORTBbits.RB0){
            btnState = 2;
        }
        if(btnState==1){
            delay_ms();
            if(PORTAbits.RA0){
                LATA = 0x80;
            }
            else{
                 LATA = PORTA >> 1;
            }
        }
        else if(btnState==2){
            delay_ms();
            if(PORTAbits.RA7){
                LATA = 0x01;
            }
            else{
                 LATA = PORTA << 1;
            }
        }
        else{
            //LATA = PORTA;
        }
    }
}

void delay_ms() {
    TMR1 = 0;
    while(TMR1 < DELAY){
        
    }
}