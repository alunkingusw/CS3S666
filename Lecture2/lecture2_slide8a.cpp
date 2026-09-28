#include <iostream>
#include <unistd.h>

int main()
{
   pid_t x = fork();

   if (x == 0)
   {
      execl("./LittleProg", "LittleProg", NULL);
      std::cout << "I’m a child" << std::endl;
   }
   else
   {
      std::cout << "I’m a parent." << std::endl;
   }

   return 0;
}
