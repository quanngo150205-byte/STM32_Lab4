/*
 * traffic_light.h
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#define PREIOD_SCAN_7SEG_LED		80
#define PREIOD_UPDATE_TIME_BUFFER	500

#include "main.h"
#include "global.h"
#include "7seg.h"

typedef enum {
		START, RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED, RED_GREENBLINK, GREENBLINK_RED
}traffic_state;

extern traffic_state trafState;

/* Ham chuyen den duong 1*/
void YellowToRed1();
void RedToGreen1();
void GreenToYellow1();

/* Ham chuyen den duong 2*/
void YellowToRed2();
void RedToGreen2();
void GreenToYellow2();

void clearAllLed();
void traffic_light_run(int, int, int);
#endif /* INC_TRAFFIC_LIGHT_H_ */
