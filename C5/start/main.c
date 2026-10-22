#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <string.h>

#define FAIL 0
#define SUCCESS 1


int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Incorrect amount of arguments\n");
        return FAIL;
    }
    const char *ext = strrchr(argv[1], '.'); // Last instance of . and returns what's after it.

    if (ext == NULL || strcmp(ext, ".vec") != 0) { /* Compares every single character to each other 
                                                    and returns 0 if they are the same */

        printf("Use .vec files only, no support for %s file type.", ext);
        return FAIL;
    }

    Vector v;
    v = createVectorFromFile(argv[1]);
    
    printVector(v);

    return SUCCESS;
}