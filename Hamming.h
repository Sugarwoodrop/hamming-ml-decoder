#include <stdio.h>
#include <stdint.h>

typedef struct CodeHamming{
    uint64_t *vector;
    uint8_t numberbit;
    uint64_t sizevector;
    uint64_t checks;
}CodeHamming;

uint64_t Matrix_vector_multiplication(CodeHamming data);
