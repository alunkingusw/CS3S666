#include <iostream>
#include <unistd.h>
#include <stdlib.h>


using namespace std;
int main(int argc, const char * argv[])
{
    int x = 3;
    
    char buffer[256];
    read(x, buffer, 256);
    
    cout << "I got: " << buffer << endl;
    
    exit(0);
}