#define IR 29
#include"pico_utils.h"
#include<time.h>

void c_init()
{
    init_ir();
}

uint8_t decode(uint64_t ir)
{
    switch(ir)
    {
        case 0xaffeaffefeffa800: return 0;
        case 0xaffeafffeffeb800: return 1;
        case 0xaffeaffeefffb800: return 2;
        case 0xaffeafffaffef800: return 3;
        case 0xaffeaffffbfea800: return 4;
        case 0xaffeaffefbffa800: return 5;
        case 0xaffeafffbbfee800: return 6;
        case 0xaffeafffebfeb800: return 7;
        case 0xaffeaffeebffb800: return 8;
        case 0xaffeafffabfef800: return 9;
        case 0xaffeaffffbaea000: return 10;
        default: return 11;
    }
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
uint8_t began = 0;
uint64_t seed = 0;
time_t offset = 0;

void c_loop()
{
    input = decode(get_ir());
    if(input == 11) return;
    if(input == 10)
    {
        began = !began;
        user = 0;
        if(began) offset = time(0);
        else seed = 0;
        printf("OK\n");
        goto await;
    }
    if(!began)
    {
        printf("PASS += %d\n", input);
        seed *= 10;
        seed += input;
        goto await;
    }

    time_t t = (time(0) - offset + seed) / 60;

    uint16_t pass = rand(t);
    if((pass & 0x000f) > 0x0009) pass &= 0xfff9;
    if((pass & 0x00f0) > 0x0090) pass &= 0xff9f;
    if((pass & 0x0f00) > 0x0900) pass &= 0xf9ff;
    if((pass & 0xf000) > 0x9000) pass &= 0x9fff;

    printf("SEED(%lld) = 0x%04x\n", t, pass);

    user |= input;
    printf("USER = 0x%04x\n", user);
    if(user == pass)
    {
        printf("UNLOCKED\n");
        user = 0;
    }
    user <<= 4;
    await: sleep_ms(300);
}
