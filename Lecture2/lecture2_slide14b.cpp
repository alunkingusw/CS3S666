#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, const char *argv[])
{
  cout << argv[1] << endl;
  cout << argv[2] << endl;
  sleep(5);
  return 0;
}
