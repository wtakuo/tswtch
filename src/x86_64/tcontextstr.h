/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

typedef struct tcontext {
    void *arg;            // rdi
    void *r15;
    void *r14;
    void *r13;
    void *r12;
    void *rbx;
    void *rbp;
    void (*fun)(void *);  // rip
    void *pad;            // padding for 16bit alignment of rip
} *tcontext_t;
