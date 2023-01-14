@ B -- branch
@ BL -- branch, but after executing return to that same place

@ R0, R1, R2, R3 -- Function parameters
@ R4 - R12 -- General Purpose
@ R13 -- Stack Pointer (SP)
@ R14 -- Link Register (LR)
@ R15 - Program Counter (PC)
@ REGISTERS ARE 32 BITS LONG
@ R0 - R7 --Low registers

@ MOVS a, b -- load b into a (b is 8 bits long)

@ADDS Rd, Rn, #<value>            @ Rd = Rn + value
@If Rd is not the same as Rn, value is a 3-bit number; if they are the same, value can be an 8-bit number and we can drop the first Rd:

@SUBS -- same as add

@COMMANDS WITH S ADDED UPDATE THE FLAGS
@FLAGS ARE TOP 4 BITS OF ANY REGISTER (31-28)
@ N - NEGATIVE
@ Z - ZERO
@ C - CARRY
@ V - OVERFLOW

@ CMPS r0, r1
@ IF r0 and r1 are equal, the Z flag on r0 is set

@ BEQ
@ BNE
@ IF ZERO FLAG ON R1 is set, branch