#include <stdio.h>
#include <math.h>

#define FREQ 10

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define width_ 40

#define complicated 1

#ifdef complicated

void plotval(float x, int width){
    int pos = (width * x) + 0.5;
    for (int i = 0; i < (width+1); i++){
        if (i == pos){
            printf("*");
        } else if (i == width/2){
            printf("|");
        } else {
            if (i < pos){
                printf("-");
            } else {
                printf("&");
            }
        }
    }
    printf("\n");
}

#else
void plotval(float x, int width){
    int pos = (width * x) + 0.5;
    for (int i = 0; i < pos; i++){
        printf(" ");
    }
    printf("*\n");
}
#endif

int main(void){
    unsigned long x;
    x = 0;
    for(;x < 1000; x++){
        double y = sin(x * FREQ * (M_PI / 180));
        y = (y+1)/2;
        printf("| x = %04lu y = %5.2f | ", x, y);
        if (x % 10 == 0){
            printf("---");
        } else {
            printf("   ");
        }
        plotval(y, width_);
    }
}