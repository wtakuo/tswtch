/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tthread.h>

void bar(void *arg) {
    int n = (long)arg;
    for (int c = 0; c < n; c++) {
        printf("bar: %d\n", c);
        tt_yield();
    }
    printf("bar: finished\n");
    tt_exit(NULL);
}

void foo(void *arg) {
    int n = (long)arg;
    new_tthread(bar, (void *)10);
    for (int c = 0; c < n; c++) {
        printf("foo: %d\n", c);
        tt_yield();
    }
    tt_join(NULL);
    printf("foo: finished\n");
    tt_exit(NULL);
}

int main(void) {
    new_tthread(foo, (void *)5);
    run_tthread();
    return EXIT_SUCCESS;
}
