#ifndef PICO_UTILS_LCD
#define PICO_UTILS_LCD

#define LCD_E 9
#define LCD_RS 8

#define LCD_B0 13
#define LCD_B1 12
#define LCD_B2 11
#define LCD_B3 10

#include"pico/stdlib.h"

//DISPLAY INSTRUCTIONS
void lcd_tick(uint8_t RS)
{
    gpio_put(LCD_E, 0);
    gpio_put(LCD_RS, 0);

    gpio_put(LCD_E, 1);
    gpio_put(LCD_RS, RS);

    gpio_put(LCD_E, 0);
    gpio_put(LCD_RS, 0);
    sleep_ms(1);
}

void lcd_set_data(uint8_t RS, uint8_t data)
{
    gpio_put(LCD_B3, data>>3&1);
    gpio_put(LCD_B2, data>>2&1);
    gpio_put(LCD_B1, data>>1&1);
    gpio_put(LCD_B0, data>>0&1);
    lcd_tick(RS);
}

void instruction(uint8_t data)
{
    lcd_set_data(0, data>>4);
    lcd_set_data(0, data);
}

void lcd_init()
{
    gpio_init(LCD_E);
    gpio_init(LCD_RS);
    gpio_init(LCD_B0);
    gpio_init(LCD_B1);
    gpio_init(LCD_B2);
    gpio_init(LCD_B3);
    gpio_set_dir(LCD_E, GPIO_OUT);
    gpio_set_dir(LCD_RS, GPIO_OUT);
    gpio_set_dir(LCD_B0, GPIO_OUT);
    gpio_set_dir(LCD_B1, GPIO_OUT);
    gpio_set_dir(LCD_B2, GPIO_OUT);
    gpio_set_dir(LCD_B3, GPIO_OUT);

    lcd_set_data(0, 0b0010);      // Function set ( 4 bit mode )
    instruction(0b00101000); // Function set ( 4 bit mode, 2 lines, 5x8 )
    instruction(0b00001110); // Display control ( display on, cursor on, blinking off )
    instruction(0b00000110); // Entry mode set ( increment, display shift off )
}

//DISPLAY BUILTIN FUNCTIONS
void lcd_set_cursor(uint8_t x, uint8_t y)
{
    instruction(0b10000000 | y << 6 | x);
}

void lcd_clear()
{
    instruction(0b00000001);
}

void lcd_home()
{
    instruction(0b00000010);
}

void lcd_shift(uint8_t direction)
{
    instruction(0b00010000 | direction << 3);
}

//DRAWING FUNCTIONS
void letter(char c)
{
    lcd_set_data(1, c>>4);
    lcd_set_data(1, c);
}

void letters(char* s)
{
    int i = 0;
    while(s[i] != 0) letter(s[i++]);
}

void introduce(const char* message)
{
    lcd_clear();
    lcd_home();
    int i = 0;
    while(message[i])
    {
        letter(message[i++]);
        sleep_ms(500);
    }
}

char msg[17] = { [0 ... 16] = 0 };
void scroll(const char* message, int* off, int direction, int line)
{
    int size = 0;
    while(message[size]) size++;

    lcd_set_cursor(0, line);
    if(direction == 1)
    {
        for(int i = 0; i < 16; i++) msg[i] = message[(i + *off) % size];
    }
    else if(direction == -1)
    {
        for(int i = 0; i < 16; i++)
        {
            int ofic = i + (size-(*off % size));
            msg[i] = message[ofic % size];
        }
    }
    letters(msg);
    (*off)++;
}

#endif /*PICO_UTILS_LCD*/
