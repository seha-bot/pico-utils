#define IR 29
#include"pico_utils.h"
#include<time.h>

void c_init()
{
    init_ir();
    init_led();
    init_button();
    gpio_put(LED, 1);
}

uint8_t decode(uint64_t ir)
{
    switch(ir)
    {
        case 0xfffbfffefafefa00: return 0;
        case 0xfffbfffffefffef8: return 1;
        case 0xfffbfffefefefec0: return 2;
        case 0xfffbffffbeffbec0: return 3;
        case 0xfffbfffebefebe00: return 4;
        case 0xfffbffffeeffeec0: return 5;
        case 0xfffbfffeeefeee00: return 6;
        case 0xfffbffffaeffae00: return 7;
        case 0xfffbfffeaefea000: return 8;
        case 0xfffbfffffafffac0: return 9;
        case 0xfffbfffefbeefb00: return 10;
        default: return 11;
    }
    // switch(ir)
    // {
    //     case 0xaffeaffefeffa800: return 0;
    //     case 0xaffeafffeffeb800: return 1;
    //     case 0xaffeaffeefffb800: return 2;
    //     case 0xaffeafffaffef800: return 3;
    //     case 0xaffeaffffbfea800: return 4;
    //     case 0xaffeaffefbffa800: return 5;
    //     case 0xaffeafffbbfee800: return 6;
    //     case 0xaffeafffebfeb800: return 7;
    //     case 0xaffeaffeebffb800: return 8;
    //     case 0xaffeafffabfef800: return 9;
    //     case 0xaffeaffffbaea000: return 10;
    //     default: return 11;
    // }
}

uint16_t hash_32(uint32_t n)
{
    return (n & 0xffff) ^ ((n >> 16) & 0xffff);
}

uint16_t rand(uint32_t seed)
{
    return hash_32(hash_32(seed * 654) * hash_32(seed * 54323));
}

uint8_t input = 0;
uint16_t user = 0;
uint64_t seed = 0;
time_t offset = 0;

uint8_t locked = 0;
uint8_t button = 0;

void toggle_lock()
{
    locked = !locked;
    gpio_put(LED, !locked);
    user = 0;
}
uint8_t mode_toggle()
{
    if(get_button() && !button && !locked)
    {
        printf("BUTTON DOWN\n");
        seed = 0;
        button = 1;
        return 1;
    }
    else if(!get_button() && button && !locked)
    {
        printf("BUTTON UP\n");
        offset = time(0);
        button = 0;
        return 1;
    }
    return 0;
}

void c_loop()
{
    if(mode_toggle()) goto await;
    input = decode(get_ir());
    if(input == 11) return;

    if(input == 10)
    {
        if(!locked) toggle_lock();
        goto await;
    }
    if(button)
    {
        printf("PASS += %d\n", input);
        seed *= 10;
        seed += input;
        goto await;
    }
    if(!locked) goto await;

    uint16_t pass = rand((time(0) - offset + seed) / 60);
    if((pass & 0x000f) > 0x0009) pass &= 0xfff9;
    if((pass & 0x00f0) > 0x0090) pass &= 0xff9f;
    if((pass & 0x0f00) > 0x0900) pass &= 0xf9ff;
    if((pass & 0xf000) > 0x9000) pass &= 0x9fff;

    user |= input;
    printf("USER = 0x%04x\n", user);
    if(user == pass) toggle_lock();
    user <<= 4;

    await: sleep_ms(300);
}
