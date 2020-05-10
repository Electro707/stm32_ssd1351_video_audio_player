#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f1xx.h"
#include "stm32f1xx_ll_tim.h"

void initDelay(void);
void delayMs(volatile int ms);

#endif
