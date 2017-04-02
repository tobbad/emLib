/*
 * PinStm32f4.h
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#ifndef PIN_DRV_PINMOCK_H_
#define PIN_DRV_PINMOCK_H_
#include "common.h"
#include "pin.h"
#include "port_type.h"

class PinStm32f4: public Pin {

public:
	PinStm32f4(Port::port_t port, Pin::pin_t pin):Pin(port, pin){};
	~PinStm32f4(){};
	bool 	read();
	elres_t write(bool value);
	elres_t mode(pin_mode_t mode);
protected:
	PinStm32f4(){};

private:
	static const Port::port_t MAX_PORT = Port::port_t::PORTD;
	static const Port::port_width_t PORT_WIDTH = Port::port_width_t::PORT_16;

};



#endif /* PIN_DRV_PINMOCK_H_ */
