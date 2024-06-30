#include "control.h"
#include "main.h"
#include "motor.h"
#include "tim.h"

extern float Velocity_KP,Velocity_KI,Velocity_KD; 

extern int Encoder_count_left,Encoder_count_right, Target_Velocity_left,Target_Velocity_right; 
extern int target_rpm_right,target_rpm_left;
extern int Moto_pwm_left,Moto_pwm_right;

//限幅
void limiting_Pwm_left(void)
{	
	  int maximum=100;    //PWM最大为100
	  if(Moto_pwm_left<-maximum) Moto_pwm_left=-maximum;	
		if(Moto_pwm_left>maximum)  Moto_pwm_left=maximum;		
}

void limiting_Pwm_right(void)
{	
	  int maximum=100;    //PWM最大为100
	  if(Moto_pwm_right<-maximum) Moto_pwm_right=-maximum;	
		if(Moto_pwm_right>maximum)  Moto_pwm_right=maximum;		
}



int myabs(int num)
{
	int temp;
	if(num<0)	temp=-num;
	else temp =num;
	return temp;
}


//设置PWM
void Set_Pwm_left(int moto)
{
	int pwm_abs;
  	if(moto<0)
	{Left_Moto(0);}	//反		
	else
	{Left_Moto(1);}//正
	pwm_abs=myabs(moto);		
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,pwm_abs);
}

void Set_Pwm_right(int moto)
{
	int pwm_abs;
  	if(moto<0)
	{Right_Moto(0);}				
	else
	{Right_Moto(1);}
	pwm_abs=myabs(moto);		
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,pwm_abs);
}






//总函数
void Control_function_left(void)
{
	Target_Velocity_left =(int)(target_rpm_left/6000.0*4*6.25*11);//将rpm转换为脉冲数
	Moto_pwm_left=Incremental_PI_left(Encoder_count_left,Target_Velocity_left);
	limiting_Pwm_left();
	Set_Pwm_left(Moto_pwm_left);
}

void Control_function_right(void)
{
	Target_Velocity_right =(int)(target_rpm_right/6000.0*4*6.25*11);//将rpm转换为脉冲数
	Moto_pwm_right=Incremental_PI_right(Encoder_count_right,Target_Velocity_right);
	limiting_Pwm_right();
	Set_Pwm_right(Moto_pwm_right);
}






/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/

int Incremental_PI_left (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Last_bias,Last_last_bias;
	 Bias=Target-Encoder;                                  
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias+Velocity_KD*(Bias-(2*Last_bias)+Last_last_bias);   
	 Last_bias=Bias;
	Last_last_bias=Last_bias;	
	 return Pwm;                                          
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/

int Incremental_PI_right (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Last_bias,Last_last_bias;
	 Bias=Target-Encoder;                                  
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias+Velocity_KD*(Bias-(2*Last_bias)+Last_last_bias);   
	 Last_bias=Bias;
	Last_last_bias=Last_bias;	
	 return Pwm;                                          
}