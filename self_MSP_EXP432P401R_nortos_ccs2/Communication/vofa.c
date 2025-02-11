/*
 * vofa.c
 *
 *  Created on: 2023年7月12日
 *      Author: 32753
 */

#ifndef VOFA_C_
#define VOFA_C_
#include"vofa.h"
#include <stdio.h>
#include <math.h>
void change(float value);
float s;
typedef union {
  float f;
  struct {
    unsigned int mantissa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
  } raw;
} myfloat;
uint32_t arr[4];
uint32_t data[8]={};
uint8_t endflag[4]={
    0x00,0x00,0x80,0x7f
};//结束帧
extern uint16_t recievedata[16];
void transimitendflag()
{   uint32_t i=0;
    for(i=0;i<4;i++)
    {UART_transmitData(EUSCI_A0_BASE,endflag[i]);}
}
void transimit(float value1,float value2,float value3)
{
    change(value1);
    UART_transmitData(EUSCI_A0_BASE,data[6]+data[7]);
    UART_transmitData(EUSCI_A0_BASE,data[4]+data[5]);
    UART_transmitData(EUSCI_A0_BASE,data[2]+data[3]);
    UART_transmitData(EUSCI_A0_BASE,data[0]+data[1]);
    change(value2);
    UART_transmitData(EUSCI_A0_BASE,data[6]+data[7]);
    UART_transmitData(EUSCI_A0_BASE,data[4]+data[5]);
    UART_transmitData(EUSCI_A0_BASE,data[2]+data[3]);
    UART_transmitData(EUSCI_A0_BASE,data[0]+data[1]);
    change(value3);
    UART_transmitData(EUSCI_A0_BASE,data[6]+data[7]);
    UART_transmitData(EUSCI_A0_BASE,data[4]+data[5]);
    UART_transmitData(EUSCI_A0_BASE,data[2]+data[3]);
    UART_transmitData(EUSCI_A0_BASE,data[0]+data[1]);
    transimitendflag();

}
void change(float value)
{
    if(value==s) return;
    else s=value;
    myfloat var;
    var.f = value;
    arr[0] = var.raw.sign; //存储符号位
    arr[1] = var.raw.exponent; //存储指数位
    arr[2] = var.raw.mantissa >> 16; //存储尾数的高16位
    arr[3] = var.raw.mantissa & 0xFFFF; //存储尾数的低16位
    data[0]=(arr[0]*8+((arr[1]&0x80)>>7)*4+((arr[1]&0x40)>>6)*2+((arr[1]&0x20)>>5)*1)*16;
    data[1]=((arr[1]&0x10)>>4)*8+((arr[1]&0x08)>>3)*4+((arr[1]&0x04)>>2)*2+((arr[1]&0x02)>>1)*1;
    //cout<<data[0]<<endl<<data[1]<<endl;
    data[2]=((arr[1]&0x01)*8+((arr[2]&0x40)>>6)*4+((arr[2]&0x20)>>5)*2+((arr[2]&0x10)>>4)*1)*16;
    //cout<<data[2]<<endl;
    data[3]=((arr[2]&0x08)>>3)*8+((arr[2]&0x04)>>2)*4+((arr[2]&0x02)>>1)*2+(arr[2]&0x01)*1;
    //cout<<data[3]<<endl<<(arr[2]&0x01)<<endl;
    data[4]=(((arr[3]&0x8000)>>15)*8+((arr[3]&0x4000)>>14)*4+((arr[3]&0x2000)>>13)*2+((arr[3]&0x1000)>>12)*1)*16;
    data[5]=((arr[3]&0x0800)>>11)*8+((arr[3]&0x0400)>>10)*4+((arr[3]&0x0200)>>9)*2+((arr[3]&0x0100)>>8)*1;
    data[6]=(((arr[3]&0x0080)>>7)*8+((arr[3]&0x0040)>>6)*4+((arr[3]&0x0020)>>5)*2+((arr[3]&0x0010)>>4)*1)*16;
    data[7]=((arr[3]&0x0008)>>3)*8+((arr[3]&0x0004)>>2)*4+((arr[3]&0x0002)>>1)*2+(arr[3]&0x0001)*1;
    //uint32_t i=0;
}




#endif /* VOFA_C_ */
