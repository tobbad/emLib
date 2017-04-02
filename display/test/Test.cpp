

#include "display.h"
#include "common.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

static void init_struct(device_t *disp, uint8_t select);
dev_handle dummy_open(void){ return 0; };
elres_t dummy_read(uint8_t *buffer, uint16_t cnt){ return EMLIB_ERROR;};
elres_t dummy_write(uint8_t *buffer, uint16_t cnt){ return EMLIB_ERROR;};
elres_t dummy_ioctrl(dev_command_t cmd, uint16_t value){ return EMLIB_ERROR;};
elres_t dummy_close(dev_handle hdl){ return EMLIB_ERROR;};

#ifdef UNIT_TEST
extern STATIC device_t  display[];
#endif


static void init_struct(device_t *disp, uint8_t select){
    uint8_t idx = 0;
    if (select & (1<<idx)) {
        disp->open = dummy_open;
    } else {
        disp->open = NULL;
    }
    idx++;
    if (select & (1<<idx)) {
        disp->read = dummy_read;
    } else {
        disp->read = NULL;
    }
    idx++;
    if (select & (1<<idx)) {
        disp->write = dummy_write;
    } else {
        disp->write = NULL;
    }
    idx++;
    if (select & (1<<idx)) {
        disp->ioctrl = dummy_ioctrl;
    } else {
        disp->ioctrl = NULL;
    }
    idx++;
    if (select & (1<<idx)) {
        disp->close = dummy_close;
    } else {
        disp->close = NULL;
    }
}



TEST_GROUP(DISPLAY_CREATE_FREE) {
    
    device_t disp;

    void setup()
    {
        init_struct(&disp, DEV_NONE);
    }
    
    void teardown()
    {

    }
    
};

TEST(DISPLAY_CREATE_FREE, Create_with_dev_check_return_error_on_NULL) {
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)NULL)
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_ERROR);
    dev_handle res = emLibDisplay_init(NULL);
    CHECK_EQUAL(DEV_HANDLE_NOTDEFINED, res);
    
}

TEST(DISPLAY_CREATE_FREE, Create_with_missing_any_func) {
    dev_handle act, exp = DEV_HANDLE_NOTDEFINED;
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&disp)
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_ERROR);
    act = emLibDisplay_init(&disp);
    CHECK_EQUAL(exp, act);
    
}

TEST(DISPLAY_CREATE_FREE, Create_no_dev_free) {
    dev_handle act[2];
    dev_handle exp[2] = {0, DEV_HANDLE_NOTDEFINED};
    init_struct(&disp, DEV_ALL);
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&disp)
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_OK);
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_NONE)
		  .andReturnValue(EMLIB_OK);
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&disp)
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_OK);
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_NONE)
		  .andReturnValue(EMLIB_ERROR);

    act[0] = emLibDisplay_init(&disp);
    act[1] = emLibDisplay_init(&disp);
    
    CHECK_EQUAL(exp[0], act[0]);
    CHECK_EQUAL(exp[1], act[1]);
    
}

/*
 * Test reset display with invalid handle (to big to small not created)
 * and created structure.
 */
TEST(DISPLAY_CREATE_FREE, Reset_on_not_created) {
	elres_t    act, exp;
	exp = EMLIB_ERROR;

	act = emLibDisplay_free(-1);
    CHECK_EQUAL(exp, act);

	act = emLibDisplay_free(MAX_DISPALY_HANDLE_CNT);
    CHECK_EQUAL(exp, act);

    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_ERROR);
	act = emLibDisplay_free(0);
    CHECK_EQUAL(exp, act);

    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_OK);
    mock().expectOneCall("device_free")
    	  .withPointerParameter("dev", (void*)&display[0])
		  .andReturnValue(EMLIB_ERROR);
	act = emLibDisplay_free(0);
    CHECK_EQUAL(exp, act);

	exp = EMLIB_OK;
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_OK);
    mock().expectOneCall("device_free")
    	  .withPointerParameter("dev", (void*)&display[0])
		  .andReturnValue(EMLIB_OK);
	act = emLibDisplay_free(0);
    CHECK_EQUAL(exp, act);
}

TEST_GROUP(DISPLAY_PAINT) {

    device_t disp;
    color_t  rgb;

    void setup()
    {
        init_struct(&disp, DEV_ALL);
    }

    void teardown()
    {

    }
};

TEST(DISPLAY_PAINT, pre_cond_check) {
	dev_handle hdl;
	elres_t    act, exp;
	exp = EMLIB_ERROR;

	act = emLibDisplay_set_pixel(DEV_HANDLE_NOTDEFINED, 0, 0, &rgb);
    CHECK_EQUAL(exp, act);

	act = emLibDisplay_set_pixel(MAX_DISPALY_HANDLE_CNT, 0, 0, &rgb);
    CHECK_EQUAL(exp, act);
    /*
     * Call function on not created display must fail.
     */
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_ERROR);
	act = emLibDisplay_set_pixel(0, 0, 0, &rgb);
    CHECK_EQUAL(exp, act);
    /*
     * Create device
     */
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&disp)
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_OK);
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_NONE)
		  .andReturnValue(EMLIB_OK);
    hdl = emLibDisplay_init(&disp);
    CHECK_EQUAL(0, hdl);
    /*
     * Call function on created display must succeed.
     */
    mock().expectOneCall("device_check")
    	  .withConstPointerParameter("dev", (void*)&display[0])
		  .withIntParameter("dev_type",(int)DEV_ALL)
		  .andReturnValue(EMLIB_OK);
    exp = EMLIB_OK;
	act = emLibDisplay_set_pixel(hdl, 0, 0, &rgb);
    CHECK_EQUAL(exp, act);
}

