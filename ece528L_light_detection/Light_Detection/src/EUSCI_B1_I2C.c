/**
 * @file EUSCI_B1_I2C.c
 * @brief Source code for the EUSCI_B1_I2C driver.
 *
 * This file contains the function definitions for the EUSCI_B1_I2C driver.
 * The EUSCI_B1_I2C driver uses busy-wait implementation.
 *
 * @note This function assumes that the necessary pin configurations for I2C communication have been performed
 *       on the corresponding pins. The output from the pins will be observed using an oscilloscope.
 *       - P6.4 (SDA)
 *       - P6.5 (SCL)
 *
 * For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @author
 *
 */

#include "../inc/EUSCI_B1_I2C.h"

void EUSCI_B1_I2C_Init()
{
    EUSCI_B1->CTLW0 |= 0x0001;
    EUSCI_B1->CTLW0 &= ~0xC000;
    EUSCI_B1->CTLW0 &= ~0x2000;
    EUSCI_B1->CTLW0 |= 0x0800;
    EUSCI_B1->CTLW0 |= 0x0600;
    EUSCI_B1->CTLW0 |= 0x0100;
    EUSCI_B1->CTLW0 |= 0x00C0;
    EUSCI_B1->CTLW0 &= ~0x0020;
    EUSCI_B1->CTLW0 &= ~0x0010;
    EUSCI_B1->CTLW0 &= ~0x0008;
    EUSCI_B1->CTLW0 &= ~0x0004;
    EUSCI_B1->CTLW0 &= ~0x0002;
    EUSCI_B1->CTLW1 &= ~0x01FF;
    EUSCI_B1->BRW = 30;

    P6->SEL0 |= 0x30;
    P6->SEL1 &= ~0x30;

    EUSCI_B1->IE &= ~0x7FFF;
    EUSCI_B1->CTLW0 &= ~0x0001;
}

void EUSCI_B1_I2C_Send_A_Byte(uint8_t slave_address, uint8_t data)
{
    while((EUSCI_B1->STATW & 0x0010) != 0);

    EUSCI_B1->I2CSA = slave_address;

    EUSCI_B1->CTLW0 = (EUSCI_B1->CTLW0 & ~0x0004) | 0x0012;

    while((EUSCI_B1->IFG & 0x0002) == 0);

    EUSCI_B1->TXBUF = data;

    while((EUSCI_B1->IFG & 0x0002) == 0);

    EUSCI_B1->CTLW0 |= 0x0004;
    EUSCI_B1->IFG &= ~0x0002;
}

void EUSCI_B1_I2C_Send_Multiple_Bytes(uint8_t slave_address, uint8_t *data_buffer, uint32_t packet_length)
{
    while((EUSCI_B1->STATW & 0x0010) != 0);
    EUSCI_B1->I2CSA = slave_address;

    EUSCI_B1->CTLW0 = (EUSCI_B1->CTLW0 & ~0x0004) | 0x0012;

    for(int i = 0; i < packet_length; i++)
    {
        while((EUSCI_B1->IFG & 0x0002) == 0);
        EUSCI_B1->TXBUF = data_buffer[i];

    }

    while((EUSCI_B1->IFG & 0x0002) == 0);
    EUSCI_B1->CTLW0 |= 0x0004;
    EUSCI_B1->IFG &= ~0x0002;
}

uint8_t EUSCI_B1_I2C_Receive_A_Byte(uint8_t slave_address)
{
    while((EUSCI_B1->STATW & 0x0010) != 0);
    EUSCI_B1->CTLW0 |= 0x0001;
    EUSCI_B1->TBCNT |= 0x0001;
    EUSCI_B1->CTLW0 &= ~0x0001;
    EUSCI_B1->I2CSA = slave_address;
    EUSCI_B1->CTLW0 = (EUSCI_B1->CTLW0 & ~0x0010) | 0x0006;

    while((EUSCI_B1->IFG & 0x0001) == 0);
    return ((uint8_t)EUSCI_B1->RXBUF);
}

void EUSCI_B1_I2C_Receive_Multiple_Bytes(uint8_t slave_address, uint8_t *data_buffer, uint16_t packet_length)
{
    EUSCI_B1->I2CSA = slave_address;
    EUSCI_B1->CTLW0 =(EUSCI_B1->CTLW0 & ~0x0010) | 0x0002;
    for(int i = 0; i < packet_length; i++)
    {
        if(i == (packet_length - 1))
        {
        EUSCI_B1->CTLW0 |= 0x0004;
        }

        while((EUSCI_B1->IFG & 0x0001) == 0);
        data_buffer[i] = EUSCI_B1->RXBUF;

    }

    while((EUSCI_B1->CTLW0 & 0x0004) != 0);
}
