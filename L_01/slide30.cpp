#include <iostream>
#include <unistd.h>

int main()
{
	pid_t x = fork();
	std::cout << "Returned val = " << x << std::endl;
	return 0;
}
