// Games, Template Method example
// Chris Grimes
// 10/26/20

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }

      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

class Dice: public Game{
public:
  void initializeGame(){
    playersCount_=1;
  }

  void makeMove(int player){

    if(compAns==1 && compTurnTracker<3){
      int totalRolled=0;
      std::cout<<std::endl<<"Computer rolled: ";
      for(int i=0; i<5; ++i){
	const int dieRoll= (rand()% 6)+1;
	std::cout<<dieRoll<<" ";
	totalRolled+=dieRoll;
      }
      if(totalRolled> compHighScore)
	compHighScore=totalRolled;
      std::cout<<"= "<<totalRolled<<", "<<"Computer's highest score ="<<compHighScore<<std::endl;
      compAns= rand()%2;
      std::cout<<"Computer answer to roll again: 0 is no: "<<compAns<<std::endl;
      if(compAns==1)
	compTurnTracker++;
      else
	compTurnTracker=3;
    }
    
    
    if(movesCount_<maxMoves_){
      int totalRolled=0;
      std::cout<<std::endl<<"You rolled: ";
      for(int i=0; i<5; ++i){
	const int dieRoll= (rand()% 6)+1;
	std::cout<<dieRoll<<" ";
	totalRolled+=dieRoll;
      }
      if(totalRolled> plyrHighScore)
	plyrHighScore=totalRolled;
      std::cout<<"= "<<totalRolled<<", "<<"Your highest score ="<<plyrHighScore<<std::endl;
      char ans;
      if(movesCount_ <2){
      std::cout<<"Roll again? [y/n]";
      std::cin>>ans;
      }
      else
	ans='n';
      if(ans=='n')
	movesCount_=3;
      else
	++movesCount_;
    }

    if(movesCount_>=3 && compTurnTracker>=3)
      playerWon_=1;
  }

  void printWinner(){
    std::cout<<std::endl<<"The winner is: ";
     if(plyrHighScore> compHighScore)
       std::cout<<"Player"<<std::endl;
     else
      std::cout<<"Computer"<<std::endl;
    }
  
private:
  int movesCount_=0;
  int compHighScore=0;
  int plyrHighScore=0;
  const int maxMoves_=3;
  int compAns=1;
  int compTurnTracker=0;
};

int main() {
   srand(time(nullptr));

   Game* gp = nullptr;
 
      gp = new Dice;
      gp->playGame(); 
      delete gp;

}
