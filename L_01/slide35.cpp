#include<iostream>
#include<unistd.h>

int main()
{
 int b = 5;
 pid_t x = fork();

 if (x == 0)
 {
    std::cout << "Child Process b = " << b << std::endl;
 }
 else
 {
    b = 10;
    std::cout << "Parent Process b = " << b << std::endl;
 }
 return 0;
}
