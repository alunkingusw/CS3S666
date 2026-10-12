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

int main() {
  // create shared memory region
  key_t segid = ftok(".", 'r');
  
  int shmid;
  shmid = shmget (segid, sizeof(sem_t), IPC_CREAT | 0660);
  void* sh_mem = shmat(shmid, (void*)0, 0);
  
  //create POSIX semaphore
  sem_t* sem = (sem_t*)sh_mem;
  int sts = sem_init (sem, true, 1);
  
  //spawn a child process
  int p = fork();
  if (p> 0) {
    sem_wait (sem);
    cout << "Parent: Sleeping for 2 seconds" << endl;
    sleep (2);
    cout << "Parent: Done sleeping" << endl;
    sem_post (sem) ;
    wait (NULL) ;
  }
  else if (p == 0) {
    sem_wait (sem);
    cout << "Child: Sleeping for 2 seconds" << endl;
    sleep (2);
    cout << "Child: Done sleeping" << endl;
    sem_post (sem);
  }
}

