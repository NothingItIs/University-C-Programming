/*
 *         File: analyse.c
 *       Author: Steve Gunn
 *      License: MIT License
 *         Date: 27th October 2018
 *  Description: Program to read in a netlist file of a circuit, perform modified nodal analysis and display the result.
 */

#include <stdio.h>
#include <stdlib.h>
#include "circuit.h"
#include <string.h>

#define FAIL 0
#define SUCCESS 1

int main(int argc, char *argv[])
{
	Circuit c;
	
    if (argc != 2) {
        printf("Incorrect amount of arguments\n");
        return FAIL;
    }

    c = createCircuitFromFile(argv[1]);
    analyseCircuit(c);
    destroyCircuit(c);

	return SUCCESS;
}

