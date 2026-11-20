# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Light Detection (I2C)
The Light Detection (I2C) lab interfaces with the following:
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* OPT3001 Ambient Light Sensor - TI BP-BASSENSORSMKII BoosterPack - [Product Link](https://www.ti.com/tool/BP-BASSENSORSMKII)
## Overview


## Components Used:
For this lab we used the following components:
* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* MSP432 LaunchPad
* USB-A to Micro-USB cable
* TI-RSLK MAX Chassis 
* Oscilloscope Probes
* * OPT3001 Ambient Light Sensor - TI BP-BASSENSORSMKII BoosterPack - [Product Link](https://www.ti.com/tool/BP-BASSENSORSMKII)
## Pre Lab
1. What is lux? What formula is used to calculate the lux measured by the OPT3001
Ambient Light Sensor? Refer to the OPT3001 Datasheet in the Result Register
section (7.6.1.1.1).

Lux is the unit of illuminance. The formula the OPT3001 uses to calculate:
lux = LSB_Size × R[11:0], where LSB_Size = 0.01 × 2<sup>E[3:0]</sup>

2. What possible I2C addresses can be used by the OPT3001 Ambient Light Sensor? In
a table, list the addresses in hexadecimal format and provide each pin connection.
Refer to the OPT3001 Datasheet in the Serial Bus Address section (7.3.4.1).

3. What is a struct in C? What can it be used for? Provide an example of using a struct
by writing a short program that defines a struct with two int members. Initialize the
members of the struct with any values of your choice and print their values.

A struct in C is a user defined data type, it is used to group different variables. [program](examplestruct.c)

## Post Lab
1. What would happen to the shape of the SCL and SDA signals if the values of the pull-
up resistors were significantly increased?

2. How can multiple peripheral devices use the same I2C bus? How does the main I2C
controller know when to transmit or receive data from the peripheral device?

3. What are some advantages and disadvantages of using I2C? List at least three
reasons for each.

4. Based on your results from the Procedure section, what was your measured SCL
clock frequency? Is this value higher or lower than the expected SCL frequency? If
there is a discrepancy between the measured and expected clock frequency values,
explain why.

## Analysis and Results:

## Known Issues or Limitations
No known issues or limitations.

## Author Contribution
* Michael Sanchez
    * 
    * 
* Gil Gandionco 
    * 
    * 
## References

* MSP432P4xx SimpleLink™ Microcontrollers
Technical Reference Manual
