.syntax unified
.thumb_func
.global main

main:
    bl stdio_init_all
    ldr r4, AVA
    ldr r5, AVB
loop:
    ldr r0, [r4]
    ldr r1, [r5]
    adds r1, r0
    str r1, [r4]
    str r0, [r5]

    ldr r0, =NUM
    bl printf

    movs r0, #250
    lsls r0, #2
    bl sleep_ms

    b loop

.align 4
AVA: .word VA
AVB: .word VB

.data
VA: .word 1
VB: .word 0
NUM: .asciz "%d\n"