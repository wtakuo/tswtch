/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#if defined(__linux__)
#include <malloc.h>
#endif

#include "tcontext.h"

tstack_t alloc_tstack(void) {
    tstack_t stack = valloc(TSTACK_SIZE);
    if (stack == NULL)
        perror("alloc_stack");
    return stack;
}

void free_tstack(tstack_t stack) {
    free(stack);
}

tcontext_t new_tcontext(tstack_t sp, void (*fun)(void *), void *arg) {
    tcontext_t context =
        (tcontext_t)((char *)sp - sizeof(struct tcontext));
    context->fun = fun;
    context->arg = arg;
    return context;
}
