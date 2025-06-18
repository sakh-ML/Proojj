//Use libnuma to allocate memory on a specific numa node

#define _GNU_SOURCE

#include <numa.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sysinfo.h>
#include <time.h>

#include <pthread.h>

//Is set to 1GB (keep in mind that the System has 0.5GB L3 Cache)
#define NUMA_BUFFER_SIZE 0x40000000UL
#define NUMBER_RANDOM_ACCESSES 0x8000000UL

unsigned int count_numa_nodes;
//This is an array of void *, holding allocated memory for each numa node
void **numa_buffers;

unsigned int count_threads;
pthread_t *core_threads;
pthread_mutex_t *core_release_mutex;

void *thread_fun(void *arg);

unsigned long *measure_results;

int main(int argc, char **argv){
    
    //The function returns the numa node with the highest number, so +1
    count_numa_nodes=numa_max_node()+1;
    printf("The system provides %d numa nodes\n", count_numa_nodes);
    
    numa_buffers=(void **)(malloc(sizeof(void *)*count_numa_nodes));
    for(unsigned int i=0;i<count_numa_nodes;i++){
        numa_buffers[i]=(void *)(numa_alloc_onnode(NUMA_BUFFER_SIZE,i));
        printf("Allocated buffer of size 0x%lx on node %d: 0x%p\n", NUMA_BUFFER_SIZE,i,numa_buffers[i]);
    }
    
    //Touch the memory before to create pagetables in the os
    for(unsigned int i=0;i<count_numa_nodes;i++){
        volatile unsigned long *ptr=(volatile unsigned long *)(numa_buffers[i]);
        for(unsigned long x=0;x<NUMA_BUFFER_SIZE/sizeof(unsigned long);x++){
            ptr[x]=0x1;
        }
    }
    
    measure_results=(unsigned long *)(malloc(sizeof(unsigned long)*count_numa_nodes));
    
    count_threads=get_nprocs();
    printf("Found %d available CPU threads\n",count_threads);
    
    core_threads=(pthread_t *)(malloc(sizeof(pthread_t)*count_threads));
    core_release_mutex=(pthread_mutex_t *)(malloc(sizeof(pthread_mutex_t)*count_threads));
    
    //Create one pthread per thread
    for(unsigned long i=0;i<count_threads;i++){
        //Create and lock all mutextes to make the threads wait
        pthread_mutex_init(core_release_mutex+i,0);
        pthread_mutex_lock(core_release_mutex+i);
        
        if(pthread_create(core_threads+i,0,thread_fun,(void *)i)!=0){
            printf("Error creating pthread for thread %ld\n",i);
            exit(1);
        }
    }
    
    //Release the first thread
    pthread_mutex_unlock(core_release_mutex);
    
    //Wait for the threads to finish
    for(unsigned long i=0;i<count_threads;i++){
        if(pthread_join(core_threads[i],0)!=0){
            printf("Error joining pthread for thread %ld\n",i);
            exit(1);
        }
    }
    
    
    free(core_threads);
    free(core_release_mutex);
    free(measure_results);
    for(unsigned int i=0;i<count_numa_nodes;i++){
        numa_free(numa_buffers[i], NUMA_BUFFER_SIZE);
    }
    free(numa_buffers);
    
    return 0;
}

int ptr_cmp (const void *a, const void *b){
    unsigned long **a_p=(unsigned long **)a;
    unsigned long **b_p=(unsigned long **)b;
    return **a_p-**b_p;
}

void print_range_numbers(){
    //The trick is to sort an array of pointers to the measure array
    unsigned long **ptr_array=(unsigned long **)(malloc(sizeof(unsigned long *)*count_numa_nodes));
    for(unsigned long i=0;i<count_numa_nodes;i++){
        ptr_array[i]=measure_results+i;
    }
    qsort(ptr_array,count_numa_nodes,sizeof(unsigned long *), ptr_cmp);
    //Print the ranges
    for(unsigned long i=0;i<count_numa_nodes;i++){
        unsigned long range=((unsigned long)ptr_array[i])-((unsigned long)measure_results);
        range /= (sizeof(unsigned long));
        printf("%ld\t", range);
    }
    free(ptr_array);
}

void *thread_fun(void *arg){
    unsigned long thread_num=(unsigned long)arg;
    
    //Pin the pthread to the specific thread
    cpu_set_t cpuset;
    pthread_t me=pthread_self();
    
    CPU_ZERO(&cpuset);
    CPU_SET(thread_num,&cpuset);
    
    if(pthread_setaffinity_np(me, sizeof(cpu_set_t),&cpuset)!=0){
        printf("Error pinning pthread for thread %ld\n",thread_num);
        exit(1);
    }
    
    //Wait for this task to be released0
    pthread_mutex_lock(core_release_mutex+thread_num);
    
    //Perform random accesses to each numa node and measure access latencies
    volatile long a = 0;

    struct timespec start, end;
    for(unsigned int node = 0; node < count_numa_nodes; ++node){

        volatile unsigned long *buffer = (volatile unsigned long *)numa_buffers[node];
        unsigned long entries = NUMA_BUFFER_SIZE / sizeof(unsigned long);
        unsigned long sum = 0;
        clock_gettime(CLOCK_MONOTONIC, &start); // start the timeeer !

        for(unsigned long i = 0; i < NUMBER_RANDOM_ACCESSES; ++i){
            // i aber random zwischen 1 ..... NUMA_BUFFER_SIZE 

            unsigned long index = rand() % entries;
            sum += buffer[index];
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        uint64_t duration_ns =
            (end.tv_sec - start.tv_sec) * 1000000000UL +
            (end.tv_nsec - start.tv_nsec);

        measure_results[node] = duration_ns; //save it in the measure result !! as index node

        printf("Thread %lu: NUMA Node %u - total time = %lu ns, average = %lu ns\n",
               thread_num, node, duration_ns, duration_ns / NUMBER_RANDOM_ACCESSES);
    }
    
    //Release the next thread
    if(thread_num!=count_threads-1){
        pthread_mutex_unlock(core_release_mutex+thread_num+1);
    }
    
    return 0;
}

