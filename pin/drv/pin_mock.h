/*
 * PinMock.h
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#ifndef PIN_DRV_PINMOCK_H_
#define PIN_DRV_PINMOCK_H_
#include "common.h"
#include "pin.h"
#include "port_type.h"

class PinMock: public Pin {

public:
	PinMock(Port::port_t port, Pin::pin_t pin):Pin(port, pin){};
	~PinMock(){};
	bool 	read();
	elres_t write(bool value);
	elres_t mode(pin_mode_t mode);
protected:
	PinMock(){};

private:
	static const Port::port_t MAX_PORT = Port::port_t::PORTD;
	static const Port::port_width_t PORT_WIDTH = Port::port_width_t::PORT_16;

};



#endif /* PIN_DRV_PINMOCK_H_ */
