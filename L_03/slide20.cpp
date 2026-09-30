//NOTE: this slide number is from where both week 3 PPTs have been merged
//heading of this slide is CREATING A PIPE

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
        cout << "Error creating pipe" << endl;
    return(0);
}