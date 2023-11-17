#include "randstate.h"
#include <stdio.h>
#include <stdint.h>
#include <gmp.h>
#include <stdlib.h>

gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    srandom(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

void randstate_clear(void) {
    gmp_randclear(state);
}
