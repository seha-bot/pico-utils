.syntax unified
.thumb_func
.global main

main:
    bl stdio_init_all
    bl init_led

    movs r5, #1
    lsls r5, #25
    ldr r4, =SIO_BASE
    ldr r4, [r4]
loop:
    str r5, [r4, #28]

    movs r0, #250
    lsls r0, #2
    bl sleep_ms

    b loop
@END loop

.data
SIO_BASE: .word 0xd0000000