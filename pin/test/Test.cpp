#include "Pin.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(Pin)
{
  Pin* gpio;

  void setup()
  {
    gpio = new Pin();
  }
  void teardown()
  {
    delete gpio;
  }
};

TEST(Pin, Create)
{
  FAIL("Start here");
}

