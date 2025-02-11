#include"getAngle.h"
#include"Communication\uart_to_pc.h"
#include"Communication\vofa.h"
uint16_t AngleDataBuf[26];
uint32_t  AngleDataBuf2[66];
uint16_t AngleData[8];
uint16_t AngleData2[6];
uint16_t CoordinateData[66];
uint16_t CenterCoordinatex;
uint16_t CenterCoordinatey;
uint16_t f1;
uint16_t f2;
uint16_t f3;
uint16_t f4;
uint16_t FnValue[8][2];
float  Angle;
float Angle2;
float s;
uint32_t buf_count;
uint32_t buf_count2;
uint32_t buf_count3;
uint32_t Coordinatex=0;
uint32_t Coordinatey=0;
void recieveAngleFromK210()
{
    if(buf_count<26)
    {
        AngleDataBuf[buf_count]=UART_receiveData(EUSCI_A1_BASE);
        buf_count++;
        UART_clearInterruptFlag(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    }
}
float getAngleFromK210()
{   if(buf_count<26) return s;
   else
  {
       int i=0;
    uint32_t flag=0;//��¼��ʼ��־
    uint32_t  flag1=0;//��¼С����λ��
    uint32_t flag2=0;//data����
    for(i=0;i<25;i++)
    {
        if(AngleDataBuf[i]==0x46&&AngleDataBuf[i+1]==0x46)
        {
            flag=i+2;
            break;
        }
    }
    for(i=flag;i<flag+8;i++)
    {
        if(AngleDataBuf[i]==0x2e) {flag1=flag2;}
        AngleData[flag2]=AngleDataBuf[i];
        flag2++;
    }
       float t=1;

   for(i=flag1-1;i>=0;i--)
   {
     s+=(float)((AngleData[i]-48)*t);
     t*=10;
   }
    //cout<<s<<endl;

     t=0.1;
    for(i=flag1+1;i<8;i++)
    {
    s+=(float)((AngleData[i]-48)*t);
    //cout<<(double)((AngleData[i]-48)*t)<<endl;
    t*=0.1;
     }
     //s+=(float)((AngleData[7]-48)*10*t);
    buf_count=0;
    return s;
  }


}

/*
 * ������������jy901s�Ĵ��������������������Ҫ�ĽǶ����ݣ�����ÿ������Ϊ11���ֽڣ�ÿ�δ�4������
 * ���Ǳ�����һ����СΪ�����ֽڵ�������Ϊ����������֤��������ʱ�̺����������������ݡ�
 */
void recieveDataFromJY901S()
{

    if(buf_count2<67)//buf_countΪ��ȡ�ֽ�����־������ȡ�ֽ���Ϊ66ʱ��ȡ�Ƕ����ݣ�����66ʱ������ȡ�ֽڵ�������
    {
        AngleDataBuf2[buf_count2]=UART_receiveData(EUSCI_A1_BASE);
        buf_count2++;
        UART_clearInterruptFlag(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    }
    else
        {
      //transimit_intarray(AngleDataBuf2,66);
              int i=0;
              uint32_t flag=0;//��¼��ʼ��־
              for(i=0;i<66;i++)
              {
                  if(AngleDataBuf2[i]==0x55&&AngleDataBuf2[i+1]==0x53&&AngleDataBuf2[i+11]==0x55)
                  {
                      flag=i+2;
                      break;
                  }
              }//ÿ�����ݶ�����0x55,0x53��ͷ�������Ƕ�λ��������λ�ڻ�������λ��

              short z;
              z=(short)(((short)AngleDataBuf2[flag+5]<<8)+AngleDataBuf2[flag+4]);
              short x;
              x=(short)(((short)AngleDataBuf2[flag+1]<<8)+AngleDataBuf2[flag]);
              // transimit((float)z,0,0);
              Angle=((float)(z/32768.0))*180;//���ݼ����ֲ����ĽǶȻ���
              Angle2=((float)(x/32768.0))*180;
              //buf_count2=0;
              buf_count2=0;//��ȡ�ֽ������㣬�����򻺳���д��������
              UART_clearInterruptFlag(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
              MAP_Interrupt_disableSleepOnIsrExit();
        }
}
/*
 *�ڱ��ļ���Angle��ȫ�ֱ�������һ�����޸���Angleֵ��Angleֵ�ᷢ���ı䣬����������ظ�ֵ
 */
float getAngleFromJY901S()
{  if(Angle<0) return Angle+360;
else return  Angle;
}
float getAngle2FromJY901S()
{  if(Angle2<0) return Angle2+360;
     else return  Angle2;
}
/*
 *�ú����ӻ�������ȡx��y����*/
 void recieveCoordinateData()
{
    if(buf_count3<66)
    {
        CoordinateData[buf_count3]=UART_receiveData(EUSCI_A2_BASE);
        buf_count3++;
        MAP_Interrupt_disableSleepOnIsrExit();
            UART_clearInterruptFlag(EUSCI_A2_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
        //return ;
    }
    else
    {
        int i=0;
      uint32_t flag=0;//��¼��ʼ��־
       for(i=0;i<66;i++)
       {
           if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xbb)
             {
                 flag=i;
               Coordinatex=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                     //// transimit_float_A0(Coordinatex);
                Coordinatey=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                         //break;
              }

            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xaa)
             {
                 flag=i;
                 CenterCoordinatex=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                               //// transimit_float_A0(Coordinatex);
                 CenterCoordinatey=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                   //break;
              }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf1)
                         {
                             flag=i;
                           FnValue[0][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                           FnValue[0][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                            //break;
                          }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf2)
                                 {
                                     flag=i;
                                   FnValue[1][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                   FnValue[1][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                    //break;
                                  }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf3)
                                 {
                                     flag=i;
                                   FnValue[2][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                   FnValue[2][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                    //break;
                                  }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf4)
                                 {
                                     flag=i;
                                   FnValue[3][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                   FnValue[3][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                    //break;
                                  }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf5)
                                 {
                                     flag=i;
                                   FnValue[4][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                   FnValue[4][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                    //break;
                                  }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf6)
                                 {
                                     flag=i;
                                   FnValue[5][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                   FnValue[5][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                    //break;
                                  }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf7)
                                 {
                                     flag=i;
                                   FnValue[6][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                   FnValue[6][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                    //break;
                                  }
            if(CoordinateData[i]==0xff&&CoordinateData[i+5]==0xf8)
                                 {
                                     flag=i;
                                   FnValue[7][0]=(CoordinateData[flag+1]<<8)+CoordinateData[flag+2];
                                   FnValue[7][1]=(CoordinateData[flag+3]<<8)+CoordinateData[flag+4];
                                    //break;
                                  }


       }

         // transimit_float_A0(Coordinatey);
           buf_count3=0;
           //transimit(getCoordinateDatax(),getCoordinateDatay(),0);
             //transimit_float_A0();
           MAP_Interrupt_disableSleepOnIsrExit();
             UART_clearInterruptFlag(EUSCI_A2_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
            // return ;
       //}

    }
}


uint32_t getCoordinateDatax()
{
    return Coordinatex;
}
uint32_t getCoordinateDatay()
{
    return Coordinatey;
}
uint32_t getCenterCoordinateDatax()
{
    return CenterCoordinatex;
}
uint32_t getCenterCoordinateDatay()
{
    return CenterCoordinatey;
}
uint16_t *getFnValue()
{
    return *FnValue;
}

