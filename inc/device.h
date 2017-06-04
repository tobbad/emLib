/*
 * device.h
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#ifndef INC_DEVICE_H_
#define INC_DEVICE_H_

class device {

	virtual void device(dev_type_t device) = 0;
	virtual ~device();
};



#endif /* INC_DEVICE_H_ */
