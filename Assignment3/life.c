//life.c
#include "universe.h"

#include <inttypes.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DELAY   50000
#define OPTIONS "tsi:n:o:"
//creating a main with getopt and switch to use cases
int main(int argc, char **argv) {
    int opt = 0;
    int default_flag = 0;
    int ncurses = true;
    FILE *outfile = stdout;
    FILE *infile = stdin;
    uint32_t n_generations = 100;
    bool toroidal = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': ncurses = false; break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Failure opening the file(s).\n");
                fclose(infile);
                return 1;
            }
            break;
        case 'n': n_generations = strtol(optarg, NULL, 10); break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Failure opening the file(s), run ./life -H for more help.\n");
                fclose(outfile);
                return 1;
            }
            break;
        default: default_flag += 1; break;
        }
    }
    //if any case is called that isnt defined, this message will print
    if (default_flag > 0) {
        printf("SYNOPSIS\n");
        printf("    Conway's Game of Life\n");
        printf("\nUSAGE\n");
        printf("    ./life tsn:i:o:h\n");
        printf("\nOPTIONS\n");
        printf("    -t             Create your universe as a toroidal\n");
        printf("    -s             Silent - do not use animate the evolution\n");
        printf("    -n {number}    Number of generations [default: 100]\n");
        printf("    -i {file}      Input file [default: stdin]\n");
        printf("    -o {file}      Output file [default: stdout]\n");
        return 0;
    }
    uint32_t rows;
    uint32_t cols;
    //take the first line of the infile and use them as rows and columns
    //use these values to create an a and b universe
    //check if the uv populate is false to free and return an error message
    fscanf(infile, "%" PRIu32 "%" PRIu32, &rows, &cols);
    Universe *a = uv_create(rows, cols, toroidal);
    Universe *b = uv_create(rows, cols, toroidal);
    if (uv_populate(a, infile) == false) {
        free(a);
        free(b);
        fprintf(stderr, "Failure to populate.\n");
    }
    //set cursor like in figure 4
    if (ncurses == true) {
        initscr();
        curs_set(FALSE);
    }
    //loop through the generations, rows, and columns, as well as checking for live and dead cells with the 3 specified rules of the game of life
    //make cells alive again as well as dead..when the loops are over, the game is over, even if all of the cells arent dead
    //sleep for 50000 microseconds
    uint32_t generation;
    uint32_t row;
    uint32_t col;
    uint32_t neighbors;
    for (generation = 0; generation <= n_generations; generation++) {
        usleep(DELAY);
        for (row = 0; row < uv_rows(a); row++) {
            for (col = 0; col < uv_cols(a); col++) {
                neighbors = uv_census(a, row, col);
                if ((uv_get_cell(a, row, col) == true) && (neighbors == 2 || neighbors == 3)) {
                    uv_live_cell(b, row, col);
                    if (ncurses == true) {
                        mvprintw(row, col, "o");
                    }
                } else if ((uv_get_cell(a, row, col) == false) && (neighbors == 3)) {
                    uv_live_cell(b, row, col);
                    if (ncurses == true) {
                        mvprintw(row, col, "o");
                    }
                } else {
                    uv_dead_cell(b, row, col);
                }
            }
        }
        //create a temporary universe to use to swap the a and b universe, then clear the screen
        Universe *temp = uv_create(rows, cols, toroidal);
        refresh();
        usleep(DELAY);
        temp = b;
        b = a;
        a = temp;
        clear();
    }
    //close the window, print out the ending grid to stdout, close the files, and delete the 2 universes
    endwin();
    uv_print(b, outfile);
    fclose(infile);
    fclose(outfile);
    uv_delete(a);
    uv_delete(b);
    return 0;
}
