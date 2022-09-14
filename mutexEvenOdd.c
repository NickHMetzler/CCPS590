#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t count_mutex   = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var = PTHREAD_COND_INITIALIZER;

void *functionEven();
void *functionOdd();
int  count = 0;

#define COUNT_DONE  10

int main()
{
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &functionEven, NULL);
   pthread_create( &thread2, NULL, &functionOdd, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   printf("Final count: %d\n", count);

   exit(0);
}

// Write numbers 1-3 and 8-10 as permitted by functionOdd()
void *functionEven()
{
   for(;;)
   {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock( &count_mutex );

      // Wait while functionOdd() operates on count.
      // Mutex is unlocked, waits for condition_var to be signaled
      pthread_cond_wait( &condition_var, &count_mutex );
      count++;
      printf("Counter value functionEven: %d\n",count);

      pthread_mutex_unlock( &count_mutex );

      if(count >= COUNT_DONE){
        return(NULL);
      }
    }
}

// Write numbers 4-7
void *functionOdd()
{
  for(;;)
  {
    pthread_mutex_lock( &count_mutex );

    if(count % 2 != 0 || count >= COUNT_DONE) {
      // Condition of if statement has been met. 
      // Signal to free waiting thread by freeing the mutex.
      // Note: functionEven() is now permitted to modify "count".
      pthread_cond_signal( &condition_var );
    }
    else {
      count++;
      printf("Counter value functionOdd: %d\n",count);
    }

    pthread_mutex_unlock( &count_mutex );

    if (count >= COUNT_DONE){
      return(NULL);
    }
  }
}
