#include "Emergency_Mission.h"
#include"Mission.h"
#include<cmath>

//int AutoP i need this especially in Emergency_Mission Because if The Mountainous_Missions Is Promoting to Emergency_Mission after (AutoP Days) then i will create new Emergency_Mission with (AutoP Days) as it's Waiting Days
Emergency_Mission::Emergency_Mission(int ed, int id, float tloc, int mdur, int sig , int AutoP ) :Mission(ed, id, tloc, mdur, sig)
{ //AutoP =0 if This Mission is Origin Emergency_Mission Waiting Days WD=0.
	Mission::set_WD(AutoP);
}

float Emergency_Mission::get_weighted_priority(float Av_Speed)
{ 
	// T is (the days it takes to reach the target location is(tloc) / (25 * speed) then fulfill mission requirements +MDUR ).then *2 to get back to the Base station
	float T = get_MDUR() + (2 * get_TLOC() / (25 * Av_Speed));
	return(100 * get_SIG() + 1000 / float(get_FD()) + 10000 / T);
}

int Emergency_Mission::In_Execuation_Event(int Current_Day, Rover*& r)
{
	set_pair(r); //now this mission is executing by Rover *r
	//now i now Acual Waiting Days
	set_WD(Current_Day - get_FD()  + get_WD()); //+ get_WD() i need this especially in Emergency_Mission Because if The Mountainous_Missions Is Promoting to Emergency_Mission after (AutoP Days) then i will create new Emergency_Mission with (AutoP Days) as it's Waiting Days
	// The days that a rover needs to complete a mission
	//(the days it takes to reach the target location is(tloc) / (25 * speed) then fulfill mission requirements +MDUR ).then *2 to get back to the Base station
	// i choose ceil() because  mdur + (2 * tloc) / (25 * speed)) will produce a floot Number But ED must be int then 5.0001 or 5.9999 will mean i'm in Day 6
	set_ED(ceil(get_MDUR() + (2 * get_TLOC()) / (25 * r->get_RoverSpeed())));//5.0001  -->6       //5.99999999 -->6  all in Day 6.

	set_CD(get_ED() + Current_Day); 
	return get_CD();
}
