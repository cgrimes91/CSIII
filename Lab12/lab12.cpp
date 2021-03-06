// lab 12
// Chris Grimes
// 11/30/20

#include <iostream>
#include <string>
#include <vector>

using std::cin; using std::cout; using std::endl;
using std::string; 
using std::vector;

class Person{ // component
public:
   Person(string firstName, Person *spouse, Person *father, Person *mother):
      firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
   const string & getFirstName(){return firstName_;}
   Person *getSpouse(){return spouse_;}
   void setSpouse(Person *spouse){spouse_=spouse;}
   Person *getFather(){return father_;}

  virtual void accept(class PersonVisitor *, std::string fisrtCanidate, std::string secondCanidate)=0;
  virtual std::string find(class PersonVisitor *, std::string fisrtCanidate, std::string secondCanidate)=0;//implemented to return strings of name of Person*
  virtual std::string name() const=0;//implemented to distinguish derived classes
   virtual ~Person(){}
private:
   const string firstName_;
   Person *spouse_;
   Person *father_;
   Person *mother_;
};

// leaf
// man has a last name 
class Man: public Person{
public:
   Man(string lastName, string firstName, Person *spouse, 
       Person *father, Person *mother): 
      lastName_(lastName), 
      Person(firstName, spouse, father, mother){}
   const string & getLastName(){return lastName_;}
  void accept(class PersonVisitor *visitor, std::string fisrtCanidate, std::string secondCanidate) override;
   std::string find(class PersonVisitor *, std::string fisrtCanidate, std::string secondCanidate)override;
  std::string name() const override{return "Man";}
private:
   const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public:
   Woman(vector<Person *> children, 
       string firstName, 
       Person *spouse, 
       Person *father, Person *mother): 
       children_(children),
       Person(firstName, spouse, father, mother){}
   const vector<Person *> & getChildren() {
      return children_;}
   void setChildren(const vector<Person *> &children){
      children_ = children;}
  void accept(class PersonVisitor *visitor, std::string fisrtCanidate, std::string secondCanidate) override;
  std::string find(class PersonVisitor *, std::string fisrtCanidate, std::string secondCanidate)override;
  std::string name() const override{return "Woman";}
private:
   vector<Person *> children_;
}; 

// abstract visitor
class PersonVisitor{
public:
   virtual void visit(Man*, std::string fisrtCanidate, std::string secondCanidate)=0;
   virtual void visit(Woman*, std::string fisrtCanidate, std::string secondCanidate)=0;
  virtual std::string print(Man*, std::string fisrtCanidate, std::string secondCanidate)=0;//the method that Person*->find() calls 
   virtual std::string print(Woman*, std::string fisrtCanidate, std::string secondCanidate)=0;//the method that Person*->find() calls
   virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor, std::string lhs, std::string rhs) {
  visitor->visit(this, lhs, rhs);
}

void Woman::accept(PersonVisitor *visitor, std::string lhs, std::string rhs){ 
   // children traversal through mother only
   // father's children are not traversed so as not 
   // to traverse them twice: for mother and father

  visitor->visit(this, lhs, rhs);
   // traversing descendants
   for(auto child : children_) 
     child->accept(visitor, lhs, rhs);
}
std::string Man::find(PersonVisitor *visitor, std::string lhs, std::string rhs) {
  return visitor->print(this, lhs, rhs);
}

