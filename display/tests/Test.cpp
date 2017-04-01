

#include "display.h"
#include "common.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

dev_handle dummy_open(void){ return 0; };
elres_t dummy_read(uint8_t *buffer, uint16_t cnt){ return EMLIB_ERROR;};
elres_t dummy_write(uint8_t *buffer, uint16_t cnt){ return EMLIB_ERROR;};
elres_t dummy_ioctrl(dev_command_t cmd, uint16_t value){ return EMLIB_ERROR;};
elres_t dummy_close(dev_handle hdl){ return EMLIB_ERROR;};


TEST_GROUP(DISPLAY) {
    
    device_t disp;

    void setup()
    {

        
    }
    
    void teardown()
    {

    }
    
    void init_struct(uint8_t select){
        uint8_t idx = 0;
        if (select & (1<<idx)) {
            disp.open = dummy_open;
        } else {
            disp.open = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
            disp.read = dummy_read;
        } else {
            disp.read = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
            disp.write = dummy_write;
        } else {
            disp.write = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
            disp.ioctrl = dummy_ioctrl;
        } else {
            disp.ioctrl = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
            disp.close = dummy_close;
        } else {
            disp.close = NULL;
        }
    }
};

TEST(DISPLAY, Create_with_null)
{
    dev_handle res = emLibDisplay_init(NULL);
    CHECK_EQUAL(DEV_HANDLE_NOTDEFINED, res);
    
}

TEST(DISPLAY, Create_with_missing_any_func)
{
    dev_handle res = emLibDisplay_init(&disp);
    CHECK_EQUAL(DEV_HANDLE_NOTDEFINED, res);
    
}

TEST(DISPLAY, Create_with_missing_function)
{
    uint8_t i;
    for ( i=0;i<(1<<5);i++) {
    	dev_handle res, exp = (i<((1<<5)-1))?DEV_HANDLE_NOTDEFINED:0;
        init_struct(i);
        res = emLibDisplay_init(&disp);
        CHECK_EQUAL(exp, res);
        emLibDisplay_reset(res);
    }
}



