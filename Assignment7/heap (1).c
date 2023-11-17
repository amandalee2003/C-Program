//heap.c
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "stats.h"
#include <stdint.h>

uint32_t l_child(uint32_t n){
    return 2*n+1;
}

uint32_t r_child(uint32_t n){
    return 2*n+2;
}

uint32_t parent(uint32_t n){
    return (n-1)/2;
}

void up_heap(Stats *stats,uint32_t *arr,uint32_t n){
    while (n > 0 && cmp(stats,arr[n],arr[parent(n)])==-1){
	swap(stats, &arr[n], &arr[parent(n)]);
	n = parent(n);
    }
}

void down_heap(Stats *stats, uint32_t *arr, uint32_t heap_size){
    uint32_t n=0;
    uint32_t bigger;
    while (l_child(n) < heap_size){
        if (r_child(n) == heap_size){
            bigger = l_child(n);
	}else{
	    if (cmp(stats,arr[l_child(n)],arr[r_child(n)])==-1){
	        bigger = l_child(n);
	    }else{
	        bigger = r_child(n);
	}}if (cmp(stats,arr[n],arr[bigger])==-1){
	    break;
	    }
	    swap(stats, &arr[n], &arr[bigger]);
	    n = bigger;
	}
}
uint32_t *build_heap(Stats *stats,uint32_t *arr, uint32_t n_elements){
    uint32_t *heap = (uint32_t *)calloc(n_elements,sizeof(uint32_t));
    for (uint32_t n=0; n<n_elements; n++){
	heap[n] = move(stats, arr[n]);
	move(stats, heap[n]);
	up_heap(stats, heap, n);
    }return heap;
    }

void heap_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
    uint32_t *heap = build_heap(stats, arr, n_elements);
    for (uint32_t n=0; n<n_elements; n++){
	arr[n] = move(stats, heap[0]);
        move(stats,arr[n]);
	heap[0] = move(stats, heap[n_elements -n-1]);
	move(stats, heap[0]);
	down_heap (stats, heap, n_elements - n);
    }
}

