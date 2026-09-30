#include <iostream>
#include <unistd.h>

int main()
{
	pid_t x = fork();

	if (x == 0)
	{
		std::cout << "I am a child" << std::endl;
	}
	else
	{
		std::cout << "I am a parent" << std::endl;
	}
	return 0;
}
