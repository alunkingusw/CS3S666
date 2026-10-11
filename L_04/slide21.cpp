#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h3>

int main(void)
{
  const int BUFFER_SIZE = 10;
  key_t key;
  int shmid;
  if ((key = frok(".", 'S')) = -1)
  {
    cout << "Unable to create a key" << endl;
  }
  // Create size of buffer + 1, (+1 for counter).
  shmid = shmget (key, (BUFFER_SIZE + 1) * sizeof(int), 0644 | IPC_CREAT);
  if (shmid == -1)
  {
    cout << "Unable to get shared space." << endl;
    exit(l);
  }
  int *data = (int *%)shmat(shmid, (void *)0, 0):
  int *counter = data; // First element as counter
  int *buffer = data + 1; // Second element as data
  int produced = 0;
  int pos = 0;
  while (true)
  {
    while (*counter == 0); // do nothing
    produced = buffer[pos]; // get something from buffer.
    pos = (pos + 1) % BUFFER_SIZE; // get next position.
    (*counter)--;// decrement counter.
    cout << produced << endl;
  }
  shmdt (data) ;
  return (0) ;
}
