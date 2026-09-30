#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
int main(void)
{
    int x;
    cout << getpid() << endl;
    cin >> x;
    return 0;
}