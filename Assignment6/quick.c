//quick.c
#include "quick.h"

#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
//this function compares and swaps values if they are greater than the other and out of order
uint32_t partition(Stats *stats, uint32_t *arr, uint32_t low, uint32_t high) {
    uint32_t i = 0;
    i = low - 1;
    uint32_t j = 0;
    for (j = low; j < high; j++) {
        if (cmp(stats, arr[j - 1], arr[high - 1]) == -1) {
            i += 1;
            swap(stats, &arr[i - 1], &arr[j - 1]); //this needs to be changed to 2 lines of moves
        }
    }
    swap(stats, &arr[i], &arr[high - 1]); //this needs to be changed to 2 lines of moves
    return (i + 1);
}

//this function uses recursion as it checks the order of 2 places in the array, and checks going up the array, as well as down
uint32_t quick_sorter(Stats *stats, uint32_t *arr, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t p = partition(stats, arr, low, high);
        quick_sorter(stats, arr, low, p - 1);
        quick_sorter(stats, arr, p + 1, high);
    }
    return *arr;
}
//this function calls quick sorter with the given array and elements needed for this quick sort
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
/*
int main(void){
    Stats *stats = calloc(1, sizeof(Stats));
    uint32_t i=0;
    //Set sets = set_empty();
    uint32_t n_elements = 13;
    uint32_t print_value = 100;
    //uint32_t *arr =(uint32_t *)calloc(n_elements, sizeof(arr))
    uint32_t arr[] = {1,5,6,8,13,88,4,99,104,7,55,3,3};
    quick_sort(stats, arr, n_elements);
    printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves, stats->compares);
    if (print_value > n_elements){
        for (i=0;i<n_elements;i++){
            printf("%13" PRIu32, arr[i]);
            if((i+1)%5 == 0 && i!=0){
               printf("\n");
    }}}
    else{
        for (i=0; i<print_value; i++){
            printf("%13" PRIu32, arr[i]);
            if ((i+1)%5 == 0 && i!=0){
                printf("\n");
    }}}
    if ((i)%5 != 0){
        printf("\n");
    }
    free(stats);
}*/
