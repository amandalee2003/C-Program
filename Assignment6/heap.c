//heap.c
#include "heap.h"

#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//this function sets the left and right child values while comparing the arrays to see which is the greater value, and returing it to use later
uint32_t max_child(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && cmp(stats, arr[right - 1], arr[left - 1]) == 1) {
        return right;
    }
    return left;
}
//this function swaps the places within the array based on the values of the children as well as comparing the first and last values to reach the desired least to greatest heap sorted array
void fix_heap(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    uint32_t found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, arr, mother, last);
    while ((mother <= (last / 2)) && !found) { //found == false
        if (cmp(stats, arr[mother - 1], arr[great - 1]) == -1) {
            swap(stats, &arr[mother - 1], &arr[great - 1]);
            mother = great;
            great = max_child(stats, arr, mother, last);
        } else {
            found = true;
        }
    }
}

//this function uses fix heap in order to build the needed heap
void build_heap(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    for (uint32_t father = (last / 2); father > (first - 1); father--) {
        fix_heap(stats, arr, father, last);
    }
}
//this function uses fixheap and build heap in order to sort the array by swaping as needed for the desired heap sort
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
