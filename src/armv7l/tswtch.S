### tswtch : A simple user-level task switching library
### Copyright (c) 2014-2017 Takuo Watanabe

### void tswtch(tstack_t *old, tstack_t new);
### Save current running context in old and load saved context from new

#if !defined(TSWTCH)
#define TSWTCH tswtch
#endif

        .globl TSWTCH
TSWTCH:
        push { r0, r4-r7, lr }
        mov r2, r8
        mov r3, r9
        mov r4, r10
        mov r5, r11
        mov r6, r12
        push { r2-r6 }

        mov r2, sp
        str r2, [r0]
        mov sp, r1

        // movs r2, #0
        // mov lr, r2

        pop { r2-r6 }
        mov r8, r2
        mov r9, r3
        mov r10, r4
        mov r11, r5
        mov r12, r6
        pop { r0, r4-r7, pc }
