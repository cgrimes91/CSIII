//Lab 8 Singleton Logger
//Chris Grimes
//10/26/20

#include "singletonHeader.hpp"
#include <iostream>

int main(){

  void logName();
  void logDate();
  
  Logger::instance();

  logName();
  
  logDate();

}

void logName(){
  std::cout<<"Please enter your name follwed by enter:";

  std::string fullName;
  
  std::cin>> fullName;

  std::cout<<"You entered: "<<fullName<<std::endl;

  Logger::instance().report(fullName);
  
}

void logDate(){
  std::cout<<"Please enter the date followed by an enter:";

  std::string Date;
  
  std::cin>>Date;

  std::cout<<"You entered: "<<Date<<std::endl;

  Logger::instance().report(Date);
  
}
