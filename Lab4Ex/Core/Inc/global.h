/*
 * global.h
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

//STATE
#define INIT   						11

#define RED_GREEN					12
#define RED_AMBER					13
#define GREEN_RED					14
#define AMBER_RED					15

#define MANUAL						16
#define MAN_RED_GREEN				17
#define MAN_RED_AMBER				18
#define MAN_GREEN_RED				19
#define MAN_AMBER_RED				20

#define CONFIG_RED					21
#define CONFIG_AMBER				22
#define CONFIG_GREEN				23

//DEFINE SOFTWARE TIMER
#define TIMER_FOR_LED_PA5			0
#define TIMER_COUNTDOWN_1			1
#define TIMER_COUNTDOWN_2			2
#define TIMER_BLINK_LED				3
#define TIMER_DISPLAY_7SEG			4
#define TIMER_UPDATE_BUFFER			5
#define TIMER_LCD_BLINK				6
#define TIMER_LCD_UPDATE			7

//DEFINE TIME TO SET
#define LED_PA5_CYCLE				1000
#define COLOR_LED_BLINK_CYCLE		250
#define PERIOD_SCAN_7SEG			40
#define PERIOD_UPDATE_TIME_BUFFER	100
#define PERIOD_LCD_BLINK			500
#define PERIOD_LCD_UPDATE			250


#define DEFAULT_REDTIME				5000
#define DEFAULT_AMBERTIME			2000
#define DEFAULT_GREENTIME			3000

#include "software_timer.h"
#include "button.h"

extern int status;
extern int flagchangeMode;
extern int flagcontrolManual;
extern int flagcontrolConfig;
extern int flagPedestrian;
extern int flagPedDisplay;
extern int pedDisplayRoad;


extern int RedTime;
extern int AmberTime;
extern int GreenTime;

extern int red_temp;
extern int amber_temp;
extern int green_temp;


#endif /* INC_GLOBAL_H_ */
