// CSIII Lab 11 main
// Chris Grimes
// 11/16/20

#include "drink.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void takeOrder(class Barista*);

int main(){

  srand(time(NULL));
  int myRand= rand()%3;

  Barista* b1=new JrBarista(new SrBarista(new Manager));

  takeOrder(b1);

  do{
  if(myRand==0 && b1->numCustomers()<5)
    takeOrder(b1);
  else
    b1->notifyCustomers(b1);
  myRand=rand()%3;
  }while(drinks_.size()!=0);
}

void takeOrder(Barista* b1){
  std::cout<<"Can I get your name?"<<std::endl;
  std::string customerName;
  std::cin>>customerName;

  Customer* c1=new Customer(customerName, b1);

  std::cout<<"Hello,"<<c1->getName()<<std::endl;
  
  char userIn;
  
  std::cout<<"Welcome to Cofee Shack, can I get you [l]arge, [m]edium, or [s]mall cofee?"<<std::endl;
  std::cin>>userIn;

  Drink* d;
  
  if(userIn== 'l'){
    d= new Drink(DrinkType::large, 3.00);
  }else if(userIn=='m'){
    d= new Drink(DrinkType::medium, 2.00);
  }else if(userIn=='s'){
    d= new Drink(DrinkType::small, 1.00);
  }

  do{
    
    std::cout<<"Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]othing?"<<std::endl;
    std::cin>>userIn;

    if(userIn=='s'){
      d= new Sprinkled(d);
    }else if(userIn=='c'){
      d= new Carameled(d);
    }else if(userIn=='f'){
      d= new Foamed(d);
    }else if(userIn=='i'){
      d= new Iced(d);
    }
  }while(userIn !='n');

  std::cout<<"We have your name as "<<c1->getName()<<std::endl;
  d->setPurchaser(c1->getName());

  b1->drinkDone(d);
  }
