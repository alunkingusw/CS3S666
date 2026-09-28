#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(void)
{

  int p[2];

  if (pipe(p)<0) exit(1);

  pid_t x = fork();

  if (x == 0)
  {
    close(p[1]);
    char buffer[8];
    int n;

    while ((n = read(p[0], buffer, 8)) > 0)
    {
      cout << "You said: " << buffer << endl;
    }
    cout << "I'm the child" << endl;
    close(p[0]);
  }
  else
  {
    close(p[0]);

    write(p[1], "Hello 1", 8);
    write(p[1], "Hello 2", 8);
    write(p[1], "Hello 3", 8);

    close(p[1]);
    cout << "I'm the parent" << endl;
    wait(NULL);
  }

  return 0;
}
