/*
 * GPIO.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ngoqu
 */
#include "GPIO.h"

void LED_PA5_toggle(){
	HAL_GPIO_TogglePin(GPIOA, LED_BLINK_Pin);
}

void ALL_RED_toggle(){
    HAL_GPIO_TogglePin(GPIOA, LED_R_A_Pin | LED_R_B_Pin | LED_R_C_Pin | LED_R_D_Pin);
}

void ALL_YELLOW_toggle(){
	HAL_GPIO_TogglePin(GPIOA, LED_Y_A_Pin | LED_Y_B_Pin | LED_Y_C_Pin | LED_Y_D_Pin);
}

void ALL_GREEN_toggle(){
	HAL_GPIO_TogglePin(GPIOA, LED_G_A_Pin | LED_G_B_Pin | LED_G_C_Pin | LED_G_D_Pin);
}

void BLINK_GREEN_ROAD1(){
	HAL_GPIO_TogglePin(GPIOA, LED_G_A_Pin|LED_G_C_Pin);
}

void BLINK_GREEN_ROAD2(){
	HAL_GPIO_TogglePin(GPIOA, LED_G_B_Pin|LED_G_D_Pin);
}
