// figures: object adapter pattern
// Chris Grimes
// 11/9/20

#include <iostream>

using std::cout; using std::endl;

// base interface
class Figure {
public:
   virtual void draw()=0;
   virtual ~Figure(){}
  virtual void resize(int)=0;
};

// implementer/adaptee
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, int topLeftY, 
		   int bottomRightX, int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

  void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
    topLeftX_=topLeftX; topLeftY_=topLeftY; bottomRightX_=bottomRightX; bottomRightY_=bottomRightY;}
  int getTopLeftX(){return topLeftX_;}
  int getTopLeftY(){return topLeftY_;}
  int getBottomRightX(){return bottomRightX_;}
  int getBottomRightY(){return bottomRightY_;}
   void oldDraw(){
      for(int i=0; i < bottomRightY_; ++i){
         for(int j=0; j < bottomRightX_; ++j)
            if( i >= topLeftY_ && j>= topLeftX_ )
               cout << '*';
            else
               cout << ' ';
         cout << endl;
      }
   }
private: // defining top/left and bottom/right coordinates 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// adapter uses composition to delegate 
// requests to adaptee
class SquareAdapter: public Figure{
public:
   SquareAdapter(int size){
     adaptee_= new LegacyRectangle(0,0,size,size); size_=size;
   }
  int size(){return size_;}
  void resize(int newSize)override{adaptee_->move(0,0,newSize,newSize);}
   void draw() override {
      adaptee_->oldDraw();
   }
private:
   LegacyRectangle *adaptee_;
  int size_;
};


int main(){
   Figure *square = new SquareAdapter(10);
   square->draw();
   std::cout<<std::endl<<"Plaes enter the size of the square you'd like to declare: "<<std::endl;
   int usrSize;
   std::cin>>usrSize;
   Figure *usrShape= new SquareAdapter(usrSize);
   usrShape->draw();
   std::cout<<std::endl<<"Please enter the size you'd like to chage your square to: "<<std::endl;
   std::cin>>usrSize;
   usrShape->resize(usrSize);
   usrShape->draw();
}

