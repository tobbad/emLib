

#include "pin_mock.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(PIN) {

	Pin * pin;

	void setup()
	{
		pin = new PinMock(Port::port_t::PORTA, Pin::pin_t::PIN_0);
	}

	void teardown()
	{
		delete pin;
	}
};

TEST(PIN, Read)
{
	bool exp, act;

	exp = true;
	mock().expectOneCall("read").onObject(pin).andReturnValue(exp);
	act = pin->read();
	CHECK_EQUAL(act, exp);

	exp = false;
	mock().expectOneCall("read").onObject(pin).andReturnValue(exp);
	act = pin->read();
	CHECK_EQUAL(act, exp);
}

TEST(PIN, Write)
{
	bool value;
	elres_t exp, act;

	exp = EMLIB_OK;
	value = true;
	mock().expectOneCall("write").onObject(pin).withParameter("value", value).andReturnValue(exp);
	act = pin->write(value);
	CHECK_EQUAL(act, exp);
}

TEST(PIN, Mode)
{
	elres_t exp, act;
	Pin::pin_mode_t mode = Pin::pin_mode_t::OUTPUT;

	exp = EMLIB_ERROR;
	mock().expectOneCall("mode").onObject(pin).withParameter("mode", static_cast<uint32_t>(mode)).andReturnValue(exp);
	act = pin->mode(mode);
	CHECK_EQUAL(act, exp);
}

