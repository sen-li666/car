
#include "key.h"
static uint8_t led_state = 0;

void key_led_init()
{
    rt_pin_mode(USER_LED1, PIN_MODE_OUTPUT);
    rt_pin_mode(USER_KEY,PIN_MODE_INPUT_PULLUP);

#ifdef USING_KEY_IRQ
    rt_pin_attach_irq(USER_KEY, PIN_IRQ_MODE_FALLING, key_irq_handler, RT_NULL);
    rt_pin_irq_enable(USER_KEY, PIN_IRQ_ENABLE);
#endif

}



#ifdef USING_KEY_POLL
static void key_thread_entry(void* parameter)
{
    while(1)
    {
        if(rt_pin_read(USER_KEY) == PIN_LOW)
        {
            rt_thread_mdelay(140);
            if(rt_pin_read(USER_KEY)== PIN_LOW)
            {
                if(led_state == 0)
                    rt_pin_write(USER_LED1, PIN_HIGH);
                else
                    rt_pin_write(USER_LED1,PIN_LOW);
                            led_state = ~led_state;

                }
            }
        rt_thread_mdelay(1);

        }
    }
#endif


rt_err_t key_sample()
{
    key_led_init();
#ifdef USING_KEY_POLL
    rt_thread_t tid1 = rt_thread_create("thread_key",key_thread_entry,RT_NULL,512,15,5);
    if(tid1 == RT_NULL)
    {
        rt_kprintf("create thread: key_poll failed\n");
        return -RT_ERROR;
    }
    rt_thread_startup(tid1);
#endif
    return RT_EOK;

}

INIT_APP_EXPORT(key_sample);

