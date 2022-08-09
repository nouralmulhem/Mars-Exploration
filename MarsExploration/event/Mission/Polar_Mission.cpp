#include "Polar_Missions.h"
#include"Mission.h"
#include<cmath>
Polar_Missions::Polar_Missions(int ed, int id, float tloc, int mdur, int sig) :Mission(ed, id, tloc, mdur, sig)
{

}
int Polar_Missions::In_Execuation_Event(int Current_Day, Rover*& r)
{
	set_pair(r); //now this mission is executing by Rover *r
	//now i now Acual Waiting Days
	set_WD(Current_Day - get_FD());
	// The days that a rover needs to complete a mission
	//(the days it takes to reach the target location is(tloc) / (25 * speed) then fulfill mission requirements +MDUR ).then *2 to get back to the Base station
	// i choose ceil() because  mdur + (2 * tloc) / (25 * speed)) will produce a floot Number But ED must be int then 5.0001 or 5.9999 will mean i'm in Day 6
	set_ED(ceil(get_MDUR() + (2 * get_TLOC()) / (25 * r->get_RoverSpeed())));//5.0001  -->6       //5.99999999 -->6  all in Day 6.
	set_CD(get_ED() + get_FD() + get_WD());
	return get_CD();
}