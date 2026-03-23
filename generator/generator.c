#include <stdio.h>
#include <stdint.h>

int main(){
    int r;
    printf("число проверок: \n");
    if(!scanf("%d", &r)){
        return -1;
    }
    uint64_t n = (1ULL << r) - 1; 
    printf("длинна: %lu\n", n);
    printf("Позиция ошибки: ");

    uint64_t error_pos;
    if(!scanf("%lu", &error_pos)){
        return -1;
    }
    FILE *f = fopen("input.txt", "w");
    fprintf(f, "%d\n[", r);
    
    for(uint64_t i = 1; i <= n; i++){
        int bit = 1; 
        if(i == error_pos) bit = 0;
        fprintf(f, "%d", bit);
        if(i < n) fprintf(f, ",");
    }
    fprintf(f, "]\n");
    fclose(f);
    
    printf("r=%d, n=%lu, error at pos %lu\n", r, n, error_pos);
    printf("После декодирования все биты должны быть 1\n");
    return 0;
}
