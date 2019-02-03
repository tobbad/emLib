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
			INPUT     = 0,
			OUTPUT    = 1,
			OUTPUT_OD = 2,
			PULL_NO   = 3,
			PULL_UP   = 4,
			PULL_DOWN = 5,
			SPEED_LOW = 6,
			SPEED_MEDIUM= 7,
			SPEED_HIGH 	= 8,
			SPEED_VERY_HIGH = 9,
		};

	public:
        Pin(Port::port_t port, Pin::pin_t pin);
		virtual ~Pin() {};
		virtual bool 	read();
		virtual elres_t write(bool value);
		virtual elres_t mode(pin_mode_t mode);


	private:
		Pin& operator=(const Pin&);

	protected:
		Pin():port(Port::port_t::PORT_NA), pin(Pin::pin_t::PIN_NA){};
		Port::port_t port;
		Pin::pin_t pin;

	public:

};



#endif  // D_Pin_H
