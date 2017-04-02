#include "Pin.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(Pin) {
	Pin* pin;

	void setup()
	{
		pin = new Pin();
	}
	void teardown()
	{
		delete pin;
	}
};

TEST(Pin, Create)
{
  FAIL("Start here");
}

