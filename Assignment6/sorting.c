//sorting.c
#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "asbqhr:n:p:H"
//creating a main with getopt and switch to use cases
int main(int argc, char **argv) {
    int opt = 0;
    int a_flag = 0;
    int b_flag = 0;
    int h_flag = 0;
    int q_flag = 0;
    int s_flag = 0;
    int n_elements = 100;
    int print_value = 100;
    int seed = 13371453;
    Stats *stats = calloc(1, sizeof(Stats));
    Set sets = set_empty();
    uint32_t *arr = (uint32_t *) calloc(n_elements, sizeof(arr));
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        //case a will set all the inserts are add one to the a flag
        case 'a':
            a_flag += 1;
            sets = set_insert(sets, 1);
            sets = set_insert(sets, 2);
            sets = set_insert(sets, 3);
            sets = set_insert(sets, 4);
            break;
        case 's':
            //case s will add one to the s flag and set the sets to the set insert of 1 (1 represents shell)
            s_flag += 1;
            sets = set_insert(sets, 1);
            break;
        //case b will add one to the b flag and set the sets to the set insert of 2 (2 represents batcher)
        case 'b':
            b_flag += 1;
            sets = set_insert(sets, 2);
            break;
        //case q will add one to the q flag and set the sets to the set insert of 4 (4 represents quick)
        case 'q':
            q_flag += 1;
            sets = set_insert(sets, 4);
            break;
        //case h will add one to the h flag and set the sets to the set insert of 3 (3 represents heap)
        case 'h':
            h_flag += 1;
            sets = set_insert(sets, 3);
            break;
        //case r sets the seed to the user input or the default value
        case 'r':
            seed = strtoul(optarg, NULL, 10);
            //seed = atoi(optarg);
            break;
        //case n sets the n elements to the user input or default value
        case 'n':
            //n_elements = atoi(optarg);
            n_elements = strtoul(optarg, NULL, 10);
            break;
        //case p sets the print value to the user input or default value
        case 'p':
            print_value = strtoul(optarg, NULL, 10);
            //print_value = atoi(optarg);
            break;
        //case H prints out the synopsis, usage, and options
        case 'H':
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n");
            printf("\nUSAGE\n");
            printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n");
            printf("\nOPTIONS\n");
            printf("   -H              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -s              Enable Shell Sort.\n");
            printf("   -b              Enable Batcher Sort.\n");
            printf("   -h              Enable Heap Sort.\n");
            printf("   -q              Enable Quick Sort.\n");
            printf("   -n length       Specify number of array elements (default: 100).\n");
            printf("   -p elements     Specify number of elements to print (default: 100).\n");
            printf("   -r seed         Specify random seed (default: 13371453).\n");
            return 0;
        default:
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n");
            printf("\nUSAGE\n");
            printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n");
            printf("\nOPTIONS\n");
            printf("   -H              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -s              Enable Shell Sort.\n");
            printf("   -b              Enable Batcher Sort.\n");
            printf("   -h              Enable Heap Sort.\n");
            printf("   -q              Enable Quick Sort.\n");
            printf("   -n length       Specify number of array elements (default: 100).\n");
            printf("   -p elements     Specify number of elements to print (default: 100).\n");
            printf("   -r seed         Specify random seed (default: 13371453).\n");
            return 0;
        }
    }
    //if no sort type is specified, then print
    if (a_flag == 0 && b_flag == 0 && q_flag == 0 && s_flag == 0 && h_flag == 0) {
        printf("Select at least one sort to perform.\n");
        printf("SYNOPSIS\n");
        printf("   A collection of comparison-based sorting algorithms.\n");
        printf("\nUSAGE\n");
        printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n");
        printf("\nOPTIONS\n");
        printf("   -H              Display program help and usage.\n");
        printf("   -a              Enable all sorts.\n");
        printf("   -s              Enable Shell Sort.\n");
        printf("   -b              Enable Batcher Sort.\n");
        printf("   -h              Enable Heap Sort.\n");
        printf("   -q              Enable Quick Sort.\n");
        printf("   -n length       Specify number of array elements (default: 100).\n");
        printf("   -p elements     Specify number of elements to print (default: 100).\n");
        printf("   -r seed         Specify random seed (default: 13371453).\n");
        return 0;
    }

    //shell sort which checks for the set member, and creates an array with calloc, and fill it using a random number from the seed and number of elements
    //the code will be printed with 13 digits, and will print a new line after 5 elements have been counted, or if the print is over
    //the array and stats will then be freed
    if (set_member(sets, 1)) {
        reset(stats);
        int i;
        arr = (uint32_t *) calloc(n_elements, sizeof(arr));
        srandom(seed);
        for (int j = 0; j < n_elements; j++) {
            arr[j] = random() & 0x3FFFFFFF;
        }
        shell_sort(stats, arr, n_elements);
        printf("Shell Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves,
            stats->compares);
        if (print_value > n_elements) {
            for (i = 0; i < n_elements; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        } else {
            for (i = 0; i < print_value; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        }
        if ((i) % 5 != 0) {
            printf("\n");
        }
        free(arr);
        free(stats);
    }

    //batcher sort which checks for the set member, and creates an array with calloc, and fill it using a random number from the seed and number of elements
    //the code will be printed with 13 digits, and will print a new line after 5 elements have been counted, or if the print is over
    //the array and stats will then be freed
    if (set_member(sets, 2)) {
        reset(stats);
        int i;
        arr = (uint32_t *) calloc(n_elements, sizeof(arr));
        srandom(seed);
        for (int j = 0; j < n_elements; j++) {
            arr[j] = random() & 0x3FFFFFFF;
        }
        batcher_sort(stats, arr, n_elements);
        printf("Batcher Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves,
            stats->compares);
        if (print_value > n_elements) {
            for (i = 0; i < n_elements; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        } else {
            for (i = 0; i < print_value; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        }
        if ((i) % 5 != 0) {
            printf("\n");
        }
        free(arr);
        free(stats);
    }
    //heap sort which checks for the set member, and creates an array with calloc, and fill it using a random number from the seed and number of elements
    //the code will be printed with 13 digits, and will print a new line after 5 elements have been counted, or if the print is over
    //the array and stats will then be freed
    if (set_member(sets, 3)) {
        reset(stats);
        int i;
        arr = (uint32_t *) calloc(n_elements, sizeof(arr));
        srandom(seed);
        for (int j = 0; j < n_elements; j++) {
            arr[j] = random() & 0x3FFFFFFF;
        }
        heap_sort(stats, arr, n_elements);
        printf("Heap Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves,
            stats->compares);
        if (print_value > n_elements) {
            for (i = 0; i < n_elements; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        } else {
            for (i = 0; i < print_value; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        }
        if ((i) % 5 != 0) {
            printf("\n");
        }
        free(arr);
        free(stats);
    }
    //quick sort which checks for the set member, and creates an array with calloc, and fill it using a random number from the seed and number of elements
    //the code will be printed with 13 digits, and will print a new line after 5 elements have been counted, or if the print is over
    //the array and stats will then be freed
    if (set_member(sets, 4)) {
        reset(stats);
        int i;
        arr = (uint32_t *) calloc(n_elements, sizeof(arr));
        srandom(seed);
        for (int j = 0; j < n_elements; j++) {
            arr[j] = random() & 0x3FFFFFFF;
        }
        quick_sort(stats, arr, n_elements);
        printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_elements, stats->moves,
            stats->compares);
        if (print_value > n_elements) {
            for (i = 0; i < n_elements; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        } else {
            for (i = 0; i < print_value; i++) {
                printf("%13" PRIu32, arr[i]);
                if ((i + 1) % 5 == 0 && i != 0) {
                    printf("\n");
                }
            }
        }
        if ((i) % 5 != 0) {
            printf("\n");
        }
        free(arr);
        free(stats);
    }

    return 0;
}
