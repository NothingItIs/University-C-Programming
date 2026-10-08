#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define EQUATION(x) (pow(x, 2) - 4)

#define POPSIZE 100
#define INIT_RANGE 20

float rnd(){
    return rand() / (float)RAND_MAX;
}

void initpop(int pop[], int size){ /* pop[] here acts as both an array 
                                    and a pointer to the argument inputed*/
    
    
    for (int i = 0; i < size; i++){ /* go thru each one, and as long as it's 
                                    below it's maximum (POPSIZE) and since arrays
                                    always end in \0 we don't need to do size+1. 
                                    Then it cycles thru every position and
                                    initializes a value into it.*/
                                    
        pop[i] = (rnd() -0.5) * INIT_RANGE; /* This is to ensure that it spreads thru a range
                                            since rnd() returns a value 0..1, -0.5 ensures it can 
                                            go into the negatives (to make negative values possible)
                                            and then we multiply by the range to ensure we covera 
                                            wide range of values*/
    }
}

void offspring(float parent, float mutst, float pop[], int size){
    int i = 0;
    pop[0] = parent; /* to ensure only a BETTER offspring survives, so if none appear the parent survives 
                        again*/
    for (i = 1; i < size; i++){ /* For every next organism within the population size*/
        pop[i] = parent + (rnd() - 0.5) * mutst; /*ensuring both positive and negative mutations
                                                    can happen*/


    }

}