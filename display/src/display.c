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
static device_t  display[MAX_DISPALY_HANDLE_CNT];
/*
 * Static functions
 */
/*
 * Public function definitions
 */
dev_handle emLibDisplay_init(device_t * hwDisplay) {
    dev_handle hdl = DEV_HANDLE_NOTDEFINED;
    if ( (NULL != hwDisplay) && 
         (EMLIB_OK == device_check(hwDisplay, DEV_ALL))) {
    	for (uint8_t i=0;i< MAX_DISPALY_HANDLE_CNT;i++){
			if (display[i].open == NULL)
			{
				hdl = i;
			}
    	}
    }
    return hdl;
}

void emLibDisplay_reset(void) {
	device_reset(display);
}

/*
 * Static function definitions
 */
/*
 *
 */
