#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct fill_cache
{
    long id;
    char *  characters;
};


long *array;
long length = 10000000;
int rcount = 0;
int ThreadsNumber = 8;
long *threadIndRes;

int count1s()
{

    for (int i = 0; i < length; i++)
    {
        if (array[i] == 1)
        {

            rcount++;
        }
    }
    return rcount;
}

void *threadCounting(void * my_struct)
{
    struct fill_cache *struct_ptr = (struct fill_cache*) my_struct;
    long nIterations = length / ThreadsNumber;
    long startID = (struct_ptr->id) * nIterations;
    printf("%d\n", startID);
    long endID = startID + nIterations;

    int temp = 0;
    int remaining_bytes=256000-((nIterations*8)+(3*sizeof(long))+sizeof(int));
    struct_ptr->characters=(char*)malloc(remaining_bytes*sizeof(char));

    if (length - endID < nIterations)
    {
        endID = length;
    }

    for (startID; startID < endID; startID++)
    {
        if (array[startID] == 1)
            temp++;
    }

    threadIndRes[struct_ptr->id] = temp;
    free(struct_ptr->characters);
}

int main()
{
    int count = 0;

    array = (long *)malloc(length * sizeof(long));
    threadIndRes = (long *)malloc(ThreadsNumber * sizeof(long));

    for (long i = 0; i < length; i++)
    {
        array[i] = rand() % 5 + 1;
    }

    rcount = count1s();
    

    pthread_t T[2]; //2=ThreadsNumber

    for (int i = 0; i < ThreadsNumber; i++)
    {
        
        struct fill_cache fill ;
        fill.id=i;
        pthread_create(&T[i], NULL, &threadCounting, &fill);
    }

    for (int i = 0; i < ThreadsNumber; i++)
    {
        pthread_join(T[i], NULL);
    }

    for (int j = 0; j < ThreadsNumber; j++)
    {
        count += threadIndRes[j];
    }

    printf("ThreadNumber: %d\n", ThreadsNumber);
    printf("Count 1's (sequ)= %d\n", rcount);
    printf("Count 1's (multiple threads): %d\n", count);
    free(array);
    free(threadIndRes);
    return 0;
}
