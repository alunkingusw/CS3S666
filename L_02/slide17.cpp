#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	const char *msg1 = "Hello";
	const char *msg2 = "It's me";

	int p[2];

	if (pipe(p) < 0) exit(1);

	pid_t x = fork();

	if (x == 0)
	{
		close(p[1]);
		char inbuff[8];
		read(p[0], inbuff, 6);
		std::cout << inbuff << endl;
		read(p[0], inbuff, 8);
		std::cout << inbuff << endl;
	}
	else
	{
		close(p[0]);
		write(p[1], msg1, 6);
		write(p[1], msg2, 8);
		wait(0);
	}

	return 0;
}
