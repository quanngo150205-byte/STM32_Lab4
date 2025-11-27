/*
 * button_even.c
 *
 *  Created on: Nov 28, 2025
 *      Author: ngoqu
 */

#include "button_event.h"

void getModeFlag();
void getManualFlag();
void getConfigFlag();

void button_event_scan(){
	//scan tio change state in Manual mode
	getManualFlag();

	//scan to change state in Config mode
	getConfigFlag();

	//change between Auto - Manual - Config
	getModeFlag();
}

void getModeFlag(){
	if (isButtonPressed(0)){
		flagchangeMode = 1;
	}
}

void getConfigFlag(){
	if (status == CONFIG_AMBER ||
		status == CONFIG_GREEN ||
		status == CONFIG_RED){
		if (isButtonDoubleClicked(2)){
			flagcontrolConfig = 1;
		}
	}
}

void getManualFlag(){
	if (status == MANUAL 		||
		status == MAN_AMBER_RED ||
		status == MAN_GREEN_RED	||
		status == MAN_RED_AMBER 	||
		status == MAN_RED_GREEN){
		if (isButtonPressed(1)){
			flagcontrolManual = 1;
		}
	}
}

