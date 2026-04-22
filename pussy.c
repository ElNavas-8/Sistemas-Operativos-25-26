#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid;

void printids (const char *s){
    pid_t pid;
    pthread_t tid;
    pid=getpid();
    tid=pthread_self();
    printf("%s pid %u tid %u\n", s, (unsigned int)pid, (unsigned int)tid);
    return;
}

void* new_thread (void *arg){
    printids("New thread: ");
    return NULL;
}

int main (void){
    pthread_create(&ntid, NULL, &new_thread, NULL); // se crea el hilo, de ahi se le asigna una funcion, el hilo procedera a ejecutar la funcion
    printids("Hilo principal: ");
    pthread_join(ntid, NULL);
    return 0;
}