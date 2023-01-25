.syntax unified
.thumb_func
.global main

main:
    bl stdio_init_all
    bl init_neo

    movs r6, #0 @ V

    movs r5, #1
    lsls r5, #23
    ldr r4, =SIO_BASE
    ldr r4, [r4]
loop:
    ldr r0, =INT_R
    ldr r0, [r0]
    lsls r0, #8
    ldr r1, =INT_B
    ldr r1, [r1]
    adds r0, r1
    bl light

    @ if(v == 0) R++ if(R == 255) v++
    @ if(v == 1) B++ if(B == 255) v++
    @ if(v == 2) R-- if(R == 0b0) v++
    @ if(v == 3) B-- if(B == 0b0) v=0

    cmp r6, #0
    beq v0
    cmp r6, #1
    beq v1
    cmp r6, #2
    beq v2
    @v3
        ldr r0, =INT_B
        ldr r1, [r0]
        subs r1, #1
        str r1, [r0]
        cmp r1, #0
        bne vnskip
        movs r6, #0
    b vnskip
    v0:
        ldr r0, =INT_R
        ldr r1, [r0]
        adds r1, #1
        str r1, [r0]
        cmp r1, #255
        bne vnskip
        adds r6, #1
    b vnskip
    v1:
        ldr r0, =INT_B
        ldr r1, [r0]
        adds r1, #1
        str r1, [r0]
        cmp r1, #255
        bne vnskip
        adds r6, #1
    b vnskip
    v2:
        ldr r0, =INT_R
        ldr r1, [r0]
        subs r1, #1
        str r1, [r0]
        cmp r1, #0
        bne vnskip
        adds r6, #1
    vnskip:

    movs r0, #2
    bl sleep_ms
    b loop
@END loop

light:
    push {lr}
    movs r1, #24
    data_fill:
        lsrs r0, #1
        movs r2, r0
        movs r3, #1
        ands r2, r3
        push {r2}
        subs r1, #1
        bne data_fill
    @END data_fill
    movs r1, #24
    colors:
        pop {r0}
        cmp r0, #0
        beq zero
        one:
            str r5, [r4, #20]
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            str r5, [r4, #24]
            bl ns100
            bl ns100
            bl ns100
            @AUTO DELAY 6 instructions (14 cycles * 8 ns/cycle = 112ns)
            b skip
        zero:
            str r5, [r4, #20]
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            str r5, [r4, #24]
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            bl ns100
            @AUTO DELAY 6 instructions (14 cycles * 8 ns/cycle = 112ns)
            b skip
        skip:
        subs r1, #1
        bne colors
    @END colors
    pop {pc}
@END light

@ 3 cycles for calling
ns100: @ 100ns = 12.5 cycles * 8 ns/cycle
    adds r0, #1 @ 1 cycle
    adds r0, #1 @ 1 cycle
    adds r0, #1 @ 1 cycle
    adds r0, #1 @ 1 cycle
    adds r0, #1 @ 1 cycle
    adds r0, #1 @ 1 cycle
    bx lr @ 3 cycles
@END ns100

.data
SIO_BASE: .word 0xd0000000
INT_R: .word 0
INT_G: .word 0
INT_B: .word 0