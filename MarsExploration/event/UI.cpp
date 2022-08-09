#include"UI/UI.h"
#include"MarsStation/MarsStation.h"

UI::UI(MarsStation* ptr)
{
	M = ptr;
}

void UI::PrintMsg(string s) // prints any message for the user
{
	cout << s << endl;
}

string UI::ReadInput() // function that takes a string from user (file name)
{
	string y;
	cin >> y;
	return y;
}

int UI::Readint() // read the mode of running from the user
{
	int i;
	cin >> i;
	return i;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::InterMode()
{
	int c;
	c = _getch(); // get the char the user entered
	if (c == 13) // 13 means enter in ASCII code 
	{
		print_day();
		cout << "Enter any other key to skip day " << endl << endl;
	}
}

void UI::StepMode() 
{
	print_day();
	Sleep(1000); // stop programm for one sec and continue
}

void UI::SilentMode() 
{
	cout << "\n";
	PrintMsg("Silent Mode");
	PrintMsg("Simulation starts...");
	PrintMsg("Simulation Ends, Output File created");
	cout << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::select_mode() // print a message for the user to enter the mode 
{
	cout << "\nin which mode you want to print your output??" << endl;
	cout << "choose 1 to ptinr in interactive mode \n";
	cout << "choose 2 to print in step-by-step mode \n";
	cout << "choose 3 to print in silent mode \n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::print_day()
{
	LinkedQueue<int> dummy;
	cout << "Current Day:" << M->getCurrentDay()<<endl; /// print the current day
	M->getWaitingMission(dummy); // get the id of all waiting missions
	cout << dummy.getcount() - 3 << " Waiting Mission: ";
	print1(dummy);
	cout << endl << "-----------------------------------------------------" << endl;

	M->getInExecuteMission(dummy); // get the id of all in-execution missions and their rovers
	cout << (dummy.getcount() - 3) / 2 << " In-Execution Missions/Rovers: ";
	print2(dummy);
	cout << endl << "-----------------------------------------------------" << endl;

	M->getAvailableRovers(dummy); // get the id of all available rovers
	cout << dummy.getcount() - 3 << " Available Rovers: ";
	print1(dummy);
	cout << endl << "-----------------------------------------------------" << endl;

	M->getInCheckupRovers(dummy); // get the id of all in checkup rovers
	cout << dummy.getcount() - 3 << " In-Checkup Rovers: ";
	print1(dummy);
	cout << endl << "-----------------------------------------------------" << endl;

	M->getCompletedMissions(dummy); // get the id of the missions done in that day
	cout << dummy.getcount() - 3 << " Completed Missions: ";
	print1(dummy);
	cout << endl << "-----------------------------------------------------" << endl;

	// we subtract 3 of all count because every list contains -1 after each mission type (3 types)

}


void UI::print1(LinkedQueue<int> &dummy) // print a queue of int 
{
	int id;
	if (dummy.peek(id)) // list isnt empty
	{
		if (id != -1) // no emergency 
		{
			dummy.dequeue(id);
			cout << "[" << id;
			while (dummy.dequeue(id))
			{
				if (id != -1)
				{
					cout << "," << id;
				}
				else
				{
					cout << "] ";
					break;
				}
			}
			if (dummy.isEmpty()) cout << "] ";
		}
		else dummy.dequeue(id);
		if (dummy.isEmpty()) return; ///////
		dummy.peek(id);
		if (id != -1) // no polar
		{
			dummy.dequeue(id);
			cout << "(" << id;
			while (dummy.dequeue(id))
			{
				if (id != -1)
				{
					cout << "," << id;
				}
				else
				{
					cout << ") ";
					break;
				}
			}
			if (dummy.isEmpty()) cout << ") ";
		}
		else dummy.dequeue(id);
		if (dummy.isEmpty()) return;
		dummy.peek(id); // no mountainous
		if (id != -1)
		{
			dummy.dequeue(id);
			cout << "{" << id;
			while (dummy.dequeue(id))
			{
				if (id != -1)
				{
					cout << "," << id;
				}
				else
				{
					cout << "} ";
					break;
				}
			}
		}
		else dummy.dequeue(id);

	}
}


void UI::print2(LinkedQueue<int> &dummy) // a function to print the in execution missions and the attached rover 
{
	int id1,id2;
	if (dummy.peek(id1))
	{
		if (id1 != -1)
		{
			dummy.dequeue(id1);
			dummy.dequeue(id2);
			cout << "[" << id1 <<"/"<< id2;
			while (dummy.dequeue(id1))
			{
				if (id1 != -1)
				{
					dummy.dequeue(id2);
					cout << "," << id1 << "/" << id2;
				}
				else
				{
					cout << "] ";
					break;
				}
			}
			if (dummy.isEmpty()) cout << "] ";
		}
		else dummy.dequeue(id1);
		if (dummy.isEmpty()) return;
		dummy.peek(id1);
		if (id1 != -1)
		{
			dummy.dequeue(id1);
			dummy.dequeue(id2);
			cout << "(" << id1 << "/" << id2;
			while (dummy.dequeue(id1))
			{
				if (id1 != -1)
				{
					dummy.dequeue(id2);
					cout << "," << id1 << "/" << id2;
				}
				else
				{
					cout << ") ";
					break;
				}
			}
			if (dummy.isEmpty()) cout << ") ";
		}
		else dummy.dequeue(id1);
		if (dummy.isEmpty()) return;
		dummy.peek(id1);
		if (id1 != -1)
		{
			dummy.dequeue(id1);
			dummy.dequeue(id2);
			cout << "{" << id1 << "/" << id2;
			while (dummy.dequeue(id1))
			{
				if (id1 != -1)
				{
					dummy.dequeue(id2);
					cout << "," << id1 << "/" << id2;
				}
				else
				{
					cout << "} ";
					break;
				}
			}
			//if (dummy.isEmpty()) cout << "} ";
		}
		else dummy.dequeue(id1);

	}


}


