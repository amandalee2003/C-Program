
//bubble.c
#include <stdint.h>
#include "stats.h"
#include <stdio.h>
#include "bubble.h"
//int size = sizeof(a)/sizeof(a[0]);
void bubble_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
    //int size = sizeof(a)/sizeof(a[0]);
    for(uint32_t i = 0; i <= n_elements - 1; i++){
	uint32_t swapped = 0;
	for(uint32_t j = n_elements-1; j>i; j-=1){
            //swap(Stats *stats, a[j], a[j-1]);
	    if(cmp(stats,arr[j],arr[j-1])==-1){
		swap(stats, &arr[j], &arr[j-1]);
		swapped = 1;
	}}if (swapped ==0){
            break;
	}}
}
