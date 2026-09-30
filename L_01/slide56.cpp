int main()
{
     int *pNums = new int[5];
     pid_t x = fork();

     if (x == 0)
     {
         std::cout << "Child Memory Location: " << pNums << std::endl;
     }
     else
     {
         std::cout << "Parent Memory Location: " << pNums << std::endl;
     }

     delete[] pNums;
     return 0;
}
