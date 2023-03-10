#define IR 29
#include"pico_utils.h"
#include"pico_lcd.h"

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

void c_init()
{
    init_ir();
}

uint16_t pass = 0;

void c_loop()
{
    uint64_t ir = get_ir();
    if(!ir) return;
    // printf("0x%llx\n", ir);
    uint8_t v = decode(ir);
    if(v == 11) return;
    printf("%d\n", v);
    pass |= v;
    if(pass == 0x9277)
    {
        printf("UNLOCKED\n");
        pass = 0;
    }
    pass <<= 4;
    sleep_ms(300);
}
