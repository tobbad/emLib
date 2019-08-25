/*
 * MockPin.h
 *
 *  Created on: 03.02.2019
 *      Author: badi
 */

#ifndef PIN_TEST_MOCKPIN_H_
#define PIN_TEST_MOCKPIN_H_


#include "gmock/gmock.h"
#include "pin.h"
#include "common.h"

class MockPin : public Pin {
    public:
        MOCK_METHOD0(read, bool());
        MOCK_METHOD1(write, elres_t(bool));
        MOCK_METHOD1(mode, elres_t(pin_mode_t));
};


#endif /* PIN_TEST_MOCKPIN_H_ */