std::string Woman::find(PersonVisitor *visitor, std::string lhs, std::string rhs){ 
   // children traversal through mother only
   // father's children are not traversed so as not 
   // to traverse them twice: for mother and father

  return visitor->print(this, lhs, rhs);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor{
public:
   void visit(Man *m, std::string lhs, std::string rhs) override {
      cout << m->getFirstName() << " " << 
	 m->getLastName() << endl;
   }
   void visit(Woman *w, std::string lhs, std::string rhs) override {
      cout << w->getFirstName() << " ";
      if (w->getSpouse() != nullptr)
	 cout << static_cast<Man *> (w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 cout << static_cast<Man *> (w->getFather())->getLastName();
      else
	 cout << "Doe";
      cout << endl;
   }
  std::string print(Man *m, std::string lhs, std::string rhs) override {
    return  m->getFirstName()+ " " +m->getLastName();
   }
  std::string print(Woman *w, std::string lhs, std::string rhs) override {
    std::string rtnval= w->getFirstName();
      if (w->getSpouse() != nullptr)
	 rtnval+=" "+ static_cast<Man *> (w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 rtnval+=" " +static_cast<Man *> (w->getFather())->getLastName();
      else
	 rtnval+=" Doe";
      return rtnval;      
   }
};

class ChildrenPrinter: public PersonVisitor{
public:
   void visit(Man *m, std::string lhs, std::string rhs) override {
      cout << m->getFirstName() << ": ";
      Woman *spouse = static_cast<Woman *>(m->getSpouse());
      if(spouse != nullptr)
	 printNames(spouse->getChildren());
      cout << endl;
   }
   void visit(Woman *w, std::string lhs, std::string rhs) override {
      cout << w->getFirstName() << ": ";
      printNames(w->getChildren());
      cout << endl;
   }
private:
   void printNames(const vector<Person *> &children){
      for(const auto c: children)
	 cout << c->getFirstName() << ", ";
   }
  std::string print(Man *m, std::string lhs, std::string rhs) override {
    return  m->getFirstName()+ " " +m->getLastName();
   }
  std::string print(Woman *w, std::string lhs, std::string rhs) override {
    std::string rtnval= w->getFirstName();
      if (w->getSpouse() != nullptr)
	 rtnval+=" "+ static_cast<Man *> (w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 rtnval+=" " +static_cast<Man *> (w->getFather())->getLastName();
      else
	 rtnval+=" Doe";
      return rtnval;
   }
};

class MaidenPrinter: public PersonVisitor{
public:
  void visit(Man *m, std::string lhs, std::string rhs) override {//returns string when man object is passed
     cout << "Instances of Man do not have maiden names, only Woman"<<std::endl;
   }
  void visit(Woman *w, std::string lhs, std::string rhs) override {//finds and returns fathers last name or "Doe" when woman is passed
      cout << w->getFirstName() << " ";
      if (w->getFather() != nullptr)
	 cout << static_cast<Man *> (w->getFather())->getLastName();
      else
	 cout << "Doe";
      cout << endl;
   }
  std::string print(Man *m, std::string lhs, std::string rhs) override {
    return  m->getFirstName()+ " " +m->getLastName();
   }
  std::string print(Woman *w, std::string lhs, std::string rhs) override {
    std::string rtnval= w->getFirstName();
      if (w->getSpouse() != nullptr)
	 rtnval+=" "+ static_cast<Man *> (w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 rtnval+=" " +static_cast<Man *> (w->getFather())->getLastName();
      else
	 rtnval+=" Doe";
      return rtnval;
   }
};

class MarriagePrinter: public PersonVisitor{
public:
  void visit(Man *m, std::string lhs, std::string rhs) override {//figures out if object is one of the two getting married, and checks to make sure marriage ia allowed
    std::string notMe="";
    if(m->getFirstName()+" "+m->getLastName()== lhs || m->getFirstName()+" "+m->getLastName() == rhs){//decide if m is getting married
      if(m->getFirstName()+" "+m->getLastName()== lhs)//decide on name of potiential spouse
	notMe=rhs;
      else
	notMe=lhs;
      Woman *spouse = static_cast<Woman *>(m->getSpouse());
      if(spouse != nullptr){//checks is already married
	cout<<"\nMan is married and cannot marry.\n";
	return;
      }
      if( lhs == rhs){//checks self-marriage
	cout<<"\nMan cannot marry himself.\n";
	return;
      }
      if(m->getFather()!=nullptr){//checks marriage with father
	NamePrinter *np= new NamePrinter;
	std::string tmp=m->getFather()->find(np,lhs,rhs);
	if(tmp==notMe){
	  cout<<"\nMan cannot marry his father.\n";
	  return;
	}
      }
      if(m->getFather()!=nullptr){
	if(m->getFather()->getFather()!=nullptr){
	  if(m->getFather()->getFather()->getSpouse()!=nullptr){//checks fathers siblings
	    Woman *gmother = static_cast<Woman *>(m->getFather()->getFather()->getSpouse());
	    std::vector<Person *> kids(gmother->getChildren());
	    for(int i =0; i<kids.size(); ++i){
	      NamePrinter *np= new NamePrinter;
	      std::string tmp=kids[i]->find(np,lhs,rhs);
	      if(tmp==notMe){
		cout<<"\nMan cannot marry his father's siblings.\n";
		return;
	      }
	    }
	  }
	}
      }
      if(m->getFather()!=nullptr){
	if(m->getFather()->getSpouse()!=nullptr){//checks marriage with mother
	  NamePrinter *np=new NamePrinter;
	  Woman *mother = static_cast<Woman *>(m->getFather()->getSpouse());
	  std::string tmp=mother->find(np,lhs,rhs);
	  if(tmp==notMe){
	    cout<<"\nMan cannot marry his mother.\n";
	    return;
	  }
	}
      }
      if(m->getFather()!=nullptr){
	if(m->getFather()->getSpouse()!=nullptr){
	  if(m->getFather()->getSpouse()->getFather()!=nullptr){//checks mothers siblings
	    if(m->getFather()->getSpouse()->getFather()->getSpouse()!=nullptr){
	      Woman *gmother = static_cast<Woman *>(m->getFather()->getSpouse()->getFather()->getSpouse());
	      std::vector<Person *> kids(gmother->getChildren());
	      for(int i =0; i<kids.size(); ++i){
		NamePrinter *np= new NamePrinter;
		std::string tmp=kids[i]->find(np,lhs,rhs);
		if(tmp==notMe){
		  cout<<"\nMan cannot marry his mother's siblings.\n";
		  return;
		}
	      }
	    }
	  }
	}
      }
      if(m->getFather()!=nullptr){
	if(m->getFather()->getSpouse()!=nullptr){//checks siblings
	  Woman *mother = static_cast<Woman *>(m->getFather()->getSpouse());
	  std::vector<Person *> kids(mother->getChildren());
	  for(int i =0; i<kids.size(); ++i){
	    NamePrinter *np= new NamePrinter;
	    std::string tmp=kids[i]->find(np,lhs,rhs);
	    if(tmp==notMe){
	      cout<<"\nMan cannot marry his siblings.\n";
	      return;
	    }
	  }
	}
      }
      std::cout<<"\nMan can marry.\n";
    }
  }
  
  void visit(Woman *w, std::string lhs, std::string rhs) override {//figures out if object is one of the two getting married, and checks to make sure marriage ia allowed
    NamePrinter *np=new NamePrinter;
    std::string wName=w->find(np,"","");
    if(wName==rhs || wName==lhs){//decide whether w is to be married
      std::string notMe="";
      if(wName==rhs)//decide on who w is
	notMe=lhs;
      else
	notMe=rhs;
      if(w->getSpouse() != nullptr){//checks marriage
	if(w->getFirstName()+" "+static_cast<Man *>(w->getSpouse())->getLastName()== lhs || w->getFirstName()+" "+static_cast<Man *>(w->getSpouse())->getLastName()== rhs){
	  cout<<"\nWoman is married and cannot marry.\n";
	  return;
	}
      }
      if(lhs == rhs){//checks self marriage
	cout<<"\nWoman cannot marry herself.\n";
	return;
      }
      if(w->getFather()!=nullptr){//checks father
	std::string tmp=w->getFather()->find(np,lhs,rhs);
	if(tmp==notMe){
	  cout<<"\nWoman cannot marry her father.\n";
	  return;
	}
      }
      if(w->getFather()!=nullptr){
	if(w->getFather()->getFather()!=nullptr){
	  if(w->getFather()->getFather()->getSpouse()!=nullptr){//checks fathers siblings
	    Woman *gmother = static_cast<Woman *>(w->getFather()->getFather()->getSpouse());
	    std::vector<Person *> kids(gmother->getChildren());
	    if(gmother->getChildren().size()>0){
	      for(int i =0; i<kids.size(); ++i){
		std::string tmp=kids[i]->find(np,lhs,rhs);
		if(tmp==notMe){
		  cout<<"\nWoman cannot marry her father's siblings.\n";
		  return;
		}
	      }
	    }
	  }
	}
      }
      if(w->getFather()!=nullptr){
	if(w->getFather()->getSpouse()!=nullptr){//checks mother
	  Woman *mother = static_cast<Woman *>(w->getFather()->getSpouse());
	  std::string tmp=mother->find(np,lhs,rhs);
	  if(tmp==notMe){
	    cout<<"\nWoman cannot marry her mother.\n";
	    return;
	  }
	}
      }
      if(w->getFather()!=nullptr){
	if(w->getFather()->getSpouse()!=nullptr){
	  if(w->getFather()->getSpouse()->getFather()!=nullptr){//checks mothers siblings
	    if(w->getFather()->getSpouse()->getFather()->getSpouse()!=nullptr){
	      Woman *gmother = static_cast<Woman *>(w->getFather()->getSpouse()->getFather()->getSpouse());
	      std::vector<Person *> kids(gmother->getChildren());
	      if(gmother->getChildren().size()<0){
		for(int i =0; i<kids.size(); ++i){
		  std::string tmp=kids[i]->find(np,lhs,rhs);
		  if(tmp==notMe){
		    cout<<"\nWoman cannot marry her mother's siblings.\n";
		    return;
		  }
		}
	      }
	    }
	  }
	}
      }
      if(w->getFather()!=nullptr){
	if(w->getFather()->getSpouse()!=nullptr){//checks siblings
	  Woman *mother = static_cast<Woman *>(w->getFather()->getSpouse());
	  std::vector<Person *> kids(mother->getChildren());
	  for(int i =0; i<kids.size(); ++i){
	    std::string tmp=kids[i]->find(np,lhs,rhs);
	    if(tmp==notMe){
	      cout<<"\nWoman cannot marry her siblings.\n";
	      return;
	    }
	  }
	}
      }
      if(w->getChildren().size()<0){//checks own kids
	std::vector<Person *> kids=w->getChildren();
	for(int i =0; i<kids.size();++i){
	  std::string tmp=kids[i]->find(np,lhs,rhs);
	  if(tmp == notMe){
	    cout<<"\nWoman cannot marry her kids.\n";
	    return;
	  }
	}
      }
      std::cout<<"\nWoman can marry\n";
    }
  }
  
  std::string print(Man *m, std::string lhs, std::string rhs) override {//the method that Person*->find() calls, returns a Person*'s name in string
    return  m->getFirstName()+ " " +m->getLastName();
   }
  
  std::string print(Woman *w, std::string lhs, std::string rhs) override {//the method that Person*->find() calls, returns a Person*'s name in string
    std::string rtnval= w->getFirstName();
      if (w->getSpouse() != nullptr)
	 rtnval+=" "+ static_cast<Man *> (w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 rtnval+=" " +static_cast<Man *> (w->getFather())->getLastName();
      else
	 rtnval+=" Doe";
      return rtnval;
   }
};

Person* getPerson(std::string input, Woman* root, std::string caller);//forward declaration

Person* getPerson(std::string input, Man* root, std::string caller){//used to find Person in tree from userInput
  NamePrinter *np= new NamePrinter;
  std::string tmp=root->find(np,"","");
  if(input==tmp)
    return root;
  if(root->getSpouse()!=nullptr){
    if(root->getSpouse()->find(np,"","")!=caller){
      Person* rtnval= getPerson(input, static_cast<Woman*>(root->getSpouse()), tmp);
      if(rtnval!=nullptr)
	return rtnval;
    }
  }
  return nullptr;
}

Person* getPerson(std::string input, Woman* root, std::string caller){//used to find Person in tree from userInput
  NamePrinter *np= new NamePrinter;
  std::string tmp= root->find(np,"","");
  if(input==tmp)
    return root;
  if(root->getSpouse()!=nullptr){
    if(root->getSpouse()->find(np,"","")!=caller){
      Person* rtnval=getPerson(input, static_cast<Man*>(root->getSpouse()),tmp);
      if(rtnval!=nullptr)
	return rtnval;
    }
  }
  if(root->getChildren().size()!=0){
    std::vector<Person*> kids=root->getChildren();
    for(auto child: kids){
      if(input==child->find(np,"","")){
	Person* rtnval= child;
	return rtnval;
      }
      else if(child->name()=="Woman"){
        Person* rtnval=getPerson(input, static_cast<Woman*>(child),tmp);
	if(rtnval!=nullptr)
	  return rtnval;
      }
      else{
	Person* rtnval=getPerson(input, static_cast<Man*>(child),tmp);
	if(rtnval!=nullptr)
	  return rtnval;
      }
    }
  }
    return nullptr;
}

//add before the last else
/*cout<<"\nWoman spouse check\n";
  if(root->getSpouse()!=nullptr){
    Person* rtnval= getPerson(input, static_cast<Man*>(root->getSpouse()));
    return rtnval;
    }*/

// demonstrating the operation
int main(){

   // setting up the genealogical tree      
   // the tree is as follows
   //    
   //
   //       James Smith  <--spouse-->   Mary 
   //	                                  |
   //	                                 children -------------------------
   //	                                  |              |                |
   //	                                  |              |                |
   //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
   //	                                  |
   //	                                 children------------
   //	                                  |                 |
   //                                     |                 |
   //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
   //	       |
   //	     children
   //	       |
   //          |
   //	     Susan


   // first generation
   Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
   Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
   ms->setSpouse(js); js->setSpouse(ms);

   // second generation
   Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
   Man *rs=new Man("Smith", "Robert", nullptr, js, ms);
   Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
   ps->setSpouse(wj); wj->setSpouse(ps);

   vector<Person *> marysKids  = {ps,
			          rs,
			          new Woman({}, "Linda", nullptr, js, ms)};
   ms->setChildren(marysKids);

   // third generation
   Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
   vector<Person *> patsKids   = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
   ps->setChildren(patsKids);

   Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);

   Woman *sj = new Woman({}, "Susan", nullptr, mj ,jj);
   vector<Person *> jensKids   = {sj}; 

   jj->setSpouse(mj); mj->setSpouse(jj);
   jj->setChildren(jensKids);

   std::string null="";

   // defining two visitors
   ChildrenPrinter *cp = new ChildrenPrinter;
   NamePrinter *np = new NamePrinter;
   MaidenPrinter *mp= new MaidenPrinter;
   MarriagePrinter *married= new MarriagePrinter;

   // executing the traversal with the composite
   // and the specific visitor

   cout << "\nNAME LIST\n";
   ms->accept(np, null, null);

   cout << endl << endl;

   cout << "CHILDREN LIST\n";
   ms->accept(cp, null ,null);

   cout << "\nJAMES' CHILDREN\n";
   js->accept(cp, null, null);

   //Lab 12 output starts
   cout<<"\nOutput for Lab 12:\n";

   cout<< "\nMaiden Names of Women Starting with Mary\n";
   ms->accept(mp, null, null);

   cout<<"\nPlease enter the name of the first canidate to be married: first name last name then enter\t";
   std::string firstCanidate;
   std::string last;
   cin>>firstCanidate;
   cin>>last;
   firstCanidate+=" "+last;
   cout<<"\nEntire Name of First Canidate \n"<<firstCanidate;

   cout<<"\nPlease enter the name of the second canidate to be married: first name last name then enter\t";
   std::string secondCanidate;
   cin>>secondCanidate;
   cin>>last;
   secondCanidate+=" "+last;
   cout<<"\nEntire Name of Second Canidate \n"<<secondCanidate;

   cout<<"\n\nFinding Input\n";
   Person* one=getPerson(firstCanidate, js,"");
   Person* two=getPerson(secondCanidate, js,"");
   if(one ==nullptr){//checks to make sure userString was a person in the tree
     cout<<"One is a nullptr, the name: "<<firstCanidate<<" is not presnt in this tree\n";
     exit(0);
   }
   if(two ==nullptr){
     cout<<"Two is a nullptr, the name: "<<secondCanidate<<" is not presnt in this tree\n";
     exit(0);
   }
      
   std::cout<<"\n\nTesting First\n";//checks the status of each person and if marriage is allowed
   one->accept(married, firstCanidate, secondCanidate);
   std::cout<<"\nTesting Second\n";
   two->accept(married, firstCanidate, secondCanidate);
}
