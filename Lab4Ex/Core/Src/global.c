/*
 * global.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ngoqu
 */

#include "global.h"

int status = 0;
int nextMenuState = 0;
int flagMenuChange = 0;

ManualEvent manEvt = EV_NONE;
ManualState man_state = MAN_RED;

void doInit(){
	status = INIT;
	nextMenuState = INIT;
	button_init();
	setTimers(100);
}
