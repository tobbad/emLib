/*
 * port_type.h
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#ifndef PORT_INC_PORT_TYPE_H_
#define PORT_INC_PORT_TYPE_H_


namespace Port {

enum class port_t {
	PORT_NA=-1,
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORT_CNT
};

enum class port_width_t {
	PORT_8,
	PORT_16,
	PORT_32,
};

}

#endif /* PORT_INC_PORT_TYPE_H_ */
