// vector and list algorithms with objects in containers
// Chris Grimes
// 9/21/20

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;

  void addClass(string&);

  void printClass(Student) const;
  
  string print() const {return firstName_ + ' ' + lastName_;}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }

  
  
private:
   string firstName_;
   string lastName_;
  list<string> classes;
};

// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   vector <list<Student>> courseStudents; 

   for(int i=1; i < argc-1; ++i){
      list<Student> roster;
      readRoster(roster, argv[i]);  
      //cout << "\n\n" << argv[i] << "\n";  
      //printRoster(roster);
      courseStudents.push_back(move(roster)); 
   }


   /*// reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   cout << "\n\n dropouts \n"; printRoster(dropouts);
   */

   list<Student> allStudents;  // master list of students
 
   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(),lst);

   /*cout << "\n\n all students unsorted \n"; 
           printRoster(allStudents);
   */

   allStudents.sort(); // sorting master list
   //cout << "\n\n all students sorted \n"; printRoster(allStudents);

   allStudents.unique(); // eliminating duplicates
   //cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
   
   /*for (const auto& str : dropouts)  // removing individual dropouts
      allStudents.remove(str);
   cout << "\n\n all students, dropouts removed \n"; printRoster(allStudents);
   */

   for(list<Student>::iterator a= allStudents.begin(); a != allStudents.end(); ++a){
     for(int b=1; b< argc-1; ++b){
       ifstream course(argv[b]);
       string first, last;
       while(course >> first >> last){
	 if(a->print() == (first+ " " +last)){
	   string fname=argv[b];
	   fname=fname.substr(0, 3);
	   a->addClass(fname);
	 }
       }
     } 
   }
   
   printRoster(allStudents);
}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      roster.push_back(Student(first, last));
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
  cout<<"\n\nAll Students \nfirst name, last name: courses enrolled\n";
  for(const auto& student : roster){
      cout << student.print() << " :";
      student.printClass(student);
   }
}

void Student::printClass(Student toPrint)const{
    for(auto q=toPrint.classes.begin();q != toPrint.classes.end(); ++q){
      cout<<*q<<" ";
    }
    cout<<std::endl;
  }
  
void Student::addClass(string& toAdd){
  classes.push_back(toAdd);
}
