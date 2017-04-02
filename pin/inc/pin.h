#ifndef D_Pin_H
#define D_Pin_H

///////////////////////////////////////////////////////////////////////////////
//
//  Pin is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "port_type.h"

class Pin {
	public:
		enum class pin_t {
			PIN_NA=-1,
			PIN_0,
			PIN_1,
			PIN_2,
			PIN_3,
			PIN_4,
			PIN_5,
			PIN_6,
			PIN_7,
			PIN_8,
			PIN_9,
			PIN_10,
			PIN_11,
			PIN_12,
			PIN_13,
			PIN_14,
			PIN_15,
		};

		enum class pin_mode_t {
			OUTPUT = 1,
			INPUT  = 2,
		};

	public:
		virtual ~Pin() {};
		virtual bool 	read() = 0;
		virtual elres_t write(bool value) = 0;
		virtual elres_t mode(pin_mode_t mode) = 0;


	private:
		Pin& operator=(const Pin&);

	protected:
		Pin(Port::port_t port, Pin::pin_t pin):port(port), pin(pin){};
		Pin():port(Port::port_t::PORT_NA), pin(Pin::pin_t::PIN_NA){};
		Port::port_t port;
		Pin::pin_t pin;

	public:

};

#endif  // D_Pin_H
