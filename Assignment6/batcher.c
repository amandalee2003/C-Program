//batcher.c
#include "batcher.h"

#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
//this is a helper bit length function which shifts until the bit is all zeros, meaning empty
uint32_t bit_length(uint32_t n) {
    Set sets = set_empty();
    uint32_t value = 0;
    while (n != sets) {
        n = n >> 1;
        value += 1;
    }
    return value;
}
//this functio compares and swaps the values if they are not in the right order based on greater than and less than
uint32_t comparator(Stats *stats, uint32_t *arr, uint32_t x, uint32_t y) {
    if (cmp(stats, arr[x], arr[y]) == 1) {
        swap(stats, &arr[x], &arr[y]);
    }
    return *arr;
}
//this function uses the bit length and comparator functions to help move up the array and swap the values which are not in the right place as well as using bit shifting.
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    uint32_t t = bit_length(n);
    uint32_t p = 1 << (t - 1);
    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;
        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
