#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

int count = 0;
int array[10];
pthread_mutex_t mutex;

//Requires: nothing
//Effects: returns the number of ones
void* count1s(void* arr) {
    int index = *(int*)arr;

    for (int i = 0; i < 5; i++) {
        if (array[i + index] == 1) {
            pthread_mutex_lock(&mutex);
            count++;
            pthread_mutex_unlock(&mutex);
        }
    }
    printf("\nlocal number of ones: %d", count);
    free(arr);
}

int main(int argc) {

    for (int i = 0; i < 10; i++) {
        array[i] = rand() % 5;
    }
    printf("}\n");

    pthread_t th[2];
    int i;
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < 2; i++) {
        int* a = malloc(sizeof(int));
        *a = i * 5;
        pthread_create(&th[i], NULL, &count1s, a);

    }

    for (i = 0; i < 2; i++) {
        pthread_join(th[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}
