#pragma once
#ifndef _PROMOT_EVENT_H
#define _PROMOT_EVENT_H
#include"Events.h"
#include"..\Mission\Mission.h"
class  PromotEvent :public Events
{
public:
	PromotEvent(MarsStation* M_ptr, int ed, int id);
	virtual void Execute(MarsStation* M_ptr);
};
#endif