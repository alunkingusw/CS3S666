//NOTE: this slide number is from where both week 3 PPTs have been merged

//ALSO NOTE - this file needs to be compiled into a Linux file system (~/) in wsl, not in Windows MNT using WSL
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(void){
    if(mknod("myPipe", S_IFIFO | 0644, 0) < 0)
        cout << "Pipe already created" << endl;
    
    cout << getpid() << endl;

    int fd = open("myPipe", O_WRONLY);
    cout << "File opened" << endl;
    
    return(0);
}