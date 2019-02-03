/*
 * Pin.cpp
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#include "pin.h"

#include "stm32f4xx_hal_gpio.h"


Pin::Pin(Port::port_t port, Pin::pin_t pin):pin(pin), port(port){}


bool Pin::read(){
	bool ret = true;

	return ret;
};

elres_t Pin::write(bool value){
	elres_t ret =EMLIB_OK;
	return ret ;

};

elres_t Pin::mode(pin_mode_t mode){
	elres_t ret =EMLIB_OK;
	return ret ;
};

