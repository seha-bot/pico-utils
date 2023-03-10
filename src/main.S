.syntax unified
.thumb_func
.global main

main:
    bl stdio_init_all
    bl init_neo
    bl c_init
loop:
    bl c_loop
    b loop
@END loop
