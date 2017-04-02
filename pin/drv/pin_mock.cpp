/*
 * PinMock.cpp
 *
 *  Created on: 02.04.2017
 *      Author: badi
 */

#include "pin_mock.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"



bool PinMock::read(){
	bool ret = mock().actualCall("read")
					 .onObject(this)
					 .returnBoolValue();
	return ret;
};

elres_t PinMock::write(bool value){
	uint32_t ret = mock().actualCall("write")
					 .onObject(this)
					 .withParameter("value", value)
					 .returnIntValue();
	return static_cast<elres_t>(ret);

};

elres_t PinMock::mode(pin_mode_t mode){
	uint32_t ret = mock().actualCall("mode")
					 .onObject(this)
					 .withParameter("mode", static_cast<uint32_t>(mode))
					 .returnIntValue();
	return static_cast<elres_t>(ret);
};

