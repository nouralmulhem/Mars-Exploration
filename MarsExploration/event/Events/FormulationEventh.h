#pragma once
#ifndef _FORMULATION_EVENT_H
#define _FORMULATION_EVENT_H
#include"Events.h"

class FormulationEvent : public Events
{
private:
	char type;
	float tloc;
	int mdur;
	int sig;
public:
	FormulationEvent(MarsStation* M_ptr, char p, int ed, int id, float l, int m, int s);
	virtual void Execute(MarsStation* M_ptr);


};
#endif
