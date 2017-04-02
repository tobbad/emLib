/*
 * mock_common.cpp
 *
 *  Created on: 26.03.2017
 *      Author: badi
 */
#include <stdio.h>
#include <string.h>
#include "common.h"

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

elres_t device_check(const device_t * dev, dev_func_t dev_type) {
    elres_t res = (elres_t)mock().actualCall("device_check")
          .withConstPointerParameter("dev", (void*)dev)
          .withIntParameter("dev_type", (int)dev_type)
          .returnIntValue();
    return res;
}


elres_t device_free(device_t * dev) {
    elres_t res = (elres_t)mock().actualCall("device_free")
          .withPointerParameter("dev", (void*)dev)
          .returnIntValue();
    return res;
}

void device_print(const device_t * dev){
    if (dev != NULL) {
        printf("open  = %p\n",dev->open);
        printf("read  = %p\n",dev->read);
        printf("write = %p\n",dev->write);
        printf("ioctrl= %p\n",dev->ioctrl);
        printf("close = %p\n",dev->close);
    }
}
