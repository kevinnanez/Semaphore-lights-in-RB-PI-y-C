#include <stdint.h>
#include <sem.h>
#define LENGTH_ARR 6

const ciclo_t mode_0[LENGTH_ARR] = {
    0b100010, 1000000000;
    0b100001, 2000000000;
    0b110100, 500000000;
    0b001100, 2000000000;
    0b010110, 500000000;
    0b000000, 0;
};

const ciclo_t mode_1[LENGTH_ARR] = {
    0b100001, 2000000000;
    0b100010, 1000000000;
    0b010100, 500000000;
    0b001100, 2000000000;
    0b010100, 500000000;
    0b000000, 0;
};

const ciclo_t mode_2[LENGTH_ARR] = {
    0b100001, 2000000000;
    0b100010, 1000000000;
    0b001100, 2000000000;
    0b000000, 1000000000;
    0b010100, 1000000000;
    0b000000, 0;
};

const ciclo_t emergency_mode[3] = {
	0b010010, 20000000;
    0b000000, 20000000;
    0b000000, 0;
};

ciclo_t* modes[] = {mode_0, mode_1, mode_2, emergency_mode};