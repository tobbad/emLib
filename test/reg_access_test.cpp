

#include <iostream>
#include <cstdint>
#include "reg_access.h"
//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "config.h"

static const uint8_t RFSIZE=10;
uint32_t regField[RFSIZE];

/***************************************************************
 *
 * Test group for testing the register access template
 *
 **************************************************************/
TEST_GROUP(REGISTER_ACCESS) {

    uint32_t RFDEFAULT32 = 0xFFFFFFFF;

    void setup()
    {
        for (uint8_t i;i<RFSIZE;i++) {
            regField[i] = RFDEFAULT32;
        }
    }

    void clear()
    {
        for (uint8_t i=0;i<RFSIZE;i++) {
            regField[i] = 0;
        }
    }

    void teardown()
    {

    }

    void print(){
        printf("regField[%d] = [", RFSIZE);
        for (uint8_t i=0;i<RFSIZE;i++) {
            printf("0x%08X ", regField[i]);
        }
        printf("]\n");
    }

};

TEST(REGISTER_ACCESS, PRECONDITION)
{
    uint32_t ZERO=0;
    clear();
    for (uint8_t i;i<RFSIZE;i++) {
        CHECK_EQUAL(ZERO, regField[0]);
    }
}


TEST(REGISTER_ACCESS, U32REG_SET){
    static const uint32_t EXP = 42;
    common::reg<regField> u32Reg;
    u32Reg = EXP;
    CHECK_EQUAL(EXP, regField[0]);
    CHECK_EQUAL(RFDEFAULT32, regField[1]);
}


TEST(REGISTER_ACCESS, U32REG_GET){
    uint32_t obt;
    common::reg<regField> u32Reg;
    obt = u32Reg.value();
    CHECK_EQUAL(obt, regField[0]);
}

TEST(REGISTER_ACCESS, U32REG_AND){
    const uint32_t mask = 1;
    uint32_t obt;
    uint32_t reg_val;
    common::reg<regField> u32Reg;
    obt = u32Reg & mask;
    reg_val = u32Reg.value();
    CHECK_EQUAL(mask, obt);
    CHECK_EQUAL(RFDEFAULT32, reg_val);
    CHECK_EQUAL(RFDEFAULT32, regField[1]);
}

TEST(REGISTER_ACCESS, U32REG_AND_ASSIGN){
    const uint32_t mask = 1;
    uint32_t obt;
    uint32_t reg_val;
    common::reg<regField> u32Reg;
    obt = u32Reg &= mask;
    reg_val = u32Reg.value();
    CHECK_EQUAL(mask, obt);
    CHECK_EQUAL(mask, reg_val);
    CHECK_EQUAL(RFDEFAULT32, regField[1]);
}

TEST(REGISTER_ACCESS, U32REG_OR){
    const uint32_t mask = 1;
    uint32_t obt;
    common::reg<regField> u32Reg;
    clear();
    obt = u32Reg | mask;
    CHECK_EQUAL(mask, obt);
    CHECK_EQUAL(0, regField[0]);
    CHECK_EQUAL(0, regField[1]);
}

TEST(REGISTER_ACCESS, U32REG_OR_ASSIGN){
    const uint32_t mask = 1;
    common::reg<regField> u32Reg;
    uint32_t obt;
    clear();
    obt = u32Reg |= mask;
    CHECK_EQUAL(mask, obt);
    CHECK_EQUAL(mask, regField[0]);
    CHECK_EQUAL(u32Reg.value(), regField[0]);
    CHECK_EQUAL(0, regField[1]);
}

TEST(REGISTER_ACCESS, U32REG_NOT){
    const uint32_t exp = 0x12345678;
    regField[0]=~exp;
    uint32_t obt;
    common::reg<regField> u32Reg;
    obt = ~u32Reg;
    CHECK_EQUAL(obt, exp);
}
