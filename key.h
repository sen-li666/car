#ifndef APPLICATIONS_KEY_H_
#define APPLICATIONS_KEY_H_

#include <rtthread.h>
#include "drv_gpio.h"

#define USER_LED1   GET_PIN(0,0)
#define USER_KEY    GET_PIN(6,2)

#define USING_KEY_POLL


void key_led_init();
rt_err_t key_sample();




#endif /* APPLICATIONS_KEY_H_ */
