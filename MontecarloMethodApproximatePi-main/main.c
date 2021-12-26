#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define SEED 87878784 /*Defined seed for random numbers*/

int main() {

    int iterations;
    double x,y,z,pi;
    int count=0;

    printf("Enter the iterations for estimate Pi: ");
    scanf("%i",&iterations);

    /*Function for generate random numbers (points goes to square and circle)*/
    srand(SEED);
    for (int i=0; i < iterations; i++) {
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        z = x*x+y*y;
        if (z<=1) count++;
    }
    pi = (double)count / iterations * 4;

    printf("Estimate of pi is %lf \n",pi);
}

