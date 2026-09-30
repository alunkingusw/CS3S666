int main()
{
     int *pNums = new int[5];
     for (int i = 0; i<5; i++) pNums[i] = 10;
       
     pid_t x = fork();


     if(x == 0)
     {
          sleep(1); //Ensure parent process modifies array first.

          for (int i = 0; i<5; i++)
               std::cout << "Child Process = " << pNums[i] << std::endl;
     }
     else
     {
	 //Change values stored in array.
          for (int i = 0; i<5; i++) pNums[i] = i;

          for (int i = 0; i<5; i++)
	      std::cout << "Parent Process = " << pNums[i] << std::endl;
     }

     delete[] pNums;
     return 0;
}
