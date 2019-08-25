

#include <iostream>
#include <cstdint>
#include "mcal_reg_access_tpl.h"
//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

static const uint8_t RFSIZE=10;
uint32_t regField[RFSIZE];

/***************************************************************
 *
 * Test group for testing the register access template
 *
 **************************************************************/
TEST_GROUP(REGISTER_ACCESS) {

    uint32_t RFDEFAULT32 = 0xFFFFFFFF;
    uint16_t RFDEFAULT16 = 0xFFFF;
    uint8_t RFDEFAULT8 = 0xFF;

    void setup()
    {
        for (uint8_t i;i<RFSIZE;i++) {
            regField[i] = RFDEFAULT32;
        }
    }

    void teardown()
    {

    }

};

TEST(REGISTER_ACCESS, U8REG_SET){
    static const uint32_t EXP = 42;
    mcal::reg::access<std::uint32_t*, std::uint8_t, regField, EXP>::reg_set();
    CHECK_EQUAL(EXP, reinterpret_cast<uint8_t*>(regField)[0]);
    CHECK_EQUAL(RFDEFAULT8, reinterpret_cast<uint8_t*>(regField)[1]);
}

TEST(REGISTER_ACCESS, U16REG_SET){
    static const uint32_t EXP = 1642;
    mcal::reg::access<std::uint32_t*, std::uint16_t, regField, EXP>::reg_set();
    CHECK_EQUAL(EXP, reinterpret_cast<uint16_t*>(regField)[0]);
    CHECK_EQUAL(RFDEFAULT16, reinterpret_cast<uint16_t*>(regField)[1]);
}

TEST(REGISTER_ACCESS, U32REG_SET){
    static const uint32_t EXP = 123121642;
    mcal::reg::access<std::uint32_t*, std::uint32_t, regField, EXP>::reg_set();
    CHECK_EQUAL(EXP, reinterpret_cast<uint32_t*>(regField)[0]);
    CHECK_EQUAL(RFDEFAULT32, reinterpret_cast<uint32_t*>(regField)[1]);
}


