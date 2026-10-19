#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void *HelloWorld (void *data)
{
  sleep (2);
  int *num = (int *) data;
  cout << "Hello World from new thread number: " << *num << endl;
  return NULL;
}
int main()
{
  pthread_t thread;
  int num_in = 5;
  int rc = pthread_create (&thread, NULL, HelloWorld, (void *) &num_in);
  if (rc != 0)
  {
    cout << "Thread failed." << endl;
  }


  cout << "Hello World from main thread number: " << num_in << endl;
  pthread_join (thread, NULL);
  return 0;
}
  