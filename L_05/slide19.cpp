#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void *HelloWorld (void *data)
{
  int *num = (int) data;
  *num = 4;
  Sleep (2);
  cout << "Hello World from new thread number: " << *num << endl;
  return NULL;
}
int main()
{
  pthread_t thread;
  int num in = 5;
  int rc
  pthread_create (&thread, NULL, HelloWorld, (void *) &num_in);
  if (rc != 0)
  {
    cout << "Thread failed." << endl;
  }

  sleep (1);
  cout << "Hello World from main thread number: " << num in << endl;
  pthread_join (thread, NULL);
  return 0;
}