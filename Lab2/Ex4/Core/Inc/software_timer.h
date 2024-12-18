#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_


#include "tim.h"
#include "software_timer.h"

#define TIMER_CYCLE_2 1

extern int Colon_fl;
extern int Updatetime_fl;


void timer_init();
void setTimer_colon(uint16_t duration);
void setTimer_update_time(uint16_t duration);
void showTime();
void updateColon();
void updateTime();

#endif /* INC_SOFTWARE_TIMER_H_ */
