#pragma once
#ifndef _EVENTS_H
#define _EVENTS_H

using namespace std;
class MarsStation;
class Events
{
private:
	int EventDay;
	int ID;
protected:
	MarsStation* M;
public:
	Events (MarsStation* Mptr,int ed, int id );
	int getID();
	int getEventDay();
	virtual void Execute (MarsStation*) = 0; // pure virtual function that will be implemented in each derived class
};
#endif

