#include <math.h>
  1 #include <stdio.h>
  2 #include <omp.h>
  3 
  4 #include "myFunction.h"
  5 
  6 int main(){
  7 
  8     int size = 1000000, i;
  9     double start = omp_get_wtime();
 10     double myArray[size];
 11     #pragma omp parallel for
 12         for(int i = 0; i < size; ++i){
 13             myArray[i] = myFunc(i);
 14         }
 15         printf("\n<<< Fertig >>>\n");
 16     
 17     
 18     double end = omp_get_wtime();
 19     printf("The time needen : %d ns", end - start);
 20         return 0;
 21 }

