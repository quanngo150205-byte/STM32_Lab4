/*
 * fsm_automatic.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ngoqu
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	traffic_light_autorun(GREEN_TIME + YELLOW_TIME, YELLOW_TIME, GREEN_TIME);
}
