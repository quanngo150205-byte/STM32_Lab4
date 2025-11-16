/*
 * traffic_light.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#include "traffic_light.h"

traffic_state trafState = START;

/* Ham chuyen den duong 1*/
void YellowToRed1(){
	HAL_GPIO_WritePin(GPIOA, LED_R_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_R_C_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_C_Pin, GPIO_PIN_SET);
}
void RedToGreen1(){
	HAL_GPIO_WritePin(GPIOA, LED_R_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_R_C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_C_Pin, GPIO_PIN_RESET);
}
void GreenToYellow1(){
	HAL_GPIO_WritePin(GPIOA, LED_G_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_G_C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_C_Pin, GPIO_PIN_RESET);
}

/* Ham chuyen den duong 2*/
void YellowToRed2(){
	HAL_GPIO_WritePin(GPIOA, LED_R_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_R_D_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_D_Pin, GPIO_PIN_SET);
}
void RedToGreen2(){
	HAL_GPIO_WritePin(GPIOA, LED_R_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_R_D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_D_Pin, GPIO_PIN_RESET);
}
void GreenToYellow2(){
	HAL_GPIO_WritePin(GPIOA, LED_G_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_G_D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_D_Pin, GPIO_PIN_RESET);
}


void clearAllLed(){
	HAL_GPIO_WritePin(LED_R_A_GPIO_Port,   LED_R_A_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_A_GPIO_Port,   LED_Y_A_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_A_GPIO_Port,   LED_G_A_Pin,     GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_R_B_GPIO_Port,   LED_R_B_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_B_GPIO_Port,   LED_Y_B_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_B_GPIO_Port,   LED_G_B_Pin,     GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_R_C_GPIO_Port,   LED_R_C_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_C_GPIO_Port,   LED_Y_C_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_C_GPIO_Port,   LED_G_C_Pin,     GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_R_D_GPIO_Port,   LED_R_D_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_D_GPIO_Port,   LED_Y_D_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_D_GPIO_Port,   LED_G_D_Pin,     GPIO_PIN_SET);
}
