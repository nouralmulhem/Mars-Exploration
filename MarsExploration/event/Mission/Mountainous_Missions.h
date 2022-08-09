#pragma once
#include"Mission.h"

class Mountainous_Missions : public Mission
{
private:
	 //IMPORTANT........//i need int count in the system instead of bool Auto_Promoted
	//bool Auto_Promoted; //it helps us get Percentage of automatically-promoted missions (relative to the total number of mountainous missions)
public:
	Mountainous_Missions(int ed, int id, float tloc, int mdur, int sig);
	
	//void Enable_Auto_Promoted(); // i need it when Automatic Promotion occurred and i will change Auto_Promoted to be True 
	//bool Is_Auto_Promoted(); //i need it when check Auto_Promoted from all Mountainous_Missions
	
	int virtual In_Execuation_Event(int Current_Day, Rover*& r); // i need this function when Mission is Changed from Waiting to Execution to calculate WD ,ED ,CD then return CD to enqueue this mission in Execution list with Priorty 1/CD.  
	void AutoP_WD(int Current_Day);
};

