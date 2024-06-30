#ifndef __CONTROL_H
#define	__CONTROL_H
#include "main.h"

int myabs(int num);

void limiting_Pwm_left(void);
void limiting_Pwm_right(void);


void Set_Pwm_left(int moto);
void Set_Pwm_right(int moto);

void Control_function_left(void);
void Control_function_right(void);


int Incremental_PI_left (int Encoder,int Target);
int Incremental_PI_right (int Encoder,int Target);


#endif