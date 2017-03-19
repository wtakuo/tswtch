/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

#pragma once

#include "tcontextstr.h"

#define TSTACK_DEPTH 1024
#define TSTACK_SIZE (TSTACK_DEPTH * sizeof(void *))

typedef void **tstack_t;

tstack_t alloc_tstack(void);
void free_tstack(tstack_t stack);
tcontext_t new_tcontext(tstack_t sp, void (*fun)(void *), void *arg);
void tswtch(tcontext_t *old, tcontext_t new);

