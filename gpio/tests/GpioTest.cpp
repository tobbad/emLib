#include "Gpio.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(Gpio)
{
  Gpio* gpio;

  void setup()
  {
    gpio = new Gpio();
  }
  void teardown()
  {
    delete gpio;
  }
};

TEST(Gpio, Create)
{
  FAIL("Start here");
}

