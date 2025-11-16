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


void doInit(){
	status = INIT;
	nextMenuState = INIT;
	button_init();
	setTimers(100);
}
