#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
int main(void)
{
    int x;
    int myPipes[2];
    if (pipe(myPipes) < 0) exit(1);
    x = fork();
    cout << getpid() << endl;
    cin >> x;
    return 0;
}