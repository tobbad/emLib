/*
 * hal_defines.h
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#ifndef PIN_TEST_HAL_DEFINES_H_
#define PIN_TEST_HAL_DEFINES_H_
#include "stdint.h"


#ifdef STM32
extern uint8_t 	periphery[];
#define PERIPH_BASE		periphery
#endif



#endif /* PIN_TEST_HAL_DEFINES_H_ */
