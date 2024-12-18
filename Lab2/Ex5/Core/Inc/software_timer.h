#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"
#include "software_timer.h"

#define TIMER_CYCLE_2 1
#define SHIFT_DELAY 1000

extern int timer2_fl;
extern int counter_shift;


void timer_init();
void setTimer2(uint16_t duration);
void shiftRight();
void showDigits();

#endif /* INC_SOFTWARE_TIMER_H_ */
