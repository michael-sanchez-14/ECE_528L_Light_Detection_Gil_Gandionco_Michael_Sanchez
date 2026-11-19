/**
 * @file main.c
 *
 * @brief Main source code for the Light_Detection (I2C) program.
 *
 * This file contains the main entry point for the Light_Detection (I2C) program.
 *
 * It establishes communication with the following peripheral using I2C to demonstrate light detection:
 *  - OPT3001 Ambient Light Sensor (TI BP-BASSENSORSMKII BoosterPack)
 *
 * The following Timer_A modules are used in this lab:
 *  - Timer_A0: Used to generate PWM signals that will be used to drive the DC motors
 *  - Timer_A1: Used to generate periodic interrupts at a specified rate (1 kHz)
 *
 * @author
 */

#include <stdint.h>
#include "msp.h"
#include <math.h>

#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/Motor.h"
#include "inc/Timer_A1_Interrupt.h"
#include "inc/OPT3001.h"


#define DEBUG_ACTIVE
#define LUX_THRESHOLD 5000
OPT3001_Result Light;
static double lux = 0;
static uint8_t lux_done = 0;
static uint16_t Duty_Cycle_Left = 3750;
static uint16_t Duty_Cycle_Right = 3750;

/**
 * @brief This function samples the OPT3001 Ambient Light Sensor and calculates the lux
 *
 * @param none
 *
 * @return none
 */
void Sample_Light_Sensor();

/**
 * @brief This function enables the motors when the measured lux is greater than the specified threshold
 *
 * @param none
 *
 * @return none
 */
void Controller_1();

/**
 * @brief User-defined function executed by Timer A1 using a periodic interrupt
 *
 * @param none
 *
 * @return none
 */
void Timer_A1_Periodic_Task(void);

int main(void)
{
    Clock_Init48MHz();
    DisableInterrupts();
    LED1_Init();
    LED2_Init();
    Chassis_Board_LEDs_Init();
    EUSCI_A0_UART_Init_Printf();
    Timer_A1_Interrupt_Init(&Timer_A1_Periodic_Task, TIMER_A1_INT_CCR0_VALUE);
    Motor_Init();
    EUSCI_B1_I2C_Init();
    P8->OUT |= 0x01;
    OPT3001_Init();
    P8->OUT &= ~0x01;
    EnableInterrupts();

    while(1)
    {
        Sample_Light_Sensor();
#ifdef DEBUG_ACTIVE
        printf("\nLight Sensor Exponent: %d\n", Light.Exponent);
        printf("Light Sensor Mantissa: %d\n", Light.Result);
        printf("Light Sensor Lux: %f\n\n", lux);
        Clock_Delay1ms(100);
#endif
    }
}

void Controller_1()
{
    if(lux >= LUX_THRESHOLD)
    {
        Motor_Forward(Duty_Cycle_Left, Duty_Cycle_Right);
    }
    else
    {
        Motor_Stop();
    }
}

void Timer_A1_Periodic_Task(void)
{
    Controller_1();
}

void Sample_Light_Sensor()
{
    Light = OPT3001_Read_Light();
    lux = (0.01)*(pow(2,Light.Exponent))*(Light.Result);
}
