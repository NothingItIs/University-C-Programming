#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"
#include <string.h>

#define FAIL 0
#define SUCCESS 1

int main(int argc, char *argv[])
{
    Vector v;
    Matrix m;

    if (argc != 3) {
        printf("Incorrect amount of arguments\n");
        return FAIL;
    }

    const char *ext = strrchr(argv[1], '.'); // Last instance of . and returns what's after it.

    if (ext == NULL || strcmp(ext, ".vec") != 0) { /* Compares every single character to each other 
                                                    and returns 0 if they are the same */

        printf("Use .vec files only, no support for %s file type.", ext);
        return FAIL;
    }

    const char *ext2 = strrchr(argv[2], '.'); // Last instance of . and returns what's after it.

    if (ext2 == NULL || strcmp(ext2, ".mat") != 0) { /* Compares every single character to each other 
                                                    and returns 0 if they are the same */

        printf("Use .mat files only, no support for %s file type.", ext2);
        return FAIL;
    }

    v = createVectorFromFile(argv[1]);

    printf("VECTOR:\n");
    printVector(v); 

    m = createMatrixFromFile(argv[2]);

    printf("MATRIX:\n");
    printMatrix(m);

    return SUCCESS;
}