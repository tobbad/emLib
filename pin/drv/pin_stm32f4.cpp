/*
 * PinStm32f4.cpp
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#include "pin_stm32f4.h"
#include "stm32f4xx_hal_gpio.h"


PinStm32f4::PinStm32f4(Port::port_t port, Pin::pin_t pin):
Pin(port, pin) {
	pin_conf.Pin = GPIO_PIN_5;
	pin_conf.Mode = GPIO_MODE_OUTPUT_PP;
	pin_conf.Pull = GPIO_PULLUP;
	pin_conf.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init()
}


bool PinStm32f4::read(){
	bool ret = true;

	return ret;
};

elres_t PinStm32f4::write(bool value){
	elres_t ret =EMLIB_OK;
	return ret ;

};

elres_t PinStm32f4::mode(pin_mode_t mode){
	elres_t ret =EMLIB_OK;
	return ret ;
};

