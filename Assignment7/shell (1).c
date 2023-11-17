//shell.c
#include "shell.h"
#include "stats.h"
#include <stdio.h>
//int size = sizeof(arr)/sizeof(arr[0]);
uint32_t gap(uint32_t n){
    if(n<=1){
	return 0;
    }else 
	if(n<=2){
	    n=1;
        }else{
	    n = (5*n)/11;
	}
    return n;
}

void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
    //int size = sizeof(arr)/sizeof(arr[0]);
    uint32_t gap_size = gap(n_elements);
    for(uint32_t step = gap_size; 0 < step; step=gap(step)){
       for(uint32_t i = step; i < n_elements; i++){
	   uint32_t j = i;
	   uint32_t temp = move(stats,arr[i]);
	   while (j >= step && cmp(stats, temp,arr[j-step])==-1){
	       arr[j] =move(stats, arr[j-step]);
	       move(stats,arr[j]);
	       j -= step;
	   }
           arr[j] = move(stats, temp);
	   move(stats,arr[j]);
    }}   
}
