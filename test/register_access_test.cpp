

#include <iostream>
#include <cstdint>
#include "mcal_reg_access_tpl.h"
//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

uint32_t regField[10]={0};

/***************************************************************
 *
 * Test group for testing the register access template
 *
 **************************************************************/
TEST_GROUP(REGISTER_ACCESS) {


    void setup()
    {


    }

    void teardown()
    {

    }

};

TEST(REGISTER_ACCESS, U8REG_READ){
    static const uint32_t EXP = 342;
	mcal::reg::access<std::uint32_t*, std::uint8_t, regField, EXP>::reg_set();
    CHECK_EQUAL(EXP, regField[0]);
}


