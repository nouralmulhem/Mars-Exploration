#include"Rover.h"
#include<iostream>
using namespace std;

int Rover::count = 0; 


Rover ::Rover(float S,int D,char B,int M)
{
	set_RoverSpeed(S);
	count++;
	RoverId = count;
	set_CUD(D);
	set_RoverType(B);
	set_NumOfMissions(M);
	Mcount=0;
}

 
 void Rover::set_RoverSpeed(float S)
 {   
	 if(S>0)
	 RoverSpeed=S;
	 else RoverSpeed=-1;
 }

 float Rover::get_RoverSpeed(){return RoverSpeed; }

 void Rover::set_CUD(int D)
 {
	 if(D>0)
	 CUD=D;
	 else CUD=-1;
 }

 int Rover::get_CUD(){return CUD;}

 /*void Rover::set_RoverId(int id)
 {
	 if(id>0)
		 RoverId=id;
	 else RoverId=-1;
 }*/

 int Rover::get_RoverId(){return RoverId;}

 void Rover ::set_RoverType(char B)
 { 
    if(B=='E')
		RoverType='E';
	else if(B=='P')
      RoverType='P';
	   else RoverType='M';   

 }

 char Rover::get_RoverType(){return RoverType;}

 void Rover ::set_NumOfMissions(int M)
 {
      if (M>0)
	  NumOfMissions=M;
 }

 int Rover::get_NumOfMissions(){return NumOfMissions ;}

 int Rover ::get_Mcount(){return Mcount;}

 void Rover::set_checkPriority(int current_day) { if(current_day>0) checked = CUD + current_day; }

 //int Rover::get_checked() { return checked; }

 int Rover::get_priority()
 {
	 return checked;
 }

 void Rover::CountMissionsDone( )
 {
   Mcount++; 
 }

 void Rover::ZeroMcount( )
 {
        Mcount=0;
 }

 Rover::~ Rover(){}