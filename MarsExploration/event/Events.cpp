#include"Events/Events.h"
#include"MarsStation/MarsStation.h"

Events::Events(MarsStation* Mptr, int ed, int id)
{
	M = Mptr;
	EventDay = ed;
	ID = id;
}
int Events::getID()
{
	return ID;
}
int Events::getEventDay()
{
	return EventDay;
}