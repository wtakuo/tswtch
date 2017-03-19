/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

typedef struct tcontext {
    void *edi;
    void *esi;
    void *ebx;
    void *ebp;
    void (*fun)(void *);  // eip
    void (*ret)(void);
    void *arg;
} *tcontext_t;
