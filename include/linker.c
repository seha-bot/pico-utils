#define IR 29
#include"pico_utils.h"
#include"pico_lcd.h"

void c_init()
{
    init_ir();
    lcd_init();
}

char shownChars[32] = { [0 ... 31] = ' ' };
char possible[][4] = {
    { 'a', 'b', 'c', '1' },
    { 'd', 'e', 'f', '2' },
    { 'g', 'h', 'i', '3' },
    { 'j', 'k', 'l', '4' },
    { 'm', 'n', 'o', '5' },
    { 'p', 'q', 'r', '6' },
    { 's', 't', 'u', '7' },
    { 'v', 'w', 'x', '8' },
    { 'y', 'z', ' ', '9' },
    { '0', '0', '0', '0' }
};
int cursor = 0;

char toLower(char c)
{
    if('A' <= c && c <= 'Z')
    {
        return c - ('a'-'A');
    }
    return c;
}
char toUpper(char c)
{
    if('a' <= c && c <= 'z')
    {
        return c + ('A'-'a');
    }
    return c;
}

void drawOnMatch(int id)
{
    int candidate = 0;
    for(int i = 0; i < 4; i++)
    {
        if(shownChars[cursor] == possible[id][i])
        {
            candidate = (i+1) & 0b11;
            break;
        }
    }
    letter(shownChars[cursor] = possible[id][candidate]);
}

void c_loop()
{
    uint64_t ir = get_ir();
    if(ir != 0)
    {
        int changed = 0;
        switch(ir)
        {
            case 0xaffeaffeefafa000: /*LEFT*/
                changed = 1;
                cursor = (cursor-1) & 0b11111;
            break;
            case 0xaffeafffbfaee000: /*RIGHT*/
                changed = 1;
                cursor = (cursor+1) & 0b11111;
            break;
            case 0xaffeafffffaea000: /*UP*/
                changed = 1;
                letter(toUpper(shownChars[cursor]));
            break;
            case 0xaffeaffeffafa000: /*DOWN*/
                changed = 1;
                letter(toLower(shownChars[cursor]));
            break;
            case 0xaffeafffeffeb800: /*1*/
                changed = 1;
                drawOnMatch(0);
            break;
            case 0xaffeaffeefffb800: /*2*/
                changed = 1;
                drawOnMatch(1);
            break;
            case 0xaffeafffaffef800: /*3*/
                changed = 1;
                drawOnMatch(2);
            break;
            case 0xaffeaffffbfea800: /*4*/
                changed = 1;
                drawOnMatch(3);
            break;
            case 0xaffeaffefbffa800: /*5*/
                changed = 1;
                drawOnMatch(4);
            break;
            case 0xaffeafffbbfee800: /*6*/
                changed = 1;
                drawOnMatch(5);
            break;
            case 0xaffeafffebfeb800: /*7*/
                changed = 1;
                drawOnMatch(6);
            break;
            case 0xaffeaffeebffb800: /*8*/
                changed = 1;
                drawOnMatch(7);
            break;
            case 0xaffeafffabfef800: /*9*/
                changed = 1;
                drawOnMatch(8);
            break;
            case 0xaffeaffefeffa800: /*0*/
                changed = 1;
                drawOnMatch(9);
            break;
            case 0xaffeaffffbaea000: /*OK*/
                changed = 1;
                for(int i = 0; i < 32; i++) shownChars[i] = ' ';
                lcd_set_cursor(0, 0);
                for(int i = 0; i < 16; i++) letter(' ');
                lcd_set_cursor(0, 1);
                for(int i = 0; i < 16; i++) letter(' ');
            break;
            case 0xaffeaffeabfff800: /*MUTE*/
                changed = 1;
                letter(++shownChars[cursor]);
            break;
        }
        if(changed)
        {
            lcd_set_cursor(cursor%16, cursor/16);
            sleep_ms(50);
        }
    }
}
