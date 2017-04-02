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
    DISP_SIZE = DEV_LAST,	/* ioctrl returns coord_t */
} disp_command_t;

typedef struct color_t_ {
	uint8_t rgb[3];
} color_t;

typedef struct coord_t_ {
	uint16_t xy[2];
} coord_t_;

typedef struct display_t_ {
	device_t device;
	elres_t (*set_pixel)(void * );
} display_t;

dev_handle emLibDisplay_init(device_t * hwDisplay);
elres_t emLibDisplay_free(dev_handle handle);
elres_t emLibDisplay_set_pixel(dev_handle handle, uint16_t x, uint16_t y, color_t *rgb);



#ifdef __cplusplus
}
#endif
#endif /* INC_EMLIB_DISPLAY_H_ */
