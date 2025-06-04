// compile with gcc -O0 bench.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cblock_struct {
    volatile unsigned long next;
    volatile unsigned long pad2[7];
} __attribute((packed));

#define WORKING_SET_SIZE_LIM (1024 * 1024UL * 4)  // 4MB
#define REPS 100

int main() {
    register unsigned long working_set_size;

    volatile struct cblock_struct *pool = (volatile struct cblock_struct *)malloc(WORKING_SET_SIZE_LIM * sizeof(struct cblock_struct));
    volatile unsigned long acc = 1;

    for (working_set_size = 1; working_set_size < WORKING_SET_SIZE_LIM; working_set_size *= 2) {
        for (unsigned long i = 0; i < WORKING_SET_SIZE_LIM; i++) {
            pool[i].next = (i + 1) % working_set_size;
        }

        clock_t start = clock();
        register unsigned long next_idx = 0;
        for (register unsigned long i = 0; i < WORKING_SET_SIZE_LIM * REPS; i++) {
            // INSERT CODE HERE
        }
        clock_t end = clock();
        printf("%lu %f\n", working_set_size * sizeof(struct cblock_struct), (double)(end - start) / CLOCKS_PER_SEC);
    }
}
