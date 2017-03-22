/*
 * tswtch : A simple user-level task switching library
 * Copyright (c) 2014-2017 Takuo Watanabe
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tcontext.h>

typedef struct node {
    int v;
    struct node *l, *r;
} *tree_t;

tree_t tcons(int v, tree_t l, tree_t r) {
    tree_t t = malloc(sizeof(struct node));
    t->v = v;
    t->l = l;
    t->r = r;
    return t;
}

void tfree(tree_t t) {
    if (t != NULL) {
        tfree(t->l);
        tfree(t->r);
        free(t);
    }
}

tcontext_t main_context;

struct param {
    char *name;
    tree_t tree;
    int v;
    tcontext_t context;
};

void trav(char *name, tree_t t, int *v, tcontext_t *context) {
    if (t != NULL) {
        trav(name, t->l, v, context);
        *v = t->v;
        tswtch(context, main_context);
        trav(name, t->r, v, context);
    }
}

void travth(void *arg) {
    struct param *p = (struct param *)arg;
    trav(p->name, p->tree, &p->v, &p->context);
    p->v = -1;
    tswtch(&p->context, main_context);
}

int main(void) {
    tree_t foo_tree =
        tcons(1, 0, tcons(2, 0, tcons(3, 0, tcons(4, 0, 0))));
    tree_t bar_tree =
        tcons(3, tcons(1, 0, tcons(2, 0, 0)), tcons(4, 0, 0));

    struct param foo = { "foo", foo_tree, 0, NULL };
    struct param bar = { "bar", bar_tree, 0, NULL };
    tstack_t foo_stack = alloc_tstack();
    tstack_t bar_stack = alloc_tstack();
    foo.context = new_tcontext(foo_stack + TSTACK_DEPTH, travth, &foo);
    bar.context = new_tcontext(bar_stack + TSTACK_DEPTH, travth, &bar);

    while (foo.v != -1 && bar.v != -1 && foo.v == bar.v) {
        tswtch(&main_context, foo.context);
        tswtch(&main_context, bar.context);
        printf("foo: %d, bar: %d\n", foo.v, bar.v);
    }
    free_tstack(foo_stack);
    free_tstack(bar_stack);
    tfree(foo_tree);
    tfree(bar_tree);
    return EXIT_SUCCESS;
}
