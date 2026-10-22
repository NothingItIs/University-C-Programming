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
    
    Vector v;
    v = createVectorFromFile(argv[1]);
    
    printVector(v);

    return SUCCESS;
}