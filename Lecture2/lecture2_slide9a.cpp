#include <iostream>
#include <unistd.h>

int main()
{
  pid_t x = fork();

  if (x == 0)
  {
    execl("./LP", "LP", "I was the child", "Now I am not", NULL);
    std::cout << "I’m a child" << std::endl;
  }
  else
  {
    std::cout << "I’m a parent." << std::endl;
  }

  return 0;
}
