
#include "shell.h"
#include "bubble.h"
#include <math.h>
#include "stats.h"
#include "quick.h"
#include "heap.h"
#include "set.h"
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdint.h>
#include "mtrand.h"
#include <stdlib.h>
#define OPTIONS "asbqhr:n:p:H"

int main(int argc, char **argv){
    int opt=0;
    void mtrand_seed (uint64_t seed);
    int n_elements = 100;
    int print_value = 100;
    int seed = 13371453;
    Stats *stats = calloc(1, sizeof(Stats));
    Set sets = set_empty();
    uint32_t *arr =(uint32_t *)calloc(n_elements, sizeof(arr));
    while((opt=getopt(argc,argv,OPTIONS)) != -1){
        switch(opt){
            case 'a':
		sets = set_insert(sets,1);
		sets = set_insert(sets,2);
		sets = set_insert(sets,3);
		sets = set_insert(sets,4);
		break;
            case 's':
		sets = set_insert(sets,4);
		break;
            case 'b':
                sets = set_insert(sets,1);
                break;
            case 'q':
		sets = set_insert(sets,3);
                break;
	    case 'h':
	        sets = set_insert(sets,2);
                break;
	    case 'r':
	        seed = atoi(optarg);
	        break;
	    case 'n':
	        n_elements = atoi(optarg);
	        if(n_elements <=  1 || n_elements >= 250000000){
		    return 1;
	        }
	        break;
	    case 'p':
	        print_value = atoi(optarg);
	        break;
	    case 'H':	
		printf("SYNOPSIS\n");
                printf("   A collection of comparison-based sorting algorithms.\n\n");
                printf("USAGE\n");
                printf("   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n\n");
                printf("OPTIONS\n");
                printf("   -H              Display program help and usage.\n");
                printf("   -a              Enable all sorts.\n");
                printf("   -b              Enable Bubble Sort.\n");
	        printf("   -h              Enable Heap Sort.\n");
                printf("   -q              Enable Quick Sort.\n");
                printf("   -s              Enable Shell Sort.\n");
                printf("   -n length       Specify number of array elements (default: 100).\n");
                printf("   -p elements     Specify number of elements to print (default: 100).\n");
                printf("   -r seed         Specify random seed (default: 13371453).\n");

		   return 0;
	    default:
		printf("SYNOPSIS\n");
                printf("   A collection of comparison-based sorting algorithms.\n\n");
                printf("USAGE\n");
                printf("   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n\n");
                printf("OPTIONS\n");
                printf("   -H              Display program help and usage.\n");
                printf("   -a              Enable all sorts.\n");
                printf("   -b              Enable Bubble Sort.\n");
                printf("   -h              Enable Heap Sort.\n");
                printf("   -q              Enable Quick Sort.\n");
                printf("   -s              Enable Shell Sort.\n");
                printf("   -n length       Specify number of array elements (default: 100).\n");
                printf("   -p elements     Specify number of elements to print (default: 100).\n");
                printf("   -r seed         Specify random seed (default: 13371453).\n");
	        return 1;
	    }}
//mtrand_seed(seed);

//bubble
if (set_member(sets,1)){
    reset(stats);
    int i;
    arr = (uint32_t *)calloc(n_elements, sizeof(arr));
    //printf("s:\n");
    mtrand_seed(seed);
    for (int a = 0; a<n_elements;a++){
        arr[a] = mtrand_rand64() & 0x3FFFFFFF;
    }
    bubble_sort(stats, arr, n_elements);
    printf("Bubble Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves, stats->compares);
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
    free(arr);
    free(stats);
}
//heap
if (set_member(sets,2)){
    reset(stats);
    //int temp = 0;
    int i;
    arr = (uint32_t *)calloc(n_elements, sizeof(arr));
    //printf("shell:\n");
    mtrand_seed(seed);
    for (int a = 0; a<n_elements;a++){
        arr[a] = mtrand_rand64() & 0x3FFFFFFF;
    }
    heap_sort(stats, arr, n_elements);
    printf("Heap Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves, stats->compares);
    if (print_value > n_elements){
        for ( i=0;i<n_elements;i++){
            printf("%13" PRIu32, arr[i]);
	    //temp = i;
            if((i+1)%5 == 0 && i!=0){
               printf("\n");
        }}}
    else{
        for (i=0; i<print_value; i++){
            printf("%13" PRIu32, arr[i]);
	    //temp = i;
            if ((i+1)%5 == 0 && i!=0){
                printf("\n");
        }}}
    if ((i)%5 != 0){
    printf("\n");
	}
    free(arr);
    free(stats);
}
//quick
if (set_member(sets,3)){
    reset(stats);
    int i;
    arr = (uint32_t *)calloc(n_elements, sizeof(arr));
    mtrand_seed(seed);
    for (int a = 0; a<n_elements;a++){
        arr[a] = mtrand_rand64() & 0x3FFFFFFF;
    }
    quick_sort(stats, arr, n_elements);
    printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves, stats->compares);
    if (print_value > n_elements){
        for ( i=0;i<n_elements;i++){
            printf("%13" PRIu32, arr[i]);
	    //temp = i;
            if((i+1)%5 == 0 && i!=0){
               printf("\n");
        }}}
    else{
        for ( i=0; i<print_value; i++){
            printf("%13" PRIu32, arr[i]);
	    //temp = i;
            if ((i+1)%5 == 0 && i!=0){
                printf("\n");
        }}}
    if ((i)%5 != 0){
    printf("\n");
	}
    free(arr);
    free(stats);
}

//shell
if (set_member(sets,4)){
    reset(stats);
    int i;
    arr = (uint32_t *)calloc(n_elements, sizeof(arr));
    //printf("shell:\n");
    mtrand_seed(seed);
    for (int a = 0; a<n_elements;a++){
        arr[a] = mtrand_rand64() & 0x3FFFFFFF;
    }
    shell_sort(stats, arr, n_elements);
    printf("Shell Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves, stats->compares);
    if (print_value > n_elements){
        for ( i=0;i<n_elements;i++){
            printf("%13" PRIu32, arr[i]);
	    //temp = i;
            if((i+1)%5 == 0 && i!=0){
               printf("\n");
        }}}
    else{
        for (i=0; i<print_value; i++){
            printf("%13" PRIu32, arr[i]);
	    //temp = i;
            if ((i+1)%5 == 0 && i!=0){
                printf("\n");
        }}}
    if ((i)%5 != 0){
    printf("\n");
	}
    free(arr);
    free(stats);

}return 0;
}
