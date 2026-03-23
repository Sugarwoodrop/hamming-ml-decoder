#include "rwfile.h"

int readfile(char *filename, CodeHamming *codeHamming){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        return ERROR;
    }
    int checks;
    if(readChecks(file ,&checks) == ERROR){
        fclose(file);
        return ERROR;
    }
    if(checks <= 0 || checks > 30){
        return ERROR;
    }
    codeHamming->checks = checks;
    if(readVector(file, codeHamming) == ERROR){
        fclose(file);
        return ERROR;
    }
    fclose(file);
    return SUCCES;
}

int readChecks(FILE *file, int *checks){
    if(fscanf(file,"%d",checks) != 1){
        return ERROR;
    }
    return SUCCES;
}
int readVector(FILE *file, CodeHamming *codeHamming){
    char cursor;
    uint8_t bit;
    uint64_t n = 0;
    if(fscanf(file, " %c", &cursor) == EOF){
        return ERROR;
    }
    codeHamming->vector = realloc(codeHamming->vector, codeHamming->sizevector * sizeof(uint64_t ));
    if(cursor == '['){
        while(1){
            if(codeHamming->numberbit >=64){
                codeHamming->numberbit = 0;
                codeHamming->sizevector++;
                codeHamming->vector = realloc(codeHamming->vector, codeHamming->sizevector * sizeof(uint64_t ));
                codeHamming->vector[codeHamming->sizevector-1] = 0;
            }
            if(fscanf(file, "%hhu", &bit) != 1){
                return ERROR;
            }
            codeHamming->vector[codeHamming->sizevector-1] |= ((uint64_t)bit << codeHamming->numberbit);
            codeHamming->numberbit++;
            n++;
            if(fscanf(file, "%c", &cursor) != 1){
                return ERROR;
            }
            if(cursor == ']'){
                if(n != ((1ULL << codeHamming->checks)-1)){
                    printf("Неверная длинна кода");
                    return ERROR;
                }
                break;
            }
            if(cursor == ','){
                continue;
            }
        }
    }
    return SUCCES;
}

int writefile(CodeHamming data, const char *filename, long time) {
    FILE *f = fopen(filename, "w");
    if (!f) return ERROR;

    uint64_t n = (1ULL << data.checks) - 1;

    fprintf(f, "[");
    for (uint64_t j = 0; j < n; j++) {
        uint64_t bit = (data.vector[j / 64] >> (j % 64)) & 1ULL;
        fprintf(f, "%lu", bit);
        if (j < n - 1) fprintf(f, ",");
    }
    fprintf(f, "]\n");
    long stop = clock();
    long ms = (long)(stop - time) * 1000  / CLOCKS_PER_SEC;
    printf("%ld ms\n", ms);
    fprintf(f, "%ldms\n", ms);
    fclose(f);
    return 0;
}
