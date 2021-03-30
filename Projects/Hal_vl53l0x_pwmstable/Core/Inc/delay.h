#ifndef __DELAY_H
#define __DELAY_H
#include "main.h"
#include "stm32f4xx_hal_cortex.h"
void delay_init(uint8_t SYSCLK);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void Get_Time(float *time);
void start_Time(void);
#endif

