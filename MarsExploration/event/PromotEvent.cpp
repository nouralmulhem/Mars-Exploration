#include"Events/PromotEvent.h"
#include"MarsStation/MarsStation.h"
#include"Mission/Mission.h"
#include"Mission/Emergency_Mission.h"
#include"Mission/Mountainous_Missions.h"

PromotEvent::PromotEvent(MarsStation* M_ptr, int ed, int id) : Events(M_ptr, ed, id)
{ }

void PromotEvent::Execute(MarsStation* M_ptr)
{
	Mission* ptr = M_ptr->getMission(getID()); // get the pointer of the mission with the id attached with the event
	if (ptr)
	{
		Mountainous_Missions* ptrM = (Mountainous_Missions*)ptr;  // downcasting to access the functions in mountainous mission class
		ptrM->AutoP_WD(M_ptr->getCurrentDay()); // set the WD of mission
		Mission* ptr2 = new Emergency_Mission(getEventDay(), getID(), ptr->get_TLOC(), ptr->get_MDUR(), ptr->get_SIG(), ptr->get_WD());
		// creat a new emergency mission and enqueue it in the waiting emergency mission list
		M_ptr->enqueueE(ptr2);
	}
}