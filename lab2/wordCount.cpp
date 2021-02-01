//Chris Grimes
//CS 44001 Lab 2
//9/13/20
//wordCount.cpp

#include <iostream>
#include <string>
#include "wordCount.hpp"

WordOccurrence::WordOccurrence(const std::string& word, int num){//ctor to give a word an number of occurrances(times been encountered)
  word_=word;
  num_=num;
}

bool WordOccurrence::matchWord(const std::string& toTest){//checks to see if passed string has already been read
  if(this->word_.length()!=toTest.length()){//asserts length is ==
    return false;
  }
  if((this->word_=="") || (toTest=="")){//asserts the neither string is an empty string
    return false;
  }
  if((this->word_!="") && (toTest!="")){
    for(int i=0; i<this->word_.length();++i){//asserts we won't exceed the bounds of the strings
      if(this->word_[i]!=toTest[i]){//checks each char
	return false;
      }
    }
  }
  return true;
}

void WordOccurrence::increment(){
  (this->num_)++;
}

std::string WordOccurrence::getWord() const{
  return this->word_;
}

int WordOccurrence::getNum() const{
  return this->num_;
}

WordList::WordList(){//default ctor
  size_=0;
  wordArray_=nullptr;
}

WordList::WordList(const WordList& cpyList){//copy ctor
  size_=cpyList.size_;
  wordArray_=new WordOccurrence[size_];
  for(int i=0; i<size_; ++i){
    wordArray_[i]=cpyList.wordArray_[i];
  }
}

WordList::~WordList(){//destructor
  delete [] wordArray_;
}

WordList& WordList::operator=(const WordList& rhs){//overloaded assignment
  if(this != &rhs){
    delete [] wordArray_;
    size_=rhs.size_;
    wordArray_= new WordOccurrence[size_];
    for(int i=0; i<size_; ++i){
      wordArray_[i]=rhs.wordArray_[i];
    }
    return *this;
  }
  return *this;
}

bool equal(const WordList& lhList, const WordList& rhList){
  if(lhList.size_ != rhList.size_){//asserts strings are the same length
    return false;
  }
  else if(lhList.size_ == rhList.size_){
    for(int i=0; i<lhList.size_;++i){
      if(lhList.wordArray_[i].getWord() != rhList.wordArray_[i].getWord()){//asserts the contentss are ==
	return false;
      }
    }
  }
  return true;
}

void WordList::addWord(const std::string& toAdd){//checks to see if the passed string has been read, if so increments the counter, if not add to word list
  bool matchFound=false;
  for(int i=0; i< this->size_;++i){
    if(this->wordArray_[i].matchWord(toAdd)==true){
      this->wordArray_[i].increment();
      matchFound=true;
    }
  }
  if(matchFound==false){
    int oldSize= this->size_;
    oldSize++;
    WordList tmp;
    tmp.size_=oldSize;
    tmp.wordArray_=new WordOccurrence[oldSize];
    int index=0;
    if(this->size_ == 0)
      tmp.wordArray_[index]=WordOccurrence(toAdd,1);
    else{
      while(index< (oldSize-1)){
	tmp.wordArray_[index]=this->wordArray_[index];
	++index;
      }
      tmp.wordArray_[index]=WordOccurrence(toAdd, 1);
    }
    *(this)=tmp;
  }
}

void WordList::print(){
  WordList rtnVal=*(this);
  while((rtnVal.size_)>0){
    WordList ordered;
    int minOccurrence=1000;
    WordOccurrence tmp;
    int indexToRemove=0;
    //for(int z=0;z<rtnVal.size_;++z){std::cout<<rtnVal.wordArray_[z].getWord()<<" "<<rtnVal.wordArray_[z].getNum()<<" origianl this\n";}
    for(int a=0; a< (rtnVal.size_);++a){//finds the string with the least occurences 
      if((((rtnVal.wordArray_[a].getNum())< minOccurrence)||(rtnVal.wordArray_[a].getNum()==minOccurrence))&&(rtnVal.wordArray_[a].getNum()!=0)){
	minOccurrence=(rtnVal.wordArray_[a].getNum());
	tmp=(rtnVal.wordArray_[a]);
	indexToRemove=a;
      }
    }
    if(tmp.getNum()>0){
    std::cout<<tmp.getWord()<<" "<<tmp.getNum()<<"\n";//prints the info about the string that was found
    }
    ordered.size_=(rtnVal.size_)-1;
    ordered.wordArray_=new WordOccurrence[ordered.size_];
    
    for(int q=0; q<(rtnVal.size_-1);++q){//creates a new list without the printed string
      if(q < indexToRemove){
	ordered.wordArray_[q]=rtnVal.wordArray_[q];
      }
      else{
	ordered.wordArray_[q]=rtnVal.wordArray_[q+1];
      }
    }
    
    rtnVal=ordered;
  }
}

