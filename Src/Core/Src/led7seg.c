/*
 * led7seg.c
 *
 *  Created on: Sep 20, 2023
 *      Author: PC
 */

#include "led7seg.h"

//char AnodeNumber[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0x8F,0x80,0x90,0x80}; //0 - 9,dp

/*void display7SEG(int num) {
	HAL_GPIO_WritePin(LED7SEG_A_GPIO_Port, LED7SEG_A_Pin, AnodeNumber[num]&0x01?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_B_GPIO_Port, LED7SEG_B_Pin, AnodeNumber[num]&0x02?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_C_GPIO_Port, LED7SEG_C_Pin, AnodeNumber[num]&0x04?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_D_GPIO_Port, LED7SEG_D_Pin, AnodeNumber[num]&0x08?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_E_GPIO_Port, LED7SEG_E_Pin, AnodeNumber[num]&0x10?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_F_GPIO_Port, LED7SEG_F_Pin, AnodeNumber[num]&0x20?SET:RESET);
	HAL_GPIO_WritePin(LED7SEG_G_GPIO_Port, LED7SEG_G_Pin, AnodeNumber[num]&0x40?SET:RESET);

}*/
