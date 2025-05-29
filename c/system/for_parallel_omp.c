/*
Dieses Programm demonstriert die Verwendung von OpenMP zur parallelen Berechnung.
Es füllt ein großes Array mit Werten, die durch die Funktion myFunc berechnet werden.
Anschließend wird die benötigte Zeit für die Berechnung gemessen und ausgegeben.
*/


#include <math.h>
#include <stdio.h>
#include <omp.h>
#include "myFunction.h"


int main() {

    int size = 1000000, i;
    double start = omp_get_wtime();
    double myArray[size];

    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        myArray[i] = myFunc(i);
    }

    printf("\n<<< Fertig >>>\n");

    double end = omp_get_wtime();
    printf("The time needed : %f ns\n", end - start);

    return 0;
}

