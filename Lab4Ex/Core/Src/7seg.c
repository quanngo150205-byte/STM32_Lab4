/*
 * 7 seg.c
 *
 *  Created on: Nov 1, 2025
 *      Author: ngoqu
 */

#include "7seg.h"

int currentEN = 0;
int timer_buffer[NUM_OF_7SEG_LED] = {0};

void display7SegLed(){
	if (currentEN == 0){
		displayDigit1(timer_buffer[0]);
		displayDigit2(timer_buffer[1]);
		HAL_GPIO_WritePin(GPIOB, EN0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin, GPIO_PIN_SET);
		currentEN = 1;
	}
	else {
		displayDigit1(timer_buffer[2]);
		displayDigit2(timer_buffer[3]);
		HAL_GPIO_WritePin(GPIOB, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin, GPIO_PIN_RESET);
		currentEN = 0;
	}
}

void updateTimerBuffer(int counter1, int counter2){
	int sec1 = counter1 / 100;
	int sec2 = counter2 / 100;
	timer_buffer[0] = sec1 / 10;
	timer_buffer[1] = sec1 % 10;
	timer_buffer[2] = sec2 / 10;
	timer_buffer[3] = sec2 % 10;
}

void clear7Seg(){
	HAL_GPIO_WritePin(GPIOB, EN0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, EN1_Pin, GPIO_PIN_SET);
	displayDigit1(10);
	displayDigit2(10);
}

//ham hien led 7 doan
void displayDigit1 (int num) {
    switch (num) {
        case 0:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
        	break;
        case 6:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
            break;
        case 8:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
            break;
        default:
            HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
            break;
    }
}

void displayDigit2 (int num) {
    switch (num) {
        case 0:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);
        	break;
        case 6:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_SET);
            break;
        case 8:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);
            break;
        default:
            HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E1_GPIO_Port, E1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(F1_GPIO_Port, F1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_SET);
            break;
    }
}
