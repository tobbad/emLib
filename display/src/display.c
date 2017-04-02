/*
 ============================================================================
 Name        : emLib_Display.c
 Author      : Tobias Badertscher
 Version     :
 Copyright   : BSD 2 claus licence
 Description : Library for displays in embedded systems
 ============================================================================
 */

/*
 * Include files
 */
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "display.h"
/*
 * Constants
 */

/*
 * Static variables
 */
STATIC device_t  display[MAX_DISPALY_HANDLE_CNT];
/*
 * Static functions
 */
static elres_t emLibDisplay_check_handle(dev_handle handle);
/*
 * Public function definitions
 */
dev_handle emLibDisplay_init(device_t * hwDisplay) {
    dev_handle hdl = DEV_HANDLE_NOTDEFINED;
    if ( EMLIB_OK == device_check(hwDisplay, DEV_ALL)) {
        for (uint8_t i=0;i< MAX_DISPALY_HANDLE_CNT;i++){
            if (EMLIB_OK == device_check(&display[i], DEV_NONE))
            {
                display[i] = *hwDisplay;
                hdl = i;
            }
        }
    }
    return hdl;
}

elres_t emLibDisplay_free(dev_handle handle) {
    elres_t res = EMLIB_ERROR;
    if ( EMLIB_OK == emLibDisplay_check_handle(handle) ) {
  		res = device_free(&display[handle]);
    }
    return res;
}

elres_t emLibDisplay_set_pixel(dev_handle handle, uint16_t x, uint16_t y, color_t *rgb) {
	elres_t res =EMLIB_ERROR;
    if ( EMLIB_OK == emLibDisplay_check_handle(handle) ) {
		res = EMLIB_OK;
	}
	return res;
}

/******************************************************************************
 *
 * Static function definitions
 *
 */
static elres_t emLibDisplay_check_handle(dev_handle handle) {
    elres_t res = EMLIB_ERROR;
    if ( (handle>DEV_HANDLE_NOTDEFINED) && (handle<MAX_DISPALY_HANDLE_CNT))
    {
    	if ( EMLIB_OK == device_check(&display[handle], DEV_ALL) ) {
    		res = EMLIB_OK;
    	}
    }
    return res;
}
