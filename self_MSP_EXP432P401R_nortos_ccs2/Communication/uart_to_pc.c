/*
 * uart_to_pc.c
 *
 *  Created on: 2023年7月5日
 *      Author: 32753
 */
#include"uart_to_pc.h"
#include"vofa.h"
//#include"bluetooth.h"
#include"external_devices/getAngle.h"
const static eUSCI_UART_ConfigV1 uartConfig={
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,
      6,
      8,
      0x20,
    EUSCI_A_UART_NO_PARITY,
    EUSCI_A_UART_LSB_FIRST,
    EUSCI_A_UART_ONE_STOP_BIT,
    EUSCI_A_UART_MODE,
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
    EUSCI_A_UART_8_BIT_LEN
};
const static eUSCI_UART_ConfigV1 uartConfig2={
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,
     78,
      2,
      0x0,
    EUSCI_A_UART_NO_PARITY,
    EUSCI_A_UART_LSB_FIRST,
    EUSCI_A_UART_ONE_STOP_BIT,
    EUSCI_A_UART_MODE,
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
    EUSCI_A_UART_8_BIT_LEN
};

void inituart_to_pc(uint32_t moduleInstance)
{         // GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
           //GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
    switch(moduleInstance)
    { case EUSCI_A0_BASE:
             GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
             GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
             GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
             MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
             GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
             MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);
             MAP_UART_enableModule(EUSCI_A0_BASE);
             MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
             MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
             UART_clearInterruptFlag(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
             MAP_Interrupt_enableMaster();
             break;


    case EUSCI_A1_BASE:
                 GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
                 GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                 GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
            MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,
                        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
            MAP_UART_initModule(EUSCI_A1_BASE, &uartConfig);
            MAP_UART_enableModule(EUSCI_A1_BASE);
            MAP_UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
            MAP_Interrupt_enableInterrupt(INT_EUSCIA1);
            UART_clearInterruptFlag(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
            MAP_Interrupt_enableMaster();
            break;
    case EUSCI_A2_BASE:
                 GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
                 GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                 GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
            MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
                        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
            MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);
            MAP_UART_enableModule(EUSCI_A2_BASE);
            MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
            MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
            UART_clearInterruptFlag(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
            MAP_Interrupt_enableMaster();
            break;
    case EUSCI_A3_BASE:
                 GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
                 GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                 GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
            MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9,
                        GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
            MAP_UART_initModule(EUSCI_A3_BASE, &uartConfig);
            MAP_UART_enableModule(EUSCI_A3_BASE);
            MAP_UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
            MAP_Interrupt_enableInterrupt(INT_EUSCIA3);
            UART_clearInterruptFlag(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
            MAP_Interrupt_enableMaster();
            break;
    default:return;
    }

}
void EUSCIA0_IRQHandler(void)
{
      UART_clearInterruptFlag(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
}
/*
 * pin2.3,pin2.3
 * 该函数为uart_A1中断，执行函数为陀螺仪jy901s
 */

void EUSCIA1_IRQHandler(void)
{
   //UART_transmitData(EUSCI_A0_BASE, UART_receiveData(EUSCI_A1_BASE));
    recieveDataFromJY901S();
    MAP_Interrupt_disableSleepOnIsrExit();
    UART_clearInterruptFlag(EUSCI_A1_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
}
/*
 * 该函数为K210回传中断;
 */
void EUSCIA2_IRQHandler(void)
{    recieveCoordinateData();
    //UART_transmitData(EUSCI_A0_BASE, UART_receiveData(EUSCI_A2_BASE));
     MAP_Interrupt_disableSleepOnIsrExit();
    UART_clearInterruptFlag(EUSCI_A2_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
}
/*
 * 该函数为蓝牙回传中断
 */
void EUSCIA3_IRQHandler(void)
{
//    uart_a3_do();
    MAP_Interrupt_disableSleepOnIsrExit();
    UART_clearInterruptFlag(EUSCI_A3_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
}
void uart_test()
{
    UART_transmitData(EUSCI_A0_BASE, 0x00);
}

