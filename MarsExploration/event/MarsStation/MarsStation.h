#pragma once


#include"..\UI\UI.h"
#include"..\ADT\LinkedQueue.h"
#include"..\ADT\LinkedQueue_pri.h"

#include"..\Events\Events.h"
#include"..\Events\CancelEvent.h"
#include"..\Events\FormulationEventh.h"
#include"..\Events\PromotEvent.h"
#include"..\Mission\Mission.h"
#include"..\Mission\Emergency_Mission.h"
#include"..\Mission\Mountainous_Missions.h"
#include"..\Mission\Polar_Missions.h"

using namespace std;

class MarsStation
{
protected:
	LinkedQueue<Events*> EventList;
	LinkedQueue<Mission*> CompleteMission;
	LinkedQueue<Mission*> Waiting_MM;
	LinkedQueue<Mission*> temp;
	LinkedQueue_pri<Mission*,float> temp_pri; 
	LinkedQueue_pri<Mission*, float> Waiting_PM_EM;
	LinkedQueue_pri<Mission*, float>inExecutionMission;
	LinkedQueue_pri<Rover*, float> EmegencyRover;
	LinkedQueue_pri<Rover*, float> MountainousRover;
	LinkedQueue_pri<Rover*, float> PolarRover;
	LinkedQueue_pri<Rover*, float>inExecutionRover;
	LinkedQueue_pri<Rover*, float>checkup;
	LinkedQueue<Rover*> tempRovers;
	UI obj;   // an obj used to print or read anything from the user through the console screen
	const string tap = "\t";
	int avgW, avgE,sumCD; 
	int promoted;
	int current_day;
	float avg_speed;
	int autop;
	int noM;
public:
	MarsStation();
	bool ReadFile();  // reading the input file and set the event list and rover lists
	void excecuting_program(int); // the function that execute the whole program 
	void program();
	void promote_mission(Mission*&,int); // this function is to promote a mission given the current day and include the mission in emergency waiting missions list
	void CreatFile(); // creating the output file and print all CM and all statistics needed
	Mission*& getMission(int); // searching for a mountainous waiting mission givin its id and return null if mission not found
	void enqueueE(Mission*&);  //  to enquque a new emergency mission in the emegency waiting mission list
	void enqueueM(Mission*&);
	void enqueueP(Mission*&);
	int getCurrentDay();  //  to get the current day
	void getWaitingMission(LinkedQueue<int>& WM);  // get the id of all waiting missions
	void getInExecuteMission(LinkedQueue<int>& EM); // get the id of all in-execution missions and the rover attached with the mission 
	void getAvailableRovers(LinkedQueue<int>& AR); // get the id of all available rover 
	void getInCheckupRovers(LinkedQueue<int>& CR); // get the id of all in checkup rovers
	void getCompletedMissions(LinkedQueue<int>& CM); // get the id of the completed missions in that day
	void AUTO_Promotion(); 
	void sortby_CD_ED(); // to sort completed mission list by ED after being sorted ny CD

	void enqueueAvilableRover(Rover*& ptr); // to enquque a new rover in waiting list depending on it's list
	void enqueueCheckRover(Rover*& ptr);    // to enquque a new rover in Check up  list depending on it's Piority
	void enqueueExecutionRover(Rover*& ptr1, Mission*& ptr2);    // to enquque a new rover in execution  list depending on it's Piority
	void MovingRoverFromCheckup();
	void MovingRoverFromExccution(Rover*& ptr);

	bool EndOfProgram();  /// to indecate the ending of my program 

	void set_number_mountainous(); // increase number of mountainous missions for each mountainous mission formulated
};



