#include "Hamming.h"

uint64_t Matrix_vector_multiplication(CodeHamming data){
    uint64_t syndrome = 0;
    uint64_t group_parity = 0;
    for(uint8_t i = 0; i < data.checks; i++){
        group_parity = 0;
        for(uint64_t j = 1; j <= (1ULL << data.checks) - 1; j++){
            if(j & (1ULL << i)){
                uint64_t bit = (data.vector[(j-1)/64] >> ((j-1) % 64)) & 1ULL;
                group_parity ^= bit;
            }
        }
        syndrome |= (group_parity << i);
    }
    return syndrome;
}
