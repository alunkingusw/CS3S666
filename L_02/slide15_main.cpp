#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t x = fork();

  if (x == 0)
  {
   execl("./LP", "LP", "I was the child", "Now I am    not", NULL);
   std::cout << "I'm child" << std::endl;
  }
  else
  {
    std::cout << "I'm parent." << std::endl;
  }

  int status;
  pid_t child = wait(&status);

  if (child == x)
  {
    std::cout << "My child has terminated" << std::endl;
    std::cout << "Val returned = " << WEXITSTATUS(status) << std::endl;
  }

  return 0;
}
