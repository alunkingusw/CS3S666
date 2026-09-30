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

int main(int argc, const char * argv[]){

    if(mknod("myPipe", S_IFIFO | 0644, 0) < 0)
        cout << "Pipe already created" << endl;

    cout << getpid() << endl;

    int fd = open("myPipe", O_RDONLY);

    cout << "File opened to read" << endl;

    char buffer[200];

    int num;
    
    while((num = read(fd, buffer,200)) > 0){
        buffer[num] = '\0';
        cout << buffer << " " << num << endl;
    }

    close(fd);
    
    cout << "Read end closed" <<endl;

    return(0);
}