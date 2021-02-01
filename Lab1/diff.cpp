// Lab 1 CS44001
// Chris Grimes
// 8/31/20

#include <iostream>
#include <fstream>
#include <string>

using std::cout; using std::endl; using std:: string;

int main( int argv, char* argc[]){
    if(argv !=3){
    
      cout<<"There are not exactly three arguments for main. Please try again with three arguments.\n";
	    exit(0);
    }
    
    else{
	
      string file1= argc[1];  //creates a string to save each file's name to
      string file2= argc[2];  
      std::ifstream input1(file1);  //begin reading files
      std::ifstream input2(file2);  
      int lineTracker=0;

      while(!input1.eof() || !input2.eof()){  //loops through lines until the file is read

	++lineTracker;

	string stringToTest1;  //strings to save the lines to be checked
	string stringToTest2;

	getline(input1, stringToTest1);  //assigns a line in file to the approiate string
	getline(input2, stringToTest2);

	int index=0;
	int differenceFound= 0; //flag to show no difference found

	while((stringToTest1[index]!=0 || stringToTest2[index]!=0) && (differenceFound==0)){  //loop to search both strings for differences

	  if(stringToTest1[index] != stringToTest2[index]){

	    differenceFound=1;
	    string stringToCout1= file1;  //strings to write output
	    string stringToCout2= file2;
	    string lineNum= std::to_string(lineTracker);  //turns lineTracker into a string for concatenation
	    stringToCout1+= ": " + lineNum + ":";
	    stringToCout2+= ": " + lineNum + ":";
	    int moddedIndex= index + (stringToCout1.size()); //adjusts the index for the filename and line number info
	    stringToCout1+= stringToTest1;
	    stringToCout2+= stringToTest2;
	    cout<< stringToCout1<< "\n" << stringToCout2<< "\n";  //cout a line from each file
	    for(int tmp=0; tmp< moddedIndex; ++tmp){  //loop for the (^) carrot to show first difference

	      cout<<" ";
	    }
	    cout<<"^\n";
	  }
	  else{

	    ++index;
	  }
	}
      }
      input1.close();
      input2.close();
    }
}
