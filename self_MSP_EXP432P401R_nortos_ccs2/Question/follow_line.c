/*
 * follow_line.c
 *
 *  Created on: 2023年7月23日
 *      Author: bink,Emma
 */

#include "Question\follow_line.h"

follow_line_t follow_line;
uint8_t data;
uint8_t count;//计算转过多少个弯了
//int set_speed[2]={300,-300};
//int set_speed3[2]={200,-200};
//int set_speed1[2]={-300,300};
//int set_speed2[2]={-200,200};

//pid参数设置
float angle_pid[2][3]={{1,0,0},
                       {1,0,0}};
float speed_pid[2][3]={{8.54,-0.11,0},
                       {8.37,0.12,0}};

//{{8.54,-0.11,0},
//                      {8.37,0.12,0}};
void set_follow_line_wd(void)
{

    data = LineSensor_Read(DEBUG_TIME);
    data=data<<1;
    switch(data)
    {
        //左转
        case 0xfc: follow_line.wd=14;break; //111 1 1100
        case 0xf8: follow_line.wd=10;break;  //111 1 1000
        case 0xf0: follow_line.wd=6;break;  //111 1 0000
        case 0xfb: follow_line.wd=5;break;  //111 1 1010
        case 0xf2: follow_line.wd=4;break;  //111 1 0010
        case 0xf6: follow_line.wd=2;break;  //111 1 0110
        case 0x36: follow_line.wd=1;break;  //111 0 0110
        case 0xc6: follow_line.wd=1;break;  //110 0 0110
        case 0x00: follow_line.wd=0;break;  //110 0 0110
        //直行
        case 0xee: follow_line.wd=0;break;  //111 0 1110
        //右转
        case 0xce: follow_line.wd=-1;break; //110 0 1110
        case 0x8e: follow_line.wd=-2;break; //100 0 1110
        case 0xde: follow_line.wd=-3;break; //110 1 1110
        case 0x9e: follow_line.wd=-4;break; //100 1 1110
        case 0xbe: follow_line.wd=-5;break; //101 1 1110
        case 0x3e: follow_line.wd=-7;break; //001 1 1110
        case 0x1e: follow_line.wd=-9;break; //000 1 1110
        case 0x7e: follow_line.wd=-14;break;//011 1 1110
    }

}

void follow_line_pid()
{
    //串级pid初始化
    PID_init(&follow_line.angle_pid[0], PID_POSITION, angle_pid[0], 20, 1);
    PID_init(&follow_line.angle_pid[1], PID_POSITION, angle_pid[1], 20, 1);
    PID_init(&follow_line.speed_pid[0], PID_POSITION, speed_pid[0], 1000, 1000);
    PID_init(&follow_line.speed_pid[1], PID_POSITION, speed_pid[1], 1000, 1000);
    //pid运算
    follow_line.set_speed[0]=GO_SPEED-PID_calc(&follow_line.angle_pid[0],follow_line.wd, 0);
    follow_line.set_speed[1]=GO_SPEED+PID_calc(&follow_line.angle_pid[0],follow_line.wd, 0);
    follow_line.wheel_pwm[0]=PID_calc(&follow_line.speed_pid[0],follow_line.motor_info->speed[0], follow_line.set_speed[0]);
    follow_line.wheel_pwm[1]=PID_calc(&follow_line.speed_pid[1],follow_line.motor_info->speed[1], follow_line.set_speed[1]);
    delay_ms(10);
}

void follow_line_loop1()//直线循迹
{
    DataPro(SensorArray,&sum,&left,&right);
    set_follow_line_wd();
    if(sum==7 && follow_line.count<7)
    {
        motor_stop();
        delay_ms(1000);

      while(1)
       {
          if(follow_line.count==6){
              motor_stop();
              delay_ms(1000);
              motor_l_90(19);
              follow_line.count++;
              break;
          }
           turn_L(20);
         DataPro(SensorArray,&sum,&left,&right);
         if( SensorArray[0]==0)
         {
             //motor_stop_time(1000);
             follow_line.count++;
             break;
         }
       }


    }
    else if(sum==7 && follow_line.count>=7)
    {
        motor_stop();
        while(1)
        {
            if(follow_line.count==13)
            {
                motor_stop();

                motor_r_90(19);
                follow_line.count=0;
               break;
            }

             turn_R(20);
           DataPro(SensorArray,&sum,&left,&right);
           if( SensorArray[6]==0)
           {
               //motor_stop_time(1000);
               follow_line.count++;
               break;
           }
         }
    }
    else
    {
        follow_line_pid();
        motor_set_speed(follow_line.wheel_pwm);
    }


}

const  follow_line_t* get_follow_line_info(void)
{
    return &follow_line;
}












