#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int COUNTER A = 0;
int COUNTER_B = 0;
pthread_mutex_t_mutex = PTHREAD_MUTEX_INITIALIZER;
void *ChangeCounter (void *pVal)
{
  int myVal = *(int *) pVal;
  for (int i=0; i< 10000; i++)
  {
    pthread_mutex_lock (&mutex); COUNTER_A = myVal;
    sleep (0.001);
    COUNTER B = myVal;
    if (COUNTER_A != COUNTER_B)
      cout<<"Counter's different!" << endl;
    pthread_mutex_unlock (&mutex);
  }
  return NULL;
}

int main()
{
  pthread t threadA;
  pthread_t threadB;
  
  int valA = 0;
  int valB = 1;

  pthread_create (&threadA, NULL, ChangeCounter, (void*) &valA);
  pthread_create (&threadB, NULL, ChangeCounter, (void*) &valB);

  pthread_join (threadA, NULL);
  pthread_join (threadB, NULL);
  pthread_mutex_destroy(&mutex);

  return 0;
}