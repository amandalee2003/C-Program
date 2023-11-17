//shell.c
#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//this shell sort contains a nested for loop and while loop which uses gaps.h as well as move to reach a fuller sorted array from least to greatest
void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (uint32_t x = 0; x <= GAPS; x++) {
        uint32_t gap = gaps[x];
        for (uint32_t i = gap; i < length; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, arr[i]);
            while (j >= gap && cmp(stats, temp, arr[j - gap]) == -1) {
                arr[j] = move(stats, arr[j - gap]);
                j -= gap;
            }
            arr[j] = move(stats, temp);
        }
    }
}
