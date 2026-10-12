#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

using namespace std;

int main()
{
  //spawn a child process
  int p = fork();
  if (p > 0)
  {
    cout << "Parent: Sleeping for 2 seconds" << endl;
    sleep (2);
    cout << "Parent: Done sleeping" << endl;
    wait (NULL) ;
  }
  else if (p == 0)
  {
    cout << "Child: Sleeping for 2 seconds" << endl;
    sleep (2);
    cout << "Child: Done sleeping" << endl;
  }
}
