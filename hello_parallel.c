#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main(){
#pragma omp parallel num_threads(100)

{   
    int thread_id = omp_get_thread_num();
    int all_threads_number = omp_get_num_threads();
    printf("Hallo Welt: Ich bin Thread Nummer %d von %d Threads\n", thread_id,all_threads_number );
}


    return 0;
}

