#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void *HelloWorld (void *)
{
  sleep (2);
  cout << "Hello World from new thread!" << endl;
  return NULL;
}

int main()
{
  pthread_t thread;
  int rc pthread_create (&thread, NULL, HelloWorld, NULL); 
  if (rc != 0)
  {
    cout << "Thread creation failed." << endl;
  }
  
  cout << "Hello World from main thread!" << endl;
  pthread_join (thread, NULL);
  return 0;
}