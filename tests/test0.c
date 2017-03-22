/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tcontext.h>

tcontext_t main_context, foo_context, bar_context;

void foo(void *arg) {
    long c = (long)arg;
    while (true) {
        printf("foo  %ld\n", c++);
        tswtch(&foo_context, bar_context);
    }
}

void bar(void *arg) {
    long c = (long)arg;
    while (true) {
        printf("bar1 %ld\n", c++);
        tswtch(&bar_context, main_context);
        printf("bar2 %ld\n", c++);
        tswtch(&bar_context, main_context);
    }
}

int main(void) {
    tstack_t foo_stack = alloc_tstack();
    tstack_t bar_stack = alloc_tstack();
    foo_context = new_tcontext(foo_stack + TSTACK_DEPTH, foo, (void *)0);
    bar_context = new_tcontext(bar_stack + TSTACK_DEPTH, bar, (void *)0);
    for (long c = 0; c < 7; c++) {
        printf("main %ld\n", c);
        tswtch(&main_context, foo_context);
    }
    free_tstack(foo_stack);
    free_tstack(bar_stack);
    return EXIT_SUCCESS;
}

