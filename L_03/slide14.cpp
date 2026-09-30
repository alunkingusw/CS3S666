#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
int main(void)
{
   close(0);
   cout << getpid() << endl;
   sleep(60);
   return(0);
}