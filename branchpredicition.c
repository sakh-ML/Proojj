// compile with gcc -O0 branchprediciton.c (name.c)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_SIZE 10000000

unsigned long test_data[TEST_SIZE];

double bench(unsigned long ratio) {
    // Generate random data
    for (unsigned long i = 0; i < TEST_SIZE; i++) {
        test_data[i] = rand() % 100; // random number von 0 bis 99
    }
    //ratio is the perecnatge of branching
    volatile unsigned long x;
    clock_t before = clock();
    for (unsigned long i = 0; i < TEST_SIZE; i++) {

        if(test_data[i] >= ratio){
            ++x;
        }
        else{
            ++x;
        }




    }
    clock_t after = clock();

    return ((double)(after - before)) / CLOCKS_PER_SEC; // brenchen wir die Laufzeit
}

int main() {
    for (unsigned long i = 0; i <= 100; i++) {
        double time = bench(i); // branch ratio
        printf("%d, %f\n", i, time);
    }
}

