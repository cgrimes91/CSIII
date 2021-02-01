//Chris Grimes
//CS 44001
//Lab 10

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

class State;

class Process{
public:
  Process();

  Process* clone(){return new Process();}

  int getID(){return id;}
  std::string report();
  void admitted();
  void interrupt();
  void exit();
  void dispatch();
  void ioWait();
  void ioDone();

  void changeState(State* s){state_=s;}

private:
  State* state_;
  static int id_;
  int id=0;
};

int Process::id_=1;

class State{
public:
  virtual std::string report()=0;
  virtual void admitted(Process*){}
  virtual void interrupt(Process*){}
  virtual void exit(Process*){}
  virtual void dispatch(Process*){}
  virtual void ioWait(Process*){}
  virtual void ioDone(Process*){}

  void changeState(Process* p, State* s){p->changeState(s);}
};

class New: public State{
public:
  static State* instance(){
    static State* only1= new New;
    return only1;
  }
  std::string report()override{return "New";}
  virtual void admitted(Process*)override;
  virtual void interrupt(Process*)override;
  virtual void exit(Process*)override;
  virtual void dispatch(Process*)override;
  virtual void ioWait(Process*)override;
  virtual void ioDone(Process*)override;
};

class Ready: public State{
public:
  static State* instance(){
    static State* only1= new Ready;
    return only1;
  }
  std::string report()override{return "Ready";}
  virtual void admitted(Process*)override;
  virtual void interrupt(Process*)override;
  virtual void exit(Process*)override;
  virtual void dispatch(Process*)override;
  virtual void ioWait(Process*)override;
  virtual void ioDone(Process*)override;
};

class Waiting: public State{
public:
  static State* instance(){
    static State* only1= new Waiting;
    return only1;
  }
  std::string report()override{return "Waiting";}
  virtual void admitted(Process*)override;
  virtual void interrupt(Process*)override;
  virtual void exit(Process*)override;
  virtual void dispatch(Process*)override;
  virtual void ioWait(Process*)override;
  virtual void ioDone(Process*)override;
};
 
class Running: public State{
public:
  static State* instance(){
    static State* only1= new Running;
    return only1;
  }
  std::string report()override{return "Running";}
  virtual void admitted(Process*)override;
  virtual void interrupt(Process*)override;
  virtual void exit(Process*)override;
  virtual void dispatch(Process*)override;
  virtual void ioWait(Process*)override;
  virtual void ioDone(Process*)override;
};

class Terminated: public State{
public:
  static State* instance(){
    static State* only1= new Terminated;
    return only1;
  }
  std::string report()override{return "Terminated";}
  virtual void admitted(Process*)override;
  virtual void interrupt(Process*)override;
  virtual void exit(Process*)override;
  virtual void dispatch(Process*)override;
  virtual void ioWait(Process*)override;
  virtual void ioDone(Process*)override;
};
//new
void New::admitted(Process* p){
  changeState(p, Ready::instance());
}

