#ifndef _MISSION_H
#define _MISSION_H

#include"..\Rover\Rover.h"

class Mission
{
private: 

	int FD; // Formulation Day: the day when the mission formulation is finalized and the mission becomes ready to be assigned to a rover. also it's name Event Day 
	int ED; //The days that a rover needs to complete a mission (the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station).
	int WD; //The number of days from the formulation of a mission until it is assigned to a rover.
	int CD; //The day at which the mission is successfully completed by the rover.(CD = FD + WD + ED)
	int ID; //ID is a unique sequence number that identifies each mission.
	int MDUR; //Mission Duration: The number of days needed to fulfill the mission requirements at the target location(assumed constant regardless of rover type).
	float TLOC; //Target Location: The distance (in kilometers) from the base station to the target location of the mission.
	int SIG; //Significance: A number representing the importance of the mission and how beneficial it is (the higher the number, the more significant it is).
	Rover* pair; //i need it to know Rover speed using it in calculting The days that a rover needs to complete a mission
public:
	Mission(int ed, int id, float tloc, int mdur, int sig);
	void  set_FD(int ed); // i need it for check Validity
	void  set_TLOC(float tloc);// i need it for check Validity
	void  set_ID(int id);// i need it for check Validity
	void  set_MDUR(int mdur);// i need it for check Validity
	void  set_SIG(int sig);// i need it for check Validity
	void  set_ED(int ed);// i need this function when Mission is Changed from Waiting to Execution in function In_Execuation_Event( int Current_Day) and also data member is inaccessible in inheirted classes
	void  set_WD(int wd);// i need this function when Mission is Changed from Waiting to Execution in function In_Execuation_Event( int Current_Day) and also data member is inaccessible in inheirted classes
	void  set_CD(int cd);// i need this function when Mission is Changed from Waiting to Execution in function In_Execuation_Event( int Current_Day) and also data member is inaccessible in inheirted classes
	void  set_pair(Rover*& r);// i need it becuase this data member is inaccessible in inheirted classes
	Rover*& get_pair(); //i need it in output Interactive mode to Know In_Execuation_Mission ID and it's Rover ID
	int  get_ID();// i need it in output file 
	int  get_FD();// i need it in output file
	int  get_ED();// i need it in output file
	int  get_WD();// i need it in output file
	int  get_CD();// i need it in output file
	float  get_TLOC();// i need it becuase this data member is inaccessible in inheirted classes
	int  get_MDUR();// i need it becuase this data member is inaccessible in inheirted classes
	int  get_SIG();// i need it becuase this data member is inaccessible in inheirted classes

	// //IMPORTANT........ // i need Func. Rover* set_Pair to set_Pair and Rover* get_Pair to get_Pair

	// i need this function when Mission is Changed from Waiting to Execution to calculate WD ,ED ,CD then return CD to enqueue this mission in Execution list with Priorty 1/CD.
	virtual int In_Execuation_Event(int Current_Day, Rover*& r) = 0;  //This Class is Abstract Class.
};

#endif