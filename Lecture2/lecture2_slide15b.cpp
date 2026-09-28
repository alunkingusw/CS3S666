#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, const char *argv[])
{
  cout << argv[1] << endl;
  cout << argv[2] << endl;
  sleep(1);
  exit(5);
}