void New::interrupt(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void New::exit(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void New::dispatch(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void New::ioWait(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void New::ioDone(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}
//ready
void Ready::admitted(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Ready::interrupt(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Ready::exit(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Ready::dispatch(Process* p){
  changeState(p, Running::instance());
}

void Ready::ioWait(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Ready::ioDone(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}
//waiting
void Waiting::admitted(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Waiting::interrupt(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Waiting::exit(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Waiting::dispatch(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Waiting::ioWait(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Waiting::ioDone(Process* p){
  changeState(p, Ready::instance());
}
//running
void Running::admitted(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Running::interrupt(Process* p){
  changeState(p, Ready::instance());
}

void Running::exit(Process* p){
  changeState(p, Terminated::instance());
}

void Running::dispatch(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Running::ioWait(Process* p){
  changeState(p, Waiting::instance());
}

void Running::ioDone(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}
//terminated
void Terminated::admitted(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Terminated::interrupt(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Terminated::exit(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Terminated::dispatch(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Terminated::ioWait(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

void Terminated::ioDone(Process* p){
  std::cout<<"Invalid Transition."<<std::endl;
}

Process::Process(){id_++; id=id_; state_=New::instance();}

void Process::admitted(){state_->admitted(this);}
void Process::interrupt(){state_->interrupt(this);}
void Process::exit(){state_->exit(this);}
void Process::dispatch(){state_->dispatch(this);}
void Process::ioWait(){state_->ioWait(this);}
void Process::ioDone(){state_->ioDone(this);}
std::string Process::report(){return state_->report();}

int main(){
  srand(time(NULL));
  int myRandExit=rand()%3;
  int myRandInterrupt=rand()%3;
  int myRandIOWait=rand()%3;
  Process first;

  std::vector <Process*> a;
  
  int i=0;
  while(i<4){
    a.push_back(first.clone());
    a[a.size()-1]->admitted();
    std::cout<<"Process "<<a[a.size()-1]->getID()<<" is "<<a[a.size()-1]->report()<<std::endl;
    ++i;
  }
  
  std::vector <Process*> ready;
  ready.push_back(a[0]);
  ready.push_back(a[1]);
  ready.push_back(a[2]);
  ready.push_back(a[3]);

  std::vector <Process*> running;
  std::vector <Process*> waiting;
  std::vector <Process*> terminated;

  
  while(terminated.size()<4){
    if(running.begin()==running.end()){
      if(ready.begin()!=ready.end()){
	Process* tmp=ready[0];
	running.push_back(tmp);
	std::cout<<"Process "<<running[0]->getID()<<" is dispatched"<<std::endl;
	running[0]->dispatch();
	auto it =ready.begin();
	ready.erase(it);
	std::cout<<"Process "<<running[0]->getID()<<" is "<<running[0]->report()<<std::endl;
      }
    }
    myRandIOWait=rand()%3;
    myRandInterrupt=rand()%3;
    myRandExit=rand()%3;
    if(myRandInterrupt==0){
      if(running.begin()!=running.end()){
      Process* tmp=running[0];
      std::cout<<"Process "<<running[0]->getID()<<" is interrupted"<<std::endl;
      tmp->interrupt();
      ready.push_back(tmp);
      auto it =running.begin();
      running.erase(it);
      std::cout<<"Process "<<ready[ready.size()-1]->getID()<<" is "<<ready[ready.size()-1]->report()<<std::endl;
    }
    }
    else if(myRandIOWait==1){
      if(running.begin()!=running.end()){
      Process* tmp=running[0];
      std::cout<<"Process "<<running[0]->getID()<<" is waiting on an I/O action"<<std::endl;
      tmp->ioWait();
      waiting.push_back(tmp);
      auto it= running.begin();
      running.erase(it);
      std::cout<<"Process "<<waiting[waiting.size()-1]->getID()<<" is "<<waiting[waiting.size()-1]->report()<<std::endl;
    }
    }
    else if(myRandExit==2){
      if(running.begin()!=running.end()){
      Process* tmp=running[0];
      std::cout<<"Process "<<running[0]->getID()<<" is finished"<<std::endl;
      tmp->exit();
      terminated.push_back(tmp);
      auto it=running.begin();
      running.erase(it);
      std::cout<<"Process "<<terminated[terminated.size()-1]->getID()<<" is "<<terminated[terminated.size()-1]->report()<<std::endl;
    }
    }
    if(waiting.begin()!=waiting.end()){
      int myRandIODone=rand()%3;
      if(myRandIODone==0){
	Process* tmp=waiting[0];
	tmp->ioDone();
	ready.push_back(tmp);
	auto it=waiting.begin();
	waiting.erase(it);
	std::cout<<"Process "<<ready[ready.size()-1]->getID()<<" is "<<ready[ready.size()-1]->report()<<std::endl;
      }
    }
  }
}
