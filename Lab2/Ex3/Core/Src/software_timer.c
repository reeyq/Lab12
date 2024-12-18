#include "software_timer.h"

#include "led_7seg.h"



#define TIMER_CYCLE_2 1



int counter_7seg_scan = 20;

uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer2(uint16_t duration)
	{
		 timer2_MUL = duration/TIMER_CYCLE_2;
		 timer2_counter = timer2_MUL;
		 flag_timer2 = 0;
	 }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  if(htim->Instance == TIM2)
	  {
		  if(timer2_counter > 0)
		  {
			  timer2_counter--;
			  if(timer2_counter == 0)
				  {
					  flag_timer2 = 1;
					  timer2_counter = timer2_MUL;
				  }
		  }
		  if(counter_7seg_scan > 0 )
		  {
				counter_7seg_scan--;
				if(counter_7seg_scan <= 0)
				{
					led7_Scan();
					counter_7seg_scan = 500; //1Hz
					//counter_scan = 20; //25Hz
					//counter_scan = 5; //100Hz
				}
		  }

	}
}
