/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "tthread.h"

#define MAXTHREADS 256

static struct tthread threads[MAXTHREADS];
static int next_id;
static tthread_t current = NULL;
static tthread_t initth = NULL;
static bool initialized = false;
static tcontext_t scheduler_context;

static struct {
    tthread_t head, tail;
} tqueue;

static void tqueue_init(void) {
    static struct tthread dummy = { .next = NULL };
    tqueue.head = tqueue.tail = &dummy;
}

static bool tqueue_empty(void) {
    return tqueue.head == tqueue.tail;
}

static void tqueue_put(tthread_t th) {
    assert(tqueue.tail->next == NULL);
    tqueue.tail->next = th;
    tqueue.tail = th;
    tqueue.tail->next = NULL;
}

static tthread_t tqueue_get(void) {
    assert(!tqueue_empty());
    tthread_t th = tqueue.head->next;
    tqueue.head->next = th->next;
    return th;
}

static void tqueue_remove(tthread_t th) {
    tthread_t u = tqueue.head;
    while (u != tqueue.tail) {
        if (u->next == th) {
            if (tqueue.tail == th)
                tqueue.tail = u;
            u->next = th->next;
            return;
        }
        u = u->next;
    }
}

static tthread_t alloc_tthread(void) {
    for (int i = 0; i < MAXTHREADS; i++) {
        if (threads[i].state == TT_UNUSED) {
            threads[i].state = TT_EMBRYO;
            return &threads[i];
        }
    }
    return NULL;
}

static tthread_t create_tthread(void (*fun)(void *), void *arg,
                                tthread_t parent) {
    tthread_t th = alloc_tthread();
    tstack_t stack = alloc_tstack();
    tcontext_t context =
        new_tcontext(stack + TSTACK_DEPTH, fun, arg);
    th->id = next_id++;
    th->state = TT_RUNNABLE;
    th->stack = stack;
    th->context = context;
    th->parent = parent;
    return th;
}

static void init_fun(void *arg) {
    (void)arg;
    while (true)
        tt_join(NULL);
}

static void initialize(void) {
    tqueue_init();
    for (int i = 0; i < MAXTHREADS; i++)
        threads[i].state = TT_UNUSED;
    next_id = 0;
    initth = create_tthread(init_fun, NULL, NULL);
    initth->parent = initth;
    current = initth;
    tqueue_put(initth);
    initialized = true;
}

tthread_t new_tthread(void (*fun)(void *), void *arg) {
    if (!initialized)
        initialize();
    tthread_t th = create_tthread(fun, arg, current);
    tqueue_put(th);
    return th;
}

void delete_tthread(tthread_t th) {
    free_tstack(th->stack);
    th->state = TT_UNUSED;
}

void run_tthread(void) {
    assert(!tqueue_empty());
    while (true) {
        tthread_t th = tqueue_get();
        if (th->state == TT_RUNNABLE) {
            current = th;
            current->state = TT_RUNNING;
            tswtch(&scheduler_context, current->context);
        }
        if (tqueue_empty()) {
            assert(th->id == 0);
            break;
        }
        tqueue_put(th);
    }
}

void tt_yield(void) {
    current->state = TT_RUNNABLE;
    tswtch(&current->context, scheduler_context);
}

static void wakeup(tthread_t th, void *event) {
    if (th->state == TT_SLEEPING && th->event == event)
        th->state = TT_RUNNABLE;
}

void tt_exit(void *result) {
    assert(current->id != 0);
    for (tthread_t th = tqueue.head->next; th != NULL; th = th->next) {
        if (th->parent == current) {
            th->parent = initth;
        }
    }
    current->state = TT_ZOMBIE;
    current->result = result;
    wakeup(current->parent, current->parent);
    tswtch(&current->context, scheduler_context);
}

void *tt_join(int *idp) {
    while (true) {
        for (tthread_t th = tqueue.head->next; th != NULL; th = th->next) {
            if (th->parent == current && th->state == TT_ZOMBIE) {
                void *result = th->result;
                if (idp != NULL)
                    *idp = th->id;
                tqueue_remove(th);
                delete_tthread(th);
                return result;
            }
        }
        current->state = TT_SLEEPING;
        current->event = current;
        tswtch(&current->context, scheduler_context);
    }
}
