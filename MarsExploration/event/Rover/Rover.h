
using namespace std;


class Rover
{ 
  float RoverSpeed;  // Speed for each rover
  int RoverId; // Id for each rover
  int CUD; //Cheak up Duration(from input file )
  int NumOfMissions; // that is(from input file ) that help me know the allowable num of missions to each rover to do 
  int Mcount; // this counter to count N Missions for each Rover that Rover can make 
  char RoverType; // this Char to know the type of each Rover
  static int count;
  int checked; // it's to return the duration for each rover in check up list 
  
public:

	Rover(float S,int D,char B,int M);
	
	 ///// Setters & getter 
     void set_RoverSpeed(float S);
	 float get_RoverSpeed();
     void set_CUD(int D);
     int get_CUD();
	 void set_checkPriority(int);
	 //int get_checked();
	 // void set_RoverId(int id);
	 int get_RoverId();
	 void set_RoverType(char B);  
	 char get_RoverType();
	 void set_NumOfMissions(int M);
	 int get_NumOfMissions();
	 int get_Mcount();
	 int get_priority();

 void CountMissionsDone(); // this Fun to increament the <<Mcount>> when Rover move from avalible to executaion 
 void ZeroMcount();    // this fun make <<Mcount=0>> when Rover move from check up to Avaliable list
   
    ~ Rover();


};
