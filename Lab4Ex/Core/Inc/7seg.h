/*
 * 7seg.h
 *
 *  Created on: Nov 1, 2025
 *      Author: ngoqu
 */

#ifndef INC_7SEG_H_
#define INC_7SEG_H_
#define NUM_OF_7SEG_LED  4

#include "global.h"
#include "traffic_light.h"

void updateTimerBuffer(int,int);
void displayDigit1(int);
void displayDigit2(int);
void clear7Seg();
void display7SegLed();

#endif /* INC_7SEG_H_ */
