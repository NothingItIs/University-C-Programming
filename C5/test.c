#include <stdio.h>
#include <stdlib.h>

int main(void){
    char *x = calloc(5, sizeof(int));
    x = "hi";
    printf("%s", x);
    return 0;
}