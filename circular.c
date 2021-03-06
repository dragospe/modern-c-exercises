#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "circular.h"


/** @brief the hidden implementation of the circular buffer type
 */
struct circular {
    size_t start;    /**< Position of the element 0 */
    size_t len;      /**< Number of elements stored */
    size_t max_len;  /**< Maximum capacity */
    double* tab;     /**< Array holding the data */
};


circular* circular_init(circular* c, size_t max_len) {
    if (c) {
        if (max_len) {
            *c = (circular) {
                .max_len = max_len,
                .tab = malloc(sizeof(double[max_len])),
            };
            // Allocation failed.
            if (!c->tab) c->max_len = 0;
        } else {
            *c = (circular) {
                0
            };
        }
    }
    return c;
}

void circular_destroy(circular* c) {
    if (c) {
        free(c -> tab);
        circular_init(c, 0);
    }
}


// Declared static, which means that this function is only visible inside this file.

static size_t circular_getpos(circular* c, size_t pos) {
    pos += c->start;
    pos %= c->max_len;
    return pos;
}

double* circular_element(circular* c, size_t pos) {
    double* ret = 0;
    if (c) {
        if (pos < c->max_len) {
            pos = circular_getpos(c, pos);
            ret = &c->tab[pos];
        }
    }
    return ret;
}

// Increment the "start" of the buffer with the proper wrapping behavior
static void circular_incstart(circular* c) {
    c->start += 1;
    c->start %= c->max_len;
}


circular* circular_append(circular* c, double value) {
    if (c) {

        size_t next_idx = (c->start + c->len) % c->max_len;
        if (c->len == c->max_len) {
            circular_incstart(c);
        }
        c->len = (c->len + 1) > c->max_len ? c->max_len : c->len + 1;
        c->tab[next_idx] = value;
        return c;
    }
    return 0;
}


double circular_pop(circular* c) {
    double ret = 0.0;
    if (c && c->len > 0) {
        ret = c->tab[c->start];
        circular_incstart(c);
        c->len -= 1;
    }
    return ret;
}

circular* circular_new(size_t len) {
    circular* c = malloc(sizeof(circular));
    if (c) {
        c->start = 0;
        c->len = 0;
        c->max_len = len;
        c->tab = malloc(len * sizeof(double));
    }
    return c;
}

void circular_delete(circular* c) {
    if(c) {
        free(c->tab);
        free(c);
    }
}

size_t circular_getlength(circular* c) {
    if (c) {
        return c->len;
    }
    return 0;
}

void print_circular(circular* c, char* label) {
    printf("%s:\n", label);
    printf("Circular at address %p:\n", (void*)c);
    printf("{\n  .start   = %lu\n", c->start);
    printf("  .len     = %lu\n", c->len);
    printf("  .max_len = %lu\n}\n", c->max_len);
    printf("  Elements:\n  ");
    for (size_t i = c->start; i - c->start < c->len; ++i) {
        printf("%.04g, ", c->tab[i % c->max_len]);
    }
    printf("\n\n");
}


int main(void) {
    circular* c = circular_new(8);
    print_circular(c, "EMPTY CIRCULAR");
    circular_append(c, 1.0);
    print_circular(c, "WITH ONE");
    circular_append(c, 2.0);
    circular_append(c, 3);
    circular_append(c, 4);
    circular_append(c, 5);
    circular_append(c, 6);
    circular_append(c, 7);
    circular_append(c, 8);
    print_circular(c, "FILLED");
    circular_append(c, 9);
    print_circular(c, "9 SHOULD WRAP");
    double d = circular_pop(c);
    print_circular(c, "POPPED VALUE");
    printf("Popped value was %g.\n\n",d);
    print_circular(c, "SHOULD BE EMPTY");
    d = circular_pop(c); // Empty buffer, should return 0
    printf("Popped value was %g.\n\n", d);
    circular_delete(c);
}

