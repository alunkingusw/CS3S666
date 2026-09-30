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
    if(x==0){
        if(execl("./LP", "LP", NULL) < 0)
            cout << "Error" << endl;
    }

    string name;
    cout << "Enter something:";
    
    cin >> name;
    close(myPipes[0]);
    write(myPipes[1], name.c_str(), name.length());

    wait(NULL);
    return 0;
}