//tests hte implementation of wordCount.hpp
//Chris Grimes
//9/13/20

#include <iostream>
#include <string>
#include "wordCount.hpp"

using std::cout; using std::endl;

void testfunc(WordList);//function to test pass-by-value for WordList class

int main(){

  WordList w;

  //testing regular member functions
  w.addWord("one");
  w.addWord("one");//adds duplicate
  w.addWord("two");
  w.addWord("three");

  cout<< "word list is:\n";
  w.print();

  WordList w2, w3;

  w3=w2=w;//tests stacking of oveloaded assignment
  w3=w3;//test protection against self assignment

  if(equal(w2, w3))
    cout<<"w2 is equal to w3"<< endl;
  else
    cout<<"w2 is not equal to w3"<< endl;

  testfunc(w);//tests copy ctor
  w.print();//if destructor is implemented properly this should print properly after testfunc completets
  
}

//tests pass-by-value for object of class varArray
void testfunc(WordList myList){//copy ctor is invoked on myList
  cout<<"word list in testfunc: "<< endl;
  myList.print();
}//destructor is invoked when myList goes out of scope
