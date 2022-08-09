#pragma once
#ifndef _CANCEL_EVENT_H
#define _CANCEL_EVENT_H
#include"Events.h"

class  CancelEvent : public Events
{
public:
	CancelEvent(MarsStation* M_ptr, int ed, int id);
	virtual void Execute(MarsStation* M_ptr);
	
};
#endif