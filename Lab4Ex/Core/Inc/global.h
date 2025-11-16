/*
 * global.h
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define INIT   1
#define AUTO   2
#define MANUAL 3
#define CONFIG 4

#include "software_timer.h"
#include "button.h"

extern int status;
extern int nextMenuState;
extern int flagMenuChange;

void doInit();

#endif /* INC_GLOBAL_H_ */
