#include"Events/CancelEvent.h"
#include"MarsStation/MarsStation.h"
//#include"MarsStation/MarsStation.h
#include"Mission/Mountainous_Missions.h"

CancelEvent::CancelEvent(MarsStation* M_ptr, int ed,int id) : Events(M_ptr, ed, id)
{

}
void CancelEvent::Execute(MarsStation* M_ptr)
{
	Mission* ptr = M_ptr->getMission(getID()); // get the pointer of the mission with the id attached with the event
	if (ptr) // check if the mission was found and delete it
	{
		delete ptr;
		ptr = NULL;
	}
}
