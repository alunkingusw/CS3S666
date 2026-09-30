#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
int main(void)
{
   close(0);
   cout << getpid() << endl;
   int myPipe[2];
   if (pipe(myPipe) < 0) exit(1);

   dup(myPipe[0]);
   
   sleep(60);
   return(0);
}