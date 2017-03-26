

#include "common.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

dev_handle dummy_open(void){ return 0; };
elres_t dummy_read(uint8_t *buffer, uint16_t cnt){ return EMLIB_ERROR;};
elres_t dummy_write(uint8_t *buffer, uint16_t cnt){ return EMLIB_ERROR;};
elres_t dummy_ioctrl(dev_command_t cmd, uint16_t value){ return EMLIB_ERROR;};
elres_t dummy_close(dev_handle hdl){ return EMLIB_ERROR;};


TEST_GROUP(DEVICE) {
    
    device_t dev;

    void setup()
    {

        
    }
    
    void teardown()
    {

    }
    
    void init_struct(uint8_t select){
        uint8_t idx = 0;
        if (select & (1<<idx)) {
        	dev.open = dummy_open;
        } else {
        	dev.open = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
        	dev.read = dummy_read;
        } else {
        	dev.read = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
        	dev.write = dummy_write;
        } else {
        	dev.write = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
        	dev.ioctrl = dummy_ioctrl;
        } else {
        	dev.ioctrl = NULL;
        }
        idx++;
        if (select & (1<<idx)) {
        	dev.close = dummy_close;
        } else {
        	dev.close = NULL;
        }
    }
};
/*
 * Check that the internal used function(s) work correct
 */
TEST(DEVICE, internal_init_struct){
	for (uint8_t i=0;i<=DEV_ALL;++i)
	{
		init_struct(i);
		if (i & DEV_OPEN  ){
        	CHECK_EQUAL(dev.open, dummy_open);
		} else {
        	CHECK(dev.open==NULL);

		}
		if (i & DEV_READ  ){
			CHECK_EQUAL(dev.read  , dummy_read);
		} else {
        	CHECK(dev.read==NULL);

		}
		if (i & DEV_WRITE ){
	    	CHECK_EQUAL(dev.write , dummy_write);
		} else {
        	CHECK(dev.write==NULL);

		}
		if (i & DEV_IOCTRL){
	    	CHECK_EQUAL(dev.ioctrl, dummy_ioctrl);
		} else {
        	CHECK(dev.ioctrl==NULL);

		}
		if (i & DEV_CLOSE ){
	    	CHECK_EQUAL(dev.close , dummy_close);
		} else {
        	CHECK(dev.close==NULL);

		}
	}
}

/*
 * Check reset of structure (setting is checked above)
 */
TEST(DEVICE, Device_reset){

	init_struct(DEV_ALL);

	device_reset(&dev);

	CHECK(NULL==dev.open);
	CHECK(NULL==dev.read);
	CHECK(NULL==dev.write);
	CHECK(NULL==dev.ioctrl);
	CHECK(NULL==dev.close);

}

/*
 * Test if a device structure with the function set is only
 * accepted as correct in the device_check if related functions
 * exist.
 */
TEST(DEVICE, Create_with_missing_function)
	{
    uint8_t i,j;
    for ( i=0;i<(1<<5);i++) {
		init_struct(i);
        for ( j=0;j<(1<<5);j++) {
			dev_handle act;
			/* If more than needed function are defined - that's OK! */
			dev_handle exp = ((i&j)==j)?EMLIB_OK:EMLIB_ERROR;
			act = device_check(&dev,(dev_func_t)j);
			CHECK_EQUAL(exp, act);
        }
   }
}



