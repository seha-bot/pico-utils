.syntax unified
.thumb_func
.global main

.data
NUM_A: .word 1
NUM_B: .word 1

.text
main:
    bl stdio_init_all
    ldr r4, =NUM_A
    ldr r5, =NUM_B
loop:
    ldr r0, [r4]
    ldr r1, [r5]
    adds r1, r0
    str r1, [r4]
    str r0, [r5]

    adr r0, PRNT
    bl printf

    movs r0, #250
    lsls r0, #2
    bl sleep_ms

    b loop

.align 4
PRNT: .asciz "%d\n"