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

void set_led()
{
    gpio_put(LED, 1);
}