#include <stdio.h>
#include <math.h>

#define FREQ 10
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void plotval(float x, int width){
    int pos = (width * x) + 0.5;
    for (int i = 0; i < pos; i++){
        printf(" ");
    }
    printf("*\n");
}

int main(void){
    unsigned long x;
    x = 0;
    for(;x < 1000; x++){
        double y = sin(x * FREQ * (M_PI / 180));
        y = (y+1)/2;
        printf("| x = %04lu y = %f | ", x, y);
        if (x % 10 == 0){
            printf("---");
        } else {
            printf("   ");
        }
        plotval(y, 40);
    }
}