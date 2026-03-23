#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "Hamming.h"

#define ERROR -1
#define SUCCES 0

int readfile(char *file, CodeHamming *codeHamming);
int readChecks(FILE *file, int *checks);
int readVector(FILE *file, CodeHamming *codeHamming);

int writefile(CodeHamming data, const char *filename, long time);
