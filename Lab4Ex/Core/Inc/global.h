/*
 * global.h
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "button.h"
#include "GPIO.h"

#define TIMER_FOR_LED_PA5		0
#define TIMER_COUNTDOWN_1		1
#define TIMER_COUNTDOWN_2		2
#define TIMER_BLINK_LED			3
#define TIMER_DISPLAY_7SEG		4
#define TIMER_UPDATE_BUFFER		5

#define LED_PA5_CYCLE				1000
#define COLOR_LED_BLINK_CYCLE		250
#define PERIOD_SCAN_7SEG_LED		80
#define PERIOD_UPDATE_TIME_BUFFER	500

//MENU STATE
#define INIT   1
#define AUTO   2
#define MANUAL 3
#define CONFIG 4

// Manual mode states
typedef enum {
	MAN_RED = 11,
	MAN_YELLOW,
	MAN_GREEN,
	MAN_RUN
} ManualState;


// Manual mode button events
typedef enum {
	EV_NONE,
	EV_INC, // Increase time
	EV_DEC, // Decrease time
	EV_NEXT_MODE // Move to next mode
} ManualEvent;


extern int status;
extern int nextMenuState;
extern int flagMenuChange;

extern ManualEvent manEvt;
extern ManualState man_state;

void doInit();

#endif /* INC_GLOBAL_H_ */
