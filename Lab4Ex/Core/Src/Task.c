/*
 * Task.c
 *
 *  Created on: Nov 28, 2025
 *      Author: ngoqu
 */

#include "Task.h"

void BlinkLed(){
	if (isTimerExpired(TIMER_FOR_LED_PA5)){
		HAL_GPIO_TogglePin(GPIOA, LED_BLINK_Pin);
		setTimer(TIMER_FOR_LED_PA5, LED_PA5_CYCLE);
	}
}

void fsm_run_all(){
	fsm_automatic_run();
	fsm_manual_run();
	fsm_config_run();
	fsm_pedestrian_run();
}

void doInit(){
	status = INIT;
	setTimers(100);
	clear7Seg();
	clearAllLed();
	button_init();
	display_lcd_init();

	/* Khoi tao gia tri mac dinh cho che do Config (don vi: giay) */
	red_temp   = DEFAULT_REDTIME   / 1000;
	amber_temp = DEFAULT_AMBERTIME / 1000;
	green_temp = DEFAULT_GREENTIME / 1000;

	flagchangeMode = 1; /* Tu dong chuyen sang RED_GREEN khi bat nguon */
}
