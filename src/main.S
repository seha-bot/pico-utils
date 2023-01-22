.syntax unified
.thumb_func
.global main

.data
SIZE: .word 5

.text
main:
    bl stdio_init_all
loop:
    ldr r7, =SIZE
    ldr r6, [r7]
    adds r6, #1
    movs r4, r6
    i:
        movs r5, r6
        j:
            cmp r5, #1
            beq vert
            cmp r5, r6
            beq vert

            cmp r4, #1
            beq hori
            cmp r4, r6
            beq hori

            b empty
            vert:
                cmp r4, #1
                beq same
                cmp r4, r6
                beq same
                ldr r0, =P_V
                bl printf
                b skip
            hori:
                ldr r0, =P_H
                bl printf
                b skip
            same:
                ldr r0, =P_HASH
                bl printf
                b skip
            empty:
                ldr r0, =P_SPACE
                bl printf
            skip:
            subs r5, #1
            bne j
        @END J
        ldr r0, =P_NEWL
        bl printf
        subs r4, #1
        bne i
    @END I

    ldr r0, =P_NEWL
    bl printf

    movs r0, #250
    lsls r0, #2
    bl sleep_ms

    b loop

.align 4
P_SPACE: .asciz " "
P_STAR: .asciz "*"
P_HASH: .asciz "#"
P_V: .asciz "|"
P_H: .asciz "-"
P_NEWL: .asciz "\n"