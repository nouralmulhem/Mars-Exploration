#pragma once
#include"Mission.h"
class Emergency_Mission : public Mission
{
private:

public:
	//int AutoP i need this especially in Emergency_Mission Because if The Mountainous_Missions Is Promoting to Emergency_Mission after (AutoP Days) then i will create new Emergency_Mission with (AutoP Days) as it's Waiting Days
	Emergency_Mission(int ed, int id, float tloc, int mdur, int sig , int AutoP = 0);
	
	// Weight Equation to Enqueue The Emergency_Mission in Priority Enqueue Emergency_List.
	float get_weighted_priority(float Av_Speed); //float Av_Speed is the Average Speed of Total Rovers in The System i need it Because Mission is still not assigned to rover yet.

	// i need this function when Mission is Changed from Waiting to Execution to calculate WD ,ED ,CD then return CD to enqueue this mission in Execution list with Priorty 1/CD. 
	int virtual In_Execuation_Event(int Current_Day, Rover*& r);
};

