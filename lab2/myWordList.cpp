//Chris Grimes
//CS 44001
//Lab 2
//.cpp to read from a file and implement functions

#include <iostream>
#include <fstream>
#include <string>
#include "wordCount.hpp"
#include <ctype.h>

using std::cout; using std::endl; using std::string;

int main(int argv, char* argc[]){
  if(argv !=2){

    cout<<"There are not exactly two arguments for main. Please try again with two arguments.\n";
    exit(0);
  }

  else{

    WordList dictionary;
    string newWord;
    string inFile= argc[1];//assigns the file to read to a string
    std::ifstream input(inFile);//begins reading file

    while(!input.eof()){

      string myString;
      while(input>>myString){//extracts word with no white space
	for(int i=0; i<myString.size();++i){
	  if(isalnum(myString[i])==0){
	    if(myString[i]==myString[0] || myString[i]==myString[myString.length()-1]){//added check
	      myString.erase(myString.begin()+i);
	      --i;
	    }
	  }
	}
      dictionary.addWord(myString);
      }
    } dictionary.print();
  
  }	  
}	
       
  

