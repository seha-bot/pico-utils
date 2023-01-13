#include"pico_utils.h"

int main()
{
    init_button();
    init_led();
    stdio_init_all();
    while(1)
    {
        u_int8_t state = get_button();
        printf("%d\n", state);

        if(state) gpio_put(LED, 1);
        else gpio_put(LED, 0);
    }
    return 0;
}
