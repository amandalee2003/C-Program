
#include "shell.h"
#include "quick.h"
#include <stdio.h>
#include "stats.h"
#include <stdint.h>
#include <unistd.h>

//quick.c
uint32_t small = 8;
void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
    uint32_t pivot = (arr[0] + arr[n_elements/2] + arr[n_elements-1])/3;
    uint32_t left_arr = 0;
    uint32_t right_arr = n_elements -1;
    if (small > n_elements){
        shell_sort(stats, arr, n_elements);
	return;
    }
   while(right_arr>left_arr){
	while(cmp(stats, pivot,arr[left_arr])==1||arr[left_arr] == pivot){
	    left_arr+=1;
	}if (left_arr==n_elements){
            return;    
        }while (cmp(stats,pivot,arr[right_arr])==-1){
            right_arr-=1;
        }if(left_arr<right_arr){
	    swap(stats,&arr[left_arr],&arr[right_arr]);
    }}
    quick_sort(stats,&arr[0],left_arr);
    quick_sort(stats,&arr[left_arr],n_elements-left_arr);
    }
