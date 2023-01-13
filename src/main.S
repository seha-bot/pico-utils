.syntax unified
.thumb_func
.global main

main:
    bl init_led
    bl stdio_init_all
loop:
    movs r0, #1
    bl write_pin

    movs r0, #125
    lsls r0, #3
    bl sleep_ms

    movs r0, #0
    bl write_pin

    movs r0, #125
    lsls r0, #3
    bl sleep_ms

    b loop
    