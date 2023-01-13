#include<stdio.h>
#include"pico/stdlib.h"

#define LED 25
#define BUTTON 24
#define RGB 23

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

void write_pin(int val)
{
    gpio_put(LED, val);
}
