#include"Events/FormulationEventh.h"
#include"MarsStation/MarsStation.h"
//#include"MarsStation/MarsStation.h
#include"Mission/Emergency_Mission.h"
#include"Mission/Mountainous_Missions.h"
#include"Mission/Polar_Missions.h"
FormulationEvent::FormulationEvent(MarsStation* M_ptr, char p, int ed, int id, float l, int m, int s) : Events(M_ptr, ed, id)
{
	type = p;
	tloc = l;
	mdur = m;
	sig = s;
}
void FormulationEvent::Execute(MarsStation* M_ptr)
{
	Mission* ptr;
	int id = (this->getID());
	int ed = (this->getEventDay());

	if (type == 'E')
	{
		ptr = new Emergency_Mission(ed, id, tloc, mdur, sig);
		M_ptr->enqueueE(ptr);

	}

	if (type == 'M')
	{
		M_ptr->set_number_mountainous(); // increament number of mountainous missions by 1
		ptr = new Mountainous_Missions(ed, id, tloc, mdur, sig);
		M_ptr->enqueueM(ptr);
	}
	if (type == 'P')
	{
		ptr = new Polar_Missions(ed, id, tloc, mdur, sig);
		M_ptr->enqueueP(ptr);

	}

}