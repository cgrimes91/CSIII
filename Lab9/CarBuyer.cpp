// needed for lab
// Chris Grimes
// 11/2/20

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot{
public:
   CarLot();
   Car *testDriveCar(int i){return car4sale_[i];}
  int nextCar(int &i, int id, std::string make, std::string choice, bool &purchase);
  int lotSize(){return sizeof(car4sale_)/sizeof(car4sale_[0]);}
   // if a car is bought, requests a new one
   Car *buyCar(int i){ 
      Car *bought = car4sale_[i];
      car4sale_[i] = 
        factories_[rand()%factories_.size()]->requestCar();
      return bought;
   }
		     
private:
   Car *car4sale_[10]; // single car for sale at the lot
   vector<CarFactory *> factories_;
};


CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale
   for(int i=0; i<lotSize(); ++i){
   car4sale_[i] = factories_[rand() % factories_.size()] -> requestCar();
   }
}

CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar(0); 

   cout << "Buyer " << id << endl;
   cout << "test driving " 
	<< toBuy->getMake() << " "
	<< toBuy->getModel()<<endl;
   int index=0;
   bool purchase=false;
   std::string make="Toyota";
   std::string models[]={"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
   std::string choice=models[rand() % 5];
   if (toBuy->getMake() == make && toBuy->getModel()==choice){
     cout<<"index "<<index<<endl << " love it! buying it!" << endl;
      carLotPtr -> buyCar(0);
      purchase = true;
   } else{
     while(purchase==false && index<carLotPtr->lotSize()-1){
       carLotPtr->nextCar(index, id, make, choice, purchase);
     }
   }
      
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar(0);
   
   cout << "Buyer " << id << endl;
   cout << "test driving "
	<< toBuy->getMake() << " "
        << toBuy->getModel()<<endl;
   int index=0;
   bool purchase= false;
   std::string make= "Ford";
   std::string models[]={"Focus", "Mustang", "Explorer", "F-150"};
   std::string choice=models[rand()% 4];
   if (toBuy->getMake() == make && toBuy->getModel() ==choice){
     cout<<"index "<<index<<endl << " love it! buying it!" << endl;
      carLotPtr -> buyCar(0);
      purchase=true;
   } else{
     while(purchase==false && index<carLotPtr->lotSize()-1){
       carLotPtr->nextCar(index, id, make, choice, purchase);
     }
   }
}


int CarLot::nextCar(int &i, int id, std::string make, std::string choice, bool &purchase){
  if(i<lotSize()-1){
    ++i;
    cout<<"index "<<i<<endl;
    Car *toBuy= carLotPtr-> testDriveCar(i);
    cout<<"Buyer "<< id<< endl;
    cout<<"test driving "<< toBuy->getMake()<< " "<< toBuy->getModel()<<endl;
    if(toBuy->getMake() == make && toBuy->getModel()==choice){
      cout<<" Love it! buying it!"<<endl;
      carLotPtr->buyCar(i);
      purchase = true;
      return i;
    }
    if(i==carLotPtr->lotSize()-1){
      cout<<"no more cars?!? i'm leaving"<<endl;
      return i;
    }
    else{
      cout<<"hated it let's try another"<<endl;
      return i;
    }
  }
  cout<<"no more cars?!? i'm leaving"<<endl;
  return i;
}

int main() {
   srand(time(nullptr));

   const int numBuyers=10;
   for(int i=0; i < numBuyers; ++i)
      if(rand()% 2 == 0)
	 toyotaLover(i);
      else
	 fordLover(i);
  
}
