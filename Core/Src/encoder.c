#include "encoder.h"

int iTimerEncoder_left,iTimerEncoder_right;

int GetTimEncoder_left(void)
{
  iTimerEncoder_right=(short)(__HAL_TIM_GET_COUNTER(&htim3));
  __HAL_TIM_SET_COUNTER(&htim3,0);
  return   iTimerEncoder_right;
}

int GetTimEncoder_right(void)
{
  iTimerEncoder_right=(short)(__HAL_TIM_GET_COUNTER(&htim2));
  __HAL_TIM_SET_COUNTER(&htim2,0);
  return   iTimerEncoder_right;
}
