// sorting oranges
// converting vectors to multimaps
// Chris Grimes
// Lab 6 pt 1
// 10/5/2020


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

struct Fruit{
   Variety v;
   string color; // red, green or orange
};


int main(){
   srand(time(nullptr));
   vector <Fruit> tree(rand()%100+1);

   std::multimap <Variety, string> fruitMap;

   for(auto f=tree.begin(); f!=tree.end(); ++f){
      f->v = static_cast<Variety>(rand() % 3);
      f->color = colors[rand()%3];
   }

   for(auto f=tree.begin(); f!=tree.end(); ++f){//read from vector and insert into tree
     fruitMap.insert(std::pair <Variety, string> (f->v, f->color));
   }
   
   cout << "Colors of the oranges: ";//find the key(s) that are oranges and print their colors
   for(auto f=fruitMap.lower_bound(Variety::orange); f != fruitMap.upper_bound(Variety::orange); ++f){
     cout<<f->second<<", ";
   }
   cout<<endl<<endl;

   /*
   cout<<"Colors of the oranges: ";
   for(auto f=tree.begin(); f!=tree.end(); ++f)
      if(f->v == Variety::orange) cout << f->color << ", ";
      cout << endl;*/

}

