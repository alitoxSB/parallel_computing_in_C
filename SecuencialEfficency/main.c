#include <stdio.h>
#include <math.h>
#include <string.h>
#include "stdlib.h"

// Justin Alejandro Zamora Esquivel.
// Lead University - Parallel Computing.


double t_serial(double n){
    return n*n;
}

double t_parallel(double n, double p){
    return ((n*n)/p) + log2(p);
}
double speedup(double serial, double parallel){
    return serial/parallel;
}

double efficiency(double speedup, double p){
    return speedup/p;
}

void program(){

    double n;
    double p;

    printf("Write n:\n");
    scanf("%lf", &n);

    printf("Write processors:\n");
    scanf("%lf", &p);

    printf("The speedup is: %lf", speedup(t_serial(n), t_parallel(n, p)));
    printf("\nThe efficency of process is: %lf", efficiency(speedup(t_serial(n), t_parallel(n, p)), p));
    printf("\n");

}

void msg(){
    printf("*----* Welcome to TC1 *----*\n"
           "1: Run Speedup and Efficency\n"
           "2: Exit \n"
           "Write a option: ");
}

int main() {

    int option = 0;

    while (option!=2){
        msg();
        scanf("%i", &option);
        if(option==1){
            program();
        }
    }
    return 0;
}