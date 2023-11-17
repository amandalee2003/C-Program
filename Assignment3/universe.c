#include "universe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//struct to refer to in all .c files when calling u->__
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};
//using calloc to create a universe and for looping through a grid, setting all indexes to a calloc
//setting toroidal, rows, and cols to the parameter values
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    if (u == NULL) {
        free(u);
        u = NULL;
    }
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t i = 0; i < rows; i++) {
        u->grid[i] = (bool *) calloc(cols, sizeof(bool));
    }
    u->toroidal = toroidal;
    u->rows = rows;
    u->cols = cols;
    return u;
}
//free the grid and universe
//set the variables to null as well
//for loop the grid for freeing and nulling
void uv_delete(Universe *u) {
    for (uint32_t i = 0; i < u->rows; i++) {
        free(u->grid[i]);
        u->grid[i] = NULL;
    }
    free(u);
    u = NULL;
}
//return the rows value
uint32_t uv_rows(Universe *u) {
    return u->rows;
}
//return the cols value
uint32_t uv_cols(Universe *u) {
    return u->cols;
}
//check if the grid is in bounds and if so, return true
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= u->rows || c >= u->cols) {
        u->grid[r][c] = false;
    } else {
        u->grid[r][c] = true;
    }
}
//set the grid at row and column to false
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    u->grid[r][c] = false;
}
//check if the grid is true or false and return the boolean
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= u->rows || c >= u->cols) {
        return false;
    } else if (u->grid[r][c] == false) {
        return false;
    } else if (u->grid[r][c] == true) {
        return true;
    } else {
        return u->grid[r][c];
    }
}
//for loop until the end of file is reached, which scanning and setting the values to row and column
//check if these values are in bounds, and if so, then call uv live cell and return true
bool uv_populate(Universe *u, FILE *infile) {
    uint32_t col;
    uint32_t row;
    while (!feof(infile)) {
        fscanf(infile, "%d %d", &row, &col);
        if (row > u->rows || col > u->cols) {
            return false;
        }
        uv_live_cell(u, row, col);
    }
    return true;
}
//checking ALL cases for corner, edge, and middle coordinates on the grid
//these cases are checking for both toroidal and nontoroidal values
//torodial will wrap around to their corresponding values
//the nontoroidal will not create neighbors out of bounds as neighbors
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t neighbors = 0;
    if (u->toroidal == true) {
        //valid neighbors
        if (r == 0 && c > 0 && c < (u->cols - 1)) { //upper edge case
            if (uv_get_cell(u, r, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, c + 1) == true) {
                neighbors += 1;
            }
        } else if (r == (u->rows - 1) && c == (u->cols - 1)) { //bottom right corner case
            if (uv_get_cell(u, r - 1, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 1, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, 1) == true) {
                neighbors += 1;
            }
        } else if (c == 0 && r == 0) { //top left corner case
            if (uv_get_cell(u, r + 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, u->cols - 2) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 2, 0) == true) {
                neighbors += 1;
            }

        } else if (r == 0 && c == (u->cols - 1)) { //top right corner case
            if (uv_get_cell(u, r + 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 2, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, 0) == true) {
                neighbors += 1;
            }

        } else if (c == 0 && r == (u->rows - 1)) { //bottom left corner case
            if (uv_get_cell(u, r - 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 1, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, u->cols - 2) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, u->rows - 1, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, u->cols - 1) == true) {
                neighbors += 1;
            }

        } else if (c == 0 && r > 0 && r < (u->rows - 1)) { //left edge case
            if (uv_get_cell(u, r, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, u->cols - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, u->cols - 1) == true) {
                neighbors += 1;
            }
        } else if (r == (u->rows - 1) && c > 0 && c < (u->cols - 1)) { //bottom edge case
            if (uv_get_cell(u, 0, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, 0, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c + 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c - 1) == true) {
                neighbors += 1;
            }
        } else if (c == (u->cols - 1) && r > 0 && r < (u->rows - 1)) { //right edge case
            if (uv_get_cell(u, r + 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r - 1, c - 1) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, 0) == true) {
                neighbors += 1;
            }
            if (uv_get_cell(u, r + 1, c - 1) == true) {
                neighbors += 1;
            }
        } else { //any middle case that doesnt go off the edge
            if (r >= 0 && r <= u->rows && c + 1 >= 0 && c + 1 <= u->cols
                && (uv_get_cell(u, r, c + 1) == true)) {
                neighbors += 1;
            }
            if (r + 1 >= 0 && r + 1 <= u->rows && c >= 0 && c <= u->cols
                && (uv_get_cell(u, r + 1, c) == true)) {
                neighbors += 1;
            }
            if (r >= 0 && r <= u->rows && c - 1 >= 0 && c - 1 <= u->cols
                && (uv_get_cell(u, r, c - 1) == true)) {
                neighbors += 1;
            }
            if (r - 1 >= 0 && r - 1 <= u->rows && c >= 0 && c <= u->cols
                && (uv_get_cell(u, r - 1, c) == true)) {
                neighbors += 1;
            }
            if (r + 1 >= 0 && r + 1 <= u->rows && c + 1 >= 0 && c + 1 <= u->cols
                && (uv_get_cell(u, r + 1, c + 1) == true)) {
                neighbors += 1;
            }
            if (r - 1 >= 0 && r - 1 <= u->rows && c - 1 >= 0 && c - 1 <= u->cols
                && (uv_get_cell(u, r - 1, c - 1) == true)) {
                neighbors += 1;
            }
            if (r - 1 >= 0 && r - 1 <= u->rows && c + 1 >= 0 && c + 1 <= u->cols
                && (uv_get_cell(u, r - 1, c + 1) == true)) {
                neighbors += 1;
            }
            if (r + 1 >= 0 && r + 1 <= u->rows && c - 1 >= 0 && c - 1 <= u->cols
                && (uv_get_cell(u, r + 1, c - 1) == true)) {
                neighbors += 1;
            }
        }
        return neighbors;
    } else {
        //all neighbors
        if (r >= 0 && r <= u->rows && c + 1 >= 0 && c + 1 <= u->cols
            && (uv_get_cell(u, r, c + 1) == true)) {
            neighbors += 1;
        }
        if (r + 1 >= 0 && r + 1 <= u->rows && c >= 0 && c <= u->cols
            && (uv_get_cell(u, r + 1, c) == true)) {
            neighbors += 1;
        }
        if (r >= 0 && r <= u->rows && c - 1 >= 0 && c - 1 <= u->cols
            && (uv_get_cell(u, r, c - 1) == true)) {
            neighbors += 1;
        }
        if (r - 1 >= 0 && r - 1 <= u->rows && c >= 0 && c <= u->cols
            && (uv_get_cell(u, r - 1, c) == true)) {
            neighbors += 1;
        }
        if (r + 1 >= 0 && r + 1 <= u->rows && c + 1 >= 0 && c + 1 <= u->cols
            && (uv_get_cell(u, r + 1, c + 1) == true)) {
            neighbors += 1;
        }
        if (r - 1 >= 0 && r - 1 <= u->rows && c - 1 >= 0 && c - 1 <= u->cols
            && (uv_get_cell(u, r - 1, c - 1) == true)) {
            neighbors += 1;
        }
        if (r - 1 >= 0 && r - 1 <= u->rows && c + 1 >= 0 && c + 1 <= u->cols
            && (uv_get_cell(u, r - 1, c + 1) == true)) {
            neighbors += 1;
        }
        if (r + 1 >= 0 && r + 1 <= u->rows && c - 1 >= 0 && c - 1 <= u->cols
            && (uv_get_cell(u, r + 1, c - 1) == true)) {
            neighbors += 1;
        }
    }
    return neighbors;
}

void uv_print(Universe *u, FILE *outfile) {
    char o = 'o';
    char dot = '.';
    uint32_t r = 0;
    for (r = 0; r < u->rows; r++) {
        for (uint32_t c = 0; c < u->cols; c++) {
            if (u->grid[r][c] == false) {
                fprintf(outfile, "%c", dot);
            }
            if (u->grid[r][c] == true) {
                fprintf(outfile, "%c", o);
            }
        }
        printf("\n");
    }
}
