/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

#pragma once

#include "tcontext.h"

enum tthread_state {
    TT_UNUSED = 0,
    TT_EMBRYO,
    TT_SLEEPING,
    TT_RUNNABLE,
    TT_RUNNING,
    TT_ZOMBIE
};

typedef struct tthread {
    struct tthread *next;
    int id;
    enum tthread_state state;
    tstack_t stack;
    tcontext_t context;
    struct tthread *parent;
    void *event;
    void *result;
} *tthread_t;

tthread_t new_tthread(void (*)(void *), void *);
void delete_tthread(tthread_t);
void run_tthread(void);
void tt_yield(void);
void tt_exit(void *);
void *tt_join(int *);
