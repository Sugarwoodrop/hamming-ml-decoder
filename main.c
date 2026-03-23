#include "rwfile.h"

int main(){
    long start = clock();
    CodeHamming data;
    data.sizevector = 1;
    data.numberbit = 0;
    if(readfile("input.txt", &data) == ERROR){
        printf("ОШИБКА ПРИ ЧТЕНИЕ");
        return ERROR;
    }
    uint64_t syndrome = Matrix_vector_multiplication(data);
    printf("syndrome = %lu\n", syndrome);
    if(syndrome != 0){
        data.vector[(syndrome-1) / 64] ^= (1ULL << ((syndrome-1) % 64));
    }
    if(writefile(data, "output.txt", start) == ERROR){
        return ERROR;
    }
    free(data.vector); 
    return SUCCES;
}
