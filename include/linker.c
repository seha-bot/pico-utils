#define IR 29
#include"pico_utils.h"

void c_init()
{
    init_ir();
}

void c_loop()
{
    uint64_t ir = get_ir();
    if(ir != 0) printf("0x%llx\n", ir);
}
