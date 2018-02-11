

#include <iostream>
#include <cstdint>
#include "mcal_reg_access_tpl.h"
//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

template<typename REG_T>
class UART {
public:
    UART(REG_T * baseaddr):
    base_addr(baseaddr){};

    REG_T value(){ return *base_addr; };
private:
    REG_T * base_addr;
};

template<typename REG_T, REG_T * baseaddr>
class UART_1 {
public:
    UART_1(){};

    REG_T value(){ return *baseaddr; };
private:
};

template<uintptr_t baseaddr>
class UART_2 {
public:
    UART_2(){};

    static uint32_t reg_get() { return *reinterpret_cast<volatile uint32_t*>(baseaddr); }
    uint32_t value(){ return *reinterpret_cast<uint32_t*>(baseaddr); };
private:
};

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


#if 0
TEST(REGISTER_ACCESS, U8REG_READ_0){
    uint32_t value=42;
    UART<uint32_t> uart(&value);
    value=0;
    CHECK_EQUAL(uart.value(), regField[0]);
}

TEST(REGISTER_ACCESS, U8REG_READ_1){
    uint32_t value=42;
    UART_1<uint32_t, &value> uart;
    value=0;
    CHECK_EQUAL(uart, regField[0]);
}

TEST(REGISTER_ACCESS, U8REG_READ_2){
    uint32_t value=42;
    UART_2<&value> uart;
    value=0;
    CHECK_EQUAL(uart.value(), regField[0]);
}

//extern uint32_t value[];
uint32_t value[42] = {42};

TEST(REGISTER_ACCESS, U8REG_READ_1_1){
    UART_1<uint32_t, regField> uart;
    regField[0]=0;
    CHECK_EQUAL(uart.value(), regField[0]);
}
#endif


