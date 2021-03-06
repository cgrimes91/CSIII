// drink class to be used in Coffee Shack lab
// Chris Grimes
// 11/16/20

#include <string>
#include <set>
#include <iostream>
#include <vector>

enum class DrinkType {small, medium, large};

class Drink{
public:
  Drink(DrinkType type=DrinkType::small,double  price=0):
                 type_(type), price_(price){}
  virtual double getPrice() const{return price_;}
  virtual std::string getName() const;
  void setPurchaser(const std::string& n){purchaser=n;}
  std::string getPurchaser(){return purchaser;}
private: 
  double price_;
  DrinkType type_;
  std::string purchaser;
};

std::vector <Drink *> drinks_;//vector to hold drink to be made/delivered

std::string Drink::getName() const{

  switch(type_){
  case DrinkType::small:
    return "small coffee";
    break;
  case DrinkType::medium:
    return "medium cofee";
    break;
  case DrinkType::large:
    return "large coffee";
    break;
  } 
}

class Sprinkled: public Drink{
public:
  Sprinkled(const Drink* base): base_(base){}
  double getPrice() const override{return base_->getPrice()+price_;}
  std::string getName()const override;
private:
  double price_=.50;
  const Drink* base_;
};

std::string Sprinkled::getName()const{
  if(base_->getName().find("with") == std::string::npos)
    return base_->getName()+" with sprinkles";
  else
    return base_->getName()+", sprinkles";
}

class Carameled: public Drink{
public:
  Carameled(const Drink* base): base_(base){}
  double getPrice() const override{return base_->getPrice()+price_;}
  std::string getName()const override;
private:
  double price_=.20;
  const Drink* base_;
};

std::string Carameled::getName()const{
  if(base_->getName().find("with") == std::string::npos)
    return base_->getName()+" with caramel";
  else
    return base_->getName()+", caramel";
}

class Foamed: public Drink{
public:
  Foamed(const Drink* base): base_(base){}
  double getPrice() const override{return base_->getPrice()+price_;}
  std::string getName()const override;
private:
  double price_=.40;
  const Drink* base_;
};

std::string Foamed::getName()const{
  if(base_->getName().find("with") == std::string::npos)
    return base_->getName()+" with foam";
  else
    return base_->getName()+", foam";
}

class Iced: public Drink{
public:
  Iced(const Drink* base): base_(base){}
  double getPrice() const override{return base_->getPrice()+price_;}
  std::string getName()const override;
private:
  double price_=.10;
  const Drink* base_;
};

std::string Iced::getName()const{
  if(base_->getName().find("with") == std::string::npos)
    return base_->getName()+" with ice";
  else
    return base_->getName()+", ice";
}

class Customer{
public:
  Customer(const std::string &,class Barista* s);
  void notify(Drink*);
  std::string getName(){return name_;}
private:
  std::string name_;
  Barista* b_;
};

class Barista{
public:
  Barista(Barista* successor=nullptr): successor_(successor){}
  void registerCustomer(Customer *c){views_.insert(c);}
  void deregisterCustomer(Customer* c){views_.erase(c);}
  virtual void notifyCustomers(Barista*)const;
  void drinkDone(Drink* d){drinks_.push_back(d);}
  int numCustomers(){return views_.size();}
  std::set <Customer *> getViews()const{return views_;}
protected:
  std::set <Customer *> views_;
  Barista* successor_;
};

Customer::Customer(const std::string& name,Barista* b){
  name_=name;
  b_=b;
  b->registerCustomer(this);
}

void Customer::notify(Drink* d){
  if(d->getPurchaser()==name_)
    std::cout<<"That's mine"<<std::endl;
}

class JrBarista: public Barista{
public:
  JrBarista(Barista* successor=nullptr):Barista(successor){}
  void notifyCustomers(Barista*)const override;
};

class SrBarista: public Barista{
public:
  SrBarista(Barista* successor=nullptr):Barista(successor){}
  void notifyCustomers(Barista*)const override;
};

class Manager: public Barista{
public:
  Manager(Barista* successor=nullptr):Barista(successor){}
  void notifyCustomers(Barista*)const override;
};

void Barista::notifyCustomers(Barista* b)const{
  if(successor_ != nullptr)
    successor_->notifyCustomers(b);
  else
    std::cout<<"Sorry, we can't honor that request."<<std::endl;
}

void JrBarista::notifyCustomers(Barista*b)const{
  Drink* orderUp=drinks_[0];
  if(orderUp->getName().find("with") == std::string::npos){
  std::cout<<orderUp->getPurchaser()<<", your "<<orderUp->getName()<<" is ready. It will be $"<<orderUp->getPrice()<<", please."<<std::endl;
  std::cout<<"Order was made by a Jr Barista"<<std::endl;
  for(auto e: views_){
    e->notify(orderUp);
  }
  drinks_.erase(drinks_.begin());
  }
  else
    successor_->notifyCustomers(b);
}

void SrBarista::notifyCustomers(Barista* b)const{
  Drink* orderUp=drinks_[0];
  if(orderUp->getName().find("foam") == std::string::npos){
  std::cout<<orderUp->getPurchaser()<<", your "<<orderUp->getName()<<" is ready. It will be $"<<orderUp->getPrice()<<", please."<<std::endl;
  std::cout<<"Order was made by a Sr Barista"<<std::endl;
  for(auto e: b->getViews()){
    e->notify(orderUp);
  }
  drinks_.erase(drinks_.begin());
  }
  else
    successor_->notifyCustomers(b);
}

void Manager::notifyCustomers(Barista* b)const{
  Drink* orderUp=drinks_[0];
  std::cout<<orderUp->getPurchaser()<<", your "<<orderUp->getName()<<" is ready. It will be $"<<orderUp->getPrice()<<", please."<<std::endl;
  std::cout<<"Order was made by the manager"<<std::endl;
  for(auto e: b->getViews()){
    e->notify(orderUp);
  }
  drinks_.erase(drinks_.begin());  
}
