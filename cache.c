// compile with gcc -O0 name.c (cache.c)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cblock_struct
{
    volatile unsigned long next;
    volatile unsigned long pad2[7];
} __attribute((packed));

#define WORKING_SET_SIZE_LIM (1024 * 1024UL * 4) // 4MB
#define REPS 100

int main()
{
    register unsigned long working_set_size;

    volatile struct cblock_struct *pool = (volatile struct cblock_struct *)malloc(WORKING_SET_SIZE_LIM * sizeof(struct cblock_struct));
    volatile unsigned long acc = 1;

    // von 1 bis 4MB
    for (working_set_size = 1; working_set_size < WORKING_SET_SIZE_LIM; working_set_size *= 2)
    {
        // von 1 wieder bis 4MB dieses mal mit working_set_size 1 dann 2 dann 4 ... also (2 hoch x)
        for (unsigned long i = 0; i < WORKING_SET_SIZE_LIM; i++)
        {
            pool[i].next = (i + 1) % working_set_size;
    
        }

        for(unsigned long i = 0; i < WORKING_SET_SIZE_LIM; ++i){
            
            unsigned long p1 = (rand() % working_set_size);
            unsigned long p2 = (rand() % working_set_size);

            unsigned long store = pool[p1].next;
            pool[p1].next = pool[p2].next;
            pool[p2].next = store;
        }

        clock_t start = clock();
        register unsigned long next_idx = 0;
        //von 1 bis 400MB
        for (register unsigned long i = 0; i < WORKING_SET_SIZE_LIM * REPS; i++)
        {
            next_idx = pool[next_idx].next; // setzen next_idx auf dem näcst wert vom pool[next_idx]

        }
        clock_t end = clock();
        printf("%lu %f\n", working_set_size * sizeof(struct cblock_struct), (double)(end - start) / CLOCKS_PER_SEC);
    }
}
