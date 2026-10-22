#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"
#include <string.h>

#define FAIL 0
#define SUCCESS 1

int main(int argc, char *argv[])
{
    Matrix m;

    if (argc != 2) {
        printf("Incorrect amount of arguments\n");
        return FAIL;
    }

    m = createMatrixFromFile(argv[1]);

    printf("MATRIX:\n");
    printMatrix(m);

    return SUCCESS;
}