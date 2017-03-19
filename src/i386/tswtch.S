### tswtch : A simple user-level task switching library
### Copyright (c) 2014-2017 Takuo Watanabe

### void tswtch(tstack_t *old, tstack_t new);
### Save current running context in old and load saved context from new

#if !defined(TSWTCH)
#define TSWTCH tswtch
#endif

        .globl TSWTCH
TSWTCH:
        movl 4(%esp), %eax      # old
        movl 8(%esp), %edx      # new

        ## Save old callee-save registers
        pushl %ebp
        pushl %ebx
        pushl %esi
        pushl %edi

        ## Switch stacks
        movl %esp, (%eax)       # *old = sp
        movl %edx, %esp         # sp = new

        ## Load new callee-save registers
        popl %edi
        popl %esi
        popl %ebx
        popl %ebp

        ret
