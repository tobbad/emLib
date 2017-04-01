/*
 * display.h
 *
 * Module for generic handling of displays.
 *
 *  Created on: 09.12.2015
 *      Author: badi
 */

#ifndef INC_EMLIB_DISPLAY_H_
#define INC_EMLIB_DISPLAY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "display_conf.h"


typedef enum {
    DISP_ONE = DEV_LAST,
} disp_command_t;



dev_handle emLibDisplay_init(device_t * hwDisplay);
elres_t emLibDisplay_reset(dev_handle handle);


#ifdef __cplusplus
}
#endif
#endif /* INC_EMLIB_DISPLAY_H_ */
