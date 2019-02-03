#include "hal_defines.h"

#include "pin.h"
#include "MockPin.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

uint8_t periphery[0x50060C00 - 0x40000000];

class PINTest : public ::testing::Test {
    protected:

    void SetUp() override {
    }

    void TearDown() override
    {
    }

    MockPin pin;


};

TEST_F(PINTest, Read)
{
	bool exp, act;

	exp = true;
	EXPECT_CALL(pin, read()).Times(1).WillOnce(Return(exp));
	act = pin.read();
	ASSERT_EQ(act, exp);

	exp = false;
    EXPECT_CALL(pin, read()).Times(1).WillOnce(Return(exp));
	act = pin.read();
	ASSERT_EQ(act, exp);
}

TEST_F(PINTest, Write)
{
	bool value;
	elres_t exp, act;

	exp = EMLIB_OK;
	value = true;
	EXPECT_CALL(pin, write(value)).Times(1).WillOnce(Return(exp));
	act = pin.write(value);
	ASSERT_EQ(act, exp);
}
TEST_F(PINTest, Mode)
{
	elres_t exp, act;
	Pin::pin_mode_t mode = Pin::pin_mode_t::OUTPUT;

	exp = EMLIB_ERROR;
    EXPECT_CALL(pin, mode(mode)).Times(1).WillOnce(Return(exp));
	act = pin.mode(mode);
	ASSERT_EQ(act, exp);
}
