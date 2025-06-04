// compile with gcc -O0 bench.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_SIZE 10000000

unsigned long test_data[TEST_SIZE];

double bench(unsigned long ratio) {
    // Generate random data
    for (unsigned long i = 0; i < TEST_SIZE; i++) {
        test_data[i] = rand() % 100; //random number from 0 to 99
    }

    volatile unsigned long x;
    clock_t before = clock();
    for (unsigned long i = 0; i < TEST_SIZE; i++) {
  	//TODO 
    }
    clock_t after = clock();

    return ((double)(after - before)) / CLOCKS_PER_SEC;
}

int main() {
    for (unsigned long i = 0; i <= 100; i++) {
        double time = bench(i);
        printf("%d, %f\n", i, time);
    }
}

