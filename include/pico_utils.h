#ifndef PICO_UTILS
#define PICO_UTILS

#include<stdio.h>
#include"pico/stdlib.h"

#define LED 25
#define BUTTON 24
#define NEO 23

void init_button()
{
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
}

uint8_t get_button()
{
    return !gpio_get(BUTTON);
}

void init_led()
{
    gpio_init(LED);
    sleep_ms(2);
    gpio_set_dir(LED, GPIO_OUT);
}

void init_neo()
{
    gpio_init(NEO);
    gpio_set_dir(NEO, GPIO_OUT);
}

#ifdef IR
void init_ir()
{
    gpio_init(IR);
    gpio_set_dir(IR, GPIO_IN);
    gpio_pull_up(IR);
}

uint64_t get_ir()
{
    if(!gpio_get(IR))
    {
        uint64_t fin = 0;
        uint8_t newValue, oldValue = 0, last = 0;
        for(int i = 0; i < 350; i++)
        {
            newValue = gpio_get(IR);
            if(newValue != oldValue)
            {
                fin |= (i - last < 5);
                fin <<= 1;
                last = i;
            }
            oldValue = newValue;
            sleep_us(200);
        }
        return fin;
    }
    return 0;
}
#endif /*IR*/

#endif /*PICO_UTILS*/
