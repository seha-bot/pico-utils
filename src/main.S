.syntax unified
.thumb_func
.global main

.data
SIZE: .word 5

.text
main:
    bl stdio_init_all
loop:
    ldr r6, =SIZE
    ldr r4, [r6]
    i:
        ldr r5, [r6]
        j:
            cmp r4, r5
            blt skip
            ldr r0, =STAR
            bl printf
            skip:
            subs r5, #1
            bne j
        @END J
        ldr r0, =NEWL
        bl printf
        subs r4, #1
        bne i
    @END I

    ldr r0, =NEWL
    bl printf

    movs r0, #250
    lsls r0, #2
    bl sleep_ms

    b loop

.align 4
STAR: .asciz "* "
NEWL: .asciz "\n"