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
    cout << getpid() << endl;
    if(x==0){
        if(execl("./LP", "LP", NULL) < 0)
            cout << "Error" << endl;
    }
    
    cin >> x;
    return 0;
}