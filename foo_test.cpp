
#include "foo.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//stating test and outcome vectors
	data_t test[N];
	data_t outcome[N];


  int retval = 0;
  ofstream myfile;

  // Init test vector
  for (int i=0; i<N; i++)
  {
	  test[i] = (data_t)i; //user-data-type of i

  }
  //save the final results to the file
  myfile.open("result.dat");

  // Executing the DUT thrice
  for (int iter = 0; iter < 3; iter++)
  {
    // Execute DUT (input->vector in, output->vector out
    diamond(test, outcome);

    // Display the results
    for (int i=0; i<N; i++)
    {
    	cout<<"Series "<<iter;
    	cout<<" Outcome "<< (int)outcome[i]<<endl;
    	myfile<<(int)outcome[i]<<endl;
    }
    myfile.close();
  }

  // Compare the results file with the golden results
  retval = system("diff --brief -w result.dat result.golden.dat");
  if (retval != 0)
  {
    cout << "Test failed  !!!" << endl;
    retval = 1;
  }
  else
  {
    cout << "Test passed !" << endl;
  }

  // Return 0 if the test passed
  return retval;
}
