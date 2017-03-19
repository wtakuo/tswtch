### tswtch : A simple user-level task switching library
### Copyright (c) 2014-2017 Takuo Watanabe

### void tswtch(tstack_t *old, tstack_t new);
### Save current running context in old and load saved context from new

#if !defined(TSWTCH)
#define TSWTCH tswtch
#endif

        .globl TSWTCH
TSWTCH:
        ## save old callee-save registers
        pushq %rbp
        pushq %rbx
        pushq %r12
        pushq %r13
        pushq %r14
        pushq %r15

        ## push argument register
        pushq %rdi

        ## switch stacks
        movq %rsp, (%rdi)       # *old = sp
        movq %rsi, %rsp         # sp = new

        ## load argument register
        popq %rdi

        ## load new callee-save registers
        popq %r15
        popq %r14
        popq %r13
        popq %r12
        popq %rbx
        popq %rbp

        ret
