#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define length 10

int count = 0;
int rcount=0;//real count
int array[length];

int num_threads = 2;

 int count1s()
 {

 for (int i=0; i<length; i++)
 {
 if (array[i] == 1)
 {
 rcount++;
}
 }
 return rcount;
 }


void *count_ones(void *arg) {
 
    int i;
    for (i = 0; i < length; i++) {
        if (array[i] == 1) {
            count++;
        }
    }
    return NULL;
}


int main(int argc, char *argv[]) {
    int i;
    pthread_t tid;
    
    srand(time(NULL));
    for (i = 0; i < length; i++) {
        array[i] = rand() % 5;
    }


    for (i = 0; i < num_threads; i++) {
        pthread_create(&tid, NULL, count_ones, NULL);
    }


    pthread_join(tid, NULL);

    printf("Number of 1s: %d (should be %d) %s ) \n", count, rcount, count == rcount ? "correct" : "incorrect");

 
    return 0;
}
