/*
 * mock_common.cpp
 *
 *  Created on: 26.03.2017
 *      Author: badi
 */

elres_t device_check(device_t * dev, dev_func_t dev_type) {
	bool is_ok=true;
	return is_ok?EMLIB_OK:EMLIB_ERROR;
}


void device_reset(device_t * dev) {

	dev->open = NULL;
	dev->read = NULL;
	dev->write = NULL;
	dev->ioctrl = NULL;
	dev->close = NULL;
	return;
}
