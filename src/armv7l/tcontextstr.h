/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

typedef struct tcontext {
    void *r8;
    void *r9;
    void *r10;
    void *r11;
    void *r12;
    void *arg;  // r0
    void *r4;
    void *r5;
    void *r6;
    void *r7;
    void (*fun)(void *); // pc
    void (*ret)(void);
} *tcontext_t;
