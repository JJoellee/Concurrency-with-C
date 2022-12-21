#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int ThreadCount=2;
long *array;
long size=1000;
long privcount = 0;
long priviterations = 0;

void *ThreadsExecution(void *rank)
{
   long my_rank = (long)rank;
   long iterations = 0;
   long count = 0;
   long perthread = size / ThreadCount;
   long start = my_rank * perthread;
   long end = start + perthread;
   if ((my_rank == ThreadCount - 1 && size % ThreadCount != 0))
   {
      for (long i = ((size / ThreadCount) * ThreadCount) - perthread; i < size; ++i)
      {
         if (array[i] == 1)
         {
            ++count;
         }
         ++iterations;
      }
   }

   else
   {
      for (long i = start; i < end; ++i)
      {
         if (array[i] == 1)
         {
            ++count;
         }
         ++iterations;
      }
   }
   privcount += count;
   priviterations += iterations;
}

void main()
{
   srand(time(0));
   for (int i = 0; i < 100; ++i) // using a for loop to run 100 times
   {
      array = (long *)malloc(sizeof(long) * size);
      for (long i = 0; i < size; ++i)
      {
         array[i] = rand() % 6;
      }
      pthread_t T[2]; //2= ThreaCount
      for (int i = 0; i < ThreadCount; ++i)
      {
         pthread_create(&T[i], NULL, &ThreadsExecution, (void *)i);
      }

      for (int i = 0; i < ThreadCount; ++i)
      {
         pthread_join(T[i], NULL);
      }
   }
  
   printf("count of 1's= %ld\n", privcount);
   printf("Iterations = %ld", priviterations);
}
