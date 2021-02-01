//Chris Grimes
//CS 44001 Lab 2 Word Count
//9/13/20
//wordCount.hpp

#include <iostream>
#include <string>

#ifndef WORDCOUNT_HPP
#define WORDCOUNT_HPP



class WordOccurrence{
public:
  WordOccurrence(const std::string& word="", int num=0);//default ctor
  bool matchWord(const std::string&);//returns true if it matches a word stored
  void increment();// increments number of occurrences
  std::string getWord() const;
  int getNum() const;

private:
  std::string word_;
  int num_;
  
};

class WordList{
public:
  WordList();//default ctor
  WordList(const WordList&);//copy ctor
  ~WordList();//destructor
  WordList& operator=(const WordList&);//overloaded assignment

  friend bool equal(const WordList&, const WordList&);

  void addWord(const std::string&);
  void print();

private:
  WordOccurrence *wordArray_;//a dynamically allocated array of wordOccurrences  --  need not be sorted before print function
  int size_;
};

#endif
