#pragma once
#include"Mission.h"
class Polar_Missions : public Mission
{
private:

public:
	Polar_Missions(int ed, int id, float tloc, int mdur, int sig);

	// i need this function when Mission is Changed from Waiting to Execution to calculate WD ,ED ,CD then return CD to enqueue this mission in Execution list with Priorty 1/CD. 
	int virtual In_Execuation_Event(int Current_Day, Rover*& r);
};

