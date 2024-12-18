#include "software_timer.h"

#include "led_7seg.h"



int timer2_fl = 0;
int counter_shift = 0;

int digits[4] = {1, 5, 2, 0};

void shiftRight()
{
	// save last number
    int lastDigit = digits[3];
    for (int i = 3; i > 0; i = i - 1)
    {
    	// shift right
        digits[i] = digits[i - 1];
    }
    digits[0] = lastDigit;
}

void showDigits(){
    for (int i = 0; i < 4; i++)
    {
        led7_SetDigit(digits[i], i, 0); // Hiển thị từng số lên từng LED
    }
}


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */

void timer_init()
{
	HAL_TIM_Base_Start_IT(&htim2);
	showDigits();
	setTimer2(SHIFT_DELAY);
}

/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer2(uint16_t duration)
{
	int timer_MUL = duration/TIMER_CYCLE_2;
	counter_shift = timer_MUL;
	timer2_fl = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		if(counter_shift > 0)
		{
			counter_shift--;
			if(counter_shift <= 0)
			{
				timer2_fl = 1;
			}
		}
		// 1ms interrupt here
		led7_Scan();
	}
}
