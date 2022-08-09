#include "Mission.h"

Mission::Mission(int ed, int id, float tloc, int mdur, int sig)
{
	set_FD(ed);
	set_TLOC(tloc);
	set_ID(id);
    set_MDUR(mdur);
	set_SIG(sig);
	WD = 0;
	ED = -1; // I NEED -1 to refer to still watting mission
	CD = -1; //// I NEED -1 to refer to still watting mission
	pair = nullptr; // still in waiting
}
void Mission::set_pair(Rover*& r)
{
	pair = r;
}
void Mission::set_FD(int ed)
{
	if (ed > 0)// start simulation from Day 1;
	{
		FD = ed;
	}
	else
	{
		FD = 1; // worst case if not reed from input File
	}
}
void Mission::set_TLOC(float tloc)
{
	if (tloc > 0)
	{
		TLOC = tloc;
	}
	else
	{
		TLOC = 1; // worst case if not reed from input File
	}
}
void Mission::set_ID(int id)
{
	if (id > 0)
	{
		ID = id;
	}
	else
	{
		ID = 0; // worst case if not reed from input File
	}
}
void Mission::set_MDUR(int mdur)
{
	if (mdur > 0)
	{
		MDUR = mdur;
	}
	else
	{
		MDUR = 1; // worst case if not reed from input File
	}
}
void Mission::set_SIG(int sig)
{
	if (sig > 0)
	{
		SIG = sig;
	}
	else
	{
		SIG = 1; // worst case if not reed from input File
	}
}
void Mission::set_ED(int ed)
{
	if (ed > 0)
	{
		ED = ed;
	}
	else
	{
		ED = -1;// invalid value i need it to check if the Mission is still in Waiting List so it won't have Execution day ED
	}
}
void Mission::set_WD(int wd)
{
	if (wd > 0)
	{
		WD = wd;
	}
	else
	{
		WD = 0; 
	}
}
void Mission::set_CD(int cd)
{
	if (cd > 0)
	{
		CD = cd;
	}
	else
	{
		CD = -1; // invalid value i need it to check if the Mission is still in Waiting List so it won't have Completed day CD 
	}
}
int Mission::get_ID()
{
	return ID;
}
int Mission::get_FD()
{
	return FD;
}
int Mission::get_ED()
{
	return ED;
}
int Mission::get_WD()
{
	return WD;
}
int Mission::get_CD()
{
	return CD;
}
float Mission::get_TLOC()
{
	return TLOC;
}
int Mission::get_MDUR()
{
	return MDUR;
}
int Mission::get_SIG()
{
	return SIG;
}
Rover*& Mission::get_pair()
{
	return pair;
}