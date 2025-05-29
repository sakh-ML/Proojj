/* 
Dieses Programm demonstriert die parallele Ausführung von vier Threads
mit POSIX-Threads (pthread). Jeder Thread führt eine eigene Funktion aus,
die eine Anzahl von Iterationen durchläuft und dabei Ausgaben macht.
Das Programm zeigt grundlegendes Erstellen, Starten und Warten auf Threads.
*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void* func1(void* arg) {
  for(int i = 0; i < 100; i++) {
    printf("I'm func1, currently at iteration %d\n", i);
  }
  return NULL;
}

void* func2(void* arg) {
  for(int i = 0; i < 100; i++) {
    printf("I'm func2, currently at iteration %d\n", i);
  }
  return NULL;
}

void* func3(void* arg) {
  for(int i = 0; i < 1000; i++) {
    printf("I'm func3, currently at iteration %d\n", i);
  }
  return NULL;
}

void* func4(void* arg) {
  for(int i = 0; i < 100; i++) {
    printf("I'm func4, currently at iteration %d\n", i);
}
  return NULL;
}

int main() {

printf("Hello from main!! /n");
pthread_t thread1, thread2, thread3, thread4;
pthread_t array_thread[4];

pthread_create(&array_thread[0], NULL, func1, NULL);
pthread_create(&array_thread[1], NULL, func2, NULL);
pthread_create(&array_thread[2], NULL, func3, NULL);
pthread_create(&array_thread[3], NULL, func4, NULL);

pthread_join(array_thread[0],NULL);
pthread_join(array_thread[1],NULL);
pthread_join(array_thread[2],NULL);
pthread_join(array_thread[3],NULL);

pthread_exit(NULL);

  return 0;
}

