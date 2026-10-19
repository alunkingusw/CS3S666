#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main(void)
{
  key_t key;
  int shmid;
  if ((key = ftok("newKey.txt", 'R')) == -1)
  {
    cout << "Unable to create a key" << endl;
  }
  shmid = shmget (key, 1024, 0644 | IPC_CREAT);
  if (shmid == -1)
  {
    cout << "Unable to get shared space." << endl;
    exit (1);
  }
  char *data = (char *)shmat(shmid, (void *)0, 0);
  cin >> data;
  return (0) ;
}
