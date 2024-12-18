#include "software_timer.h"
#include "led_7seg.h"



int Colon_fl = 0;
int count_colon = 0;

int Updatetime_fl = 0;
int count_update_time = 0;

int hours = 15;
int minutes = 20;
int colon_status = 0;

void updateTime()
{
	minutes++;
	if(minutes >= 60)
	{
		minutes = 0;
		hours = hours + 1;
		if(hours >= 24)
		{
			hours = 0;
		}
	}
	setTimer_update_time(60000);
}
void updateColon()
{
	colon_status = !colon_status;
	led7_SetColon(colon_status);
	setTimer_colon(250);
}

void showTime()
{
    int hour_tens = hours / 10;
    int hour_units = hours % 10;
    int minute_tens = minutes / 10;
    int minute_units = minutes % 10;

    led7_SetDigit(hour_tens, 0, 0);
    led7_SetDigit(hour_units, 1, 0);
    led7_SetDigit(minute_tens, 2, 0);
    led7_SetDigit(minute_units, 3, 0);
}


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */

void timer_init()
{
	HAL_TIM_Base_Start_IT(&htim2);
	setTimer_colon(250);
	setTimer_update_time(60000);
	showTime();
}

/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer_colon(uint16_t duration)
{
	int timer_MUL = duration/TIMER_CYCLE_2;
	count_colon = timer_MUL;
	Colon_fl = 0;
}
void setTimer_update_time(uint16_t duration)
{
	int timer_MUL = duration/TIMER_CYCLE_2;
	count_update_time = timer_MUL;
	Updatetime_fl = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		if(count_colon > 0)
		{
			count_colon = count_colon - 1;
			if(count_colon <= 0)
			{
				Colon_fl = 1;
			}
		}
		if(count_update_time > 0)
		{
			count_update_time = count_update_time - 1;
			if(count_update_time <= 0)
			{
				Updatetime_fl = 1;
			}
		}
		// 1ms interrupt here
		led7_Scan();
	}
}
