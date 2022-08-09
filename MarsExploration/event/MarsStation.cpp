#include"MarsStation/MarsStation.h"

#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

MarsStation::MarsStation() : obj(this)
{
	avgW = avgE = sumCD = 0;
	promoted = 0;
	current_day = 0;
	avg_speed = 0;
	autop = 0;
	noM = 0;
}


bool MarsStation::ReadFile()
{
	//creating an obj of ifstream and reading the file name then opening it
	ifstream file;
	obj.PrintMsg("Please, Enter Input File Name.txt ");
	string filename = obj.ReadInput();
	file.open("_input/"+filename);

	int rovers, Mbe4check, dayscheck;
	float speed;
	string speed_str;
	string line, line2, line3, line4;
	Rover* ptr;

	if (file.is_open())
	{
		// getting the first four lines
		getline(file, line);
		getline(file, line2);
		getline(file, line3);
		getline(file, line4);

		// setting the number of missions done before a rover go to checkup
		Mbe4check = stoi(line4);
		line4 = line4.substr(to_string(Mbe4check).length() + 1, string::npos);

		// getting all information about mountainous rovers
		rovers = stoi(line);
		line = line.substr(to_string(rovers).length() + 1, string::npos);
		dayscheck = stoi(line4);
		line4 = line4.substr(to_string(dayscheck).length() + 1, string::npos);
		for (int i = 0; i < rovers; i++)
		{
			speed = stof(line);
			line = line.substr(line.find_first_of(' ') + 1, string::npos);
			avg_speed += speed;
			ptr = new Rover(speed, dayscheck, 'M', Mbe4check);
			MountainousRover.enqueue(ptr, speed);
		}

		// getting all information about polar rovers
		rovers = stoi(line2);
		line2 = line2.substr(to_string(rovers).length() + 1, string::npos);
		dayscheck = stoi(line4);
		line4 = line4.substr(to_string(dayscheck).length() + 1, string::npos);
		for (int i = 0; i < rovers; i++)
		{
			speed = stof(line2);
			line2 = line2.substr(line2.find_first_of(' ') +1 , string::npos);
			avg_speed += speed;
			ptr = new Rover(speed, dayscheck, 'P', Mbe4check);
			PolarRover.enqueue(ptr, speed);
		}

		// getting all information about emergency rovers
		rovers = stoi(line3);
		line3 = line3.substr(to_string(rovers).length() + 1, string::npos);
		dayscheck = stoi(line4);
		for (int i = 0; i < rovers; i++)
		{
			speed = stof(line3);
			line3 = line3.substr(line3.find_first_of(' ') + 1, string::npos);
			avg_speed += speed;
			ptr = new Rover(speed, dayscheck, 'E', Mbe4check);
			EmegencyRover.enqueue(ptr, speed);
		}
		int x = MountainousRover.getcount();
		int y = PolarRover.getcount();
		int z = EmegencyRover.getcount();
		avg_speed = (float)avg_speed / (x + y + z);

		// getting the days after which an mountainous waiting mission should be promoted
		getline(file, line);
		autop = stoi(line);

		// ignoring number of events
		getline(file, line);

		char typeE, typeM;
		int fd, id, mdur, sig;
		float tloc;
		string tloc_str;
		while (getline(file, line))
		{
			//reading each event line and creating an event of each type read and enqueue it in the event list
			Events* ptr = NULL;
			typeE = line[0]; // type of event
			line = line.substr(2, string::npos);
			if (typeE == 'F') // if the event was formulation event
			{
				typeM = line[0]; // type of mission 
				line = line.substr(2, string::npos);
				// data of the mission should be created
				fd = stoi(line);
				line = line.substr(to_string(fd).length() + 1, string::npos);
				id = stoi(line);
				line = line.substr(to_string(id).length() + 1, string::npos);
				tloc = stof(line);
				line = line.substr(line.find_first_of(' ') + 1, string::npos);
				mdur = stoi(line);
				line = line.substr(to_string(mdur).length() + 1, string::npos);
				sig = stoi(line);
				ptr = new FormulationEvent(this, typeM, fd, id, tloc, mdur, sig); // creating a new formulation event
				EventList.enqueue(ptr); // add it to event list
			}
			else if (typeE == 'X') // if event was cancellation event
			{
				// reading ID of mission should be cancelled and the day of cancellation
				fd = stoi(line);
				line = line.substr(to_string(fd).length() + 1, string::npos);
				id = stoi(line);
				ptr = new CancelEvent(this, fd, id); // creating a new cancellation event
				EventList.enqueue(ptr);// add it to event list

			}
			else if (typeE == 'P') // if event was promoting event
			{
				// reading ID of mission should be promoted and the day of promoting
				fd = stoi(line);
				line = line.substr(to_string(fd).length() + 1, string::npos);
				id = stoi(line);
				ptr = new PromotEvent(this, fd, id); // creating a new promoting event
				EventList.enqueue(ptr);// add it to event list
			}

		}
		file.close(); // closing the file
		return true;
	}
	else
	{
		obj.PrintMsg("can't open the file");
		return false;
	}

}


void MarsStation::program()
{
	bool test = ReadFile(); // read the input file from the user and print a message couldnt open the file if there is no file with this name
	if (!test) return; // if there is no file with this name return 
	obj.select_mode(); // ask the user to select mode of operation
	int mode = obj.Readint(); 
	obj.PrintMsg("\n");
	excecuting_program(mode); 
	CreatFile(); // creating the output file after executing the prgramm
	if (mode == 3) obj.SilentMode(); // if mode == 3 then print in silent mode
	
}


void MarsStation::excecuting_program(int mode)
{
	Events* ptr;
	Mission* ptr2;
	Rover* ptr3;
	Emergency_Mission* ptrE;
	Polar_Missions* ptrP;
	Mountainous_Missions* ptrM;
	while (!EndOfProgram())
	{
		current_day++;
		AUTO_Promotion(); // promot missions that reach its auto promotion day
		while (!EventList.isEmpty())
		{
			EventList.peek(ptr);
			if (ptr->getEventDay() == current_day) // execute all events that formulated in the current day
			{
				EventList.dequeue(ptr);
				ptr->Execute(this);
			}
			else break;
		}


		while (!inExecutionMission.isEmpty()) // move completed missions from in execution list to completed missions list
		{
			inExecutionMission.peek(ptr2);
			if (ptr2->get_CD() == current_day)
			{
				inExecutionMission.dequeue(ptr2);
				MovingRoverFromExccution(ptr2->get_pair());
				ptr2->get_pair() = nullptr;
				ptr2->set_pair(ptr2->get_pair());
				avgE += ptr2->get_ED();
				sumCD += ptr2->get_CD();
				CompleteMission.enqueue(ptr2);
			}
			else break;
		}
		MovingRoverFromCheckup(); // moving rovers from checkup to available again

		////////////////////////////////////////////////////////////////////////////////////////

		while (!Waiting_PM_EM.isEmpty()) // assign all emergency missions first then polar missions
		{
			Waiting_PM_EM.peek(ptr2);
			ptrE = dynamic_cast<Emergency_Mission*>(ptr2);
			ptrP = dynamic_cast<Polar_Missions*>(ptr2);
			if (ptrE)
			{
				if (!EmegencyRover.isEmpty() || !MountainousRover.isEmpty() || !PolarRover.isEmpty())
				{
					Waiting_PM_EM.dequeue(ptr2);
					if (!EmegencyRover.isEmpty()) // assign to emergency rover if exist
						EmegencyRover.dequeue(ptr3);
					else if (!MountainousRover.isEmpty()) // if not assign to mountainous if exist
						MountainousRover.dequeue(ptr3);
					else if (!PolarRover.isEmpty()) // if not assign to polar if exist
						PolarRover.dequeue(ptr3);
					ptr2->In_Execuation_Event(current_day, ptr3);
					ptr3->CountMissionsDone();
					avgW += ptr2->get_WD();
					inExecutionMission.enqueue(ptr2, (-1)* ptr2->get_CD());
					inExecutionRover.enqueue(ptr3, (-1)* ptr2->get_CD());
				}
				else break;
			}
			else if (ptrP)
			{
				if (!PolarRover.isEmpty()) // assign to polar rover only if exist
				{
					Waiting_PM_EM.dequeue(ptr2);
					PolarRover.dequeue(ptr3);
					ptr2->In_Execuation_Event(current_day, ptr3);
					ptr3->CountMissionsDone();
					avgW += ptr2->get_WD();
					inExecutionMission.enqueue(ptr2, (-1)* ptr2->get_CD());
					inExecutionRover.enqueue(ptr3, (-1)* ptr2->get_CD());
				}
				else break;
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////

		while (Waiting_MM.peek(ptr2)) // assign mountainous missions 
		{
			if (!EmegencyRover.isEmpty() || !MountainousRover.isEmpty())
			{
				Waiting_MM.dequeue(ptr2);
				if (!MountainousRover.isEmpty()) // assign to mountainous rover if exist 
					MountainousRover.dequeue(ptr3);
				else if (!EmegencyRover.isEmpty()) // if not assign the mission to emergency rover
					EmegencyRover.dequeue(ptr3);
				ptr2->In_Execuation_Event(current_day, ptr3);
				ptr3->CountMissionsDone();
				avgW += ptr2->get_WD();
				inExecutionMission.enqueue(ptr2, (-1)* ptr2->get_CD());
				inExecutionRover.enqueue(ptr3, (-1)* ptr2->get_CD());
			}
			else break;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mode == 1)
		{
			obj.InterMode();
		}
		else if (mode == 2)
		{
			obj.StepMode();
		}
		// print all information of the current day in the mode choosen
	}

}


void MarsStation::CreatFile()
{
	sortby_CD_ED();
	//creating an obj of ofstream and reading the file name then opening it
	ofstream out;
	obj.PrintMsg("\nPlease, Enter Output File Name");
	string filename = obj.ReadInput();
	filename += ".txt";
	out.open("_output/"+filename);

	if (out.is_open())
	{
		Mission* ptr;
		int noPolar = 0, noMountainous = 0, noEmegency = 0;
		int cd, id, fd, wd, ed;
		out << "CD	ID	FD	WD	ED" << endl; // printing the first line in input line
		int noMision = CompleteMission.getcount();
		while (!CompleteMission.isEmpty())
		{
			// check if the mission was emergency or mountainous or polar and increament its count
			CompleteMission.dequeue(ptr);
			Mountainous_Missions* Mptr = dynamic_cast<Mountainous_Missions*>(ptr);
			if (Mptr) noMountainous++;
			Polar_Missions* Pptr = dynamic_cast<Polar_Missions*>(ptr);
			if (Pptr) noPolar++;
			Emergency_Mission* Eptr = dynamic_cast<Emergency_Mission*>(ptr);
			if (Eptr) noEmegency++;

			// getting all data of the mission
			cd = ptr->get_CD();
			id = ptr->get_ID();
			fd = ptr->get_FD();
			wd = ptr->get_WD();
			ed = ptr->get_ED();

			out << cd << tap << id << tap << fd << tap << wd << tap << ed << endl;
		}

		// print all statistics needed
		out << "Missions : " << noMision << " [M: " << noMountainous << ", P: " << noPolar << ", E: " << noEmegency << "]" << endl;
		out << "Rovers : " << EmegencyRover.getcount() + PolarRover.getcount() + MountainousRover.getcount()
			<< " [M: " << MountainousRover.getcount() << ", P: " << PolarRover.getcount()
			<< ", E: " << EmegencyRover.getcount() << "]" << endl;
		out << "Avg Wait = " << (float)avgW / noMision << ", Avg Exec = " << (float)avgE / noMision << endl;
		if (noM == 0)
			out << "Auto-promoted: " << "there is no mountainous missions" << endl;
		else 
			out << "Auto-promoted: " << ((float)promoted / noM) * 100 << "%" << endl;
		out.close();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////


void MarsStation::promote_mission(Mission*& ptr, int current) // used to promote a function
{
	Mountainous_Missions* ptr2 = (Mountainous_Missions*)(ptr);
	ptr2->AutoP_WD(current); // set the days the mission waited as mountainous before beeing promoted
	// getting all data of mountainous mission
	//int fd = ptr->get_FD();
	int id = ptr->get_ID();
	float t = ptr->get_TLOC();
	int dur = ptr->get_MDUR();
	int s = ptr->get_SIG();
	int w = ptr->get_WD();
	delete ptr;
	ptr = new Emergency_Mission(current, id, t, dur, s, w); // creating new emergency mission with the same data
}


Mission*& MarsStation::getMission(int id) // find a mission using its id and return a pointer to it
{
	Mission* ptr;
	Mission* ptr2 = NULL;
	while (Waiting_MM.dequeue(ptr))
	{
		if (ptr->get_ID() == id)
			ptr2 = ptr;
		else
		{
			temp.enqueue(ptr);
		}
	}
	while (temp.dequeue(ptr))
	{
		Waiting_MM.enqueue(ptr);
	}
	return ptr2;
}


void MarsStation::enqueueE(Mission*& ptr) // enqueu an emergency mission in the waiting list
{
	Emergency_Mission* ptr2 = (Emergency_Mission*)ptr;
	Waiting_PM_EM.enqueue(ptr, ptr2->get_weighted_priority(avg_speed));
}


void MarsStation::enqueueM(Mission*& ptr) // enqueue a mountainous mission in the waiting list
{
	Waiting_MM.enqueue(ptr);
}


void MarsStation::enqueueP(Mission*& ptr) // enqueue a polar mission in the waiting list
{
	Waiting_PM_EM.enqueue(ptr, -1);
}


int MarsStation::getCurrentDay() // return the current day
{
	return current_day;
}



// this section of functions is to print each day on console screen

void MarsStation::getWaitingMission(LinkedQueue<int>& WM)
{
	Mission* ptr;
	Emergency_Mission* ptr2;
	Polar_Missions* ptr3;
	while (Waiting_PM_EM.peek(ptr))
	{
		ptr2 = dynamic_cast<Emergency_Mission*>(ptr);
		if (ptr2)
		{
			Waiting_PM_EM.dequeue(ptr);
			temp.enqueue(ptr);
			WM.enqueue(ptr->get_ID());
		}
		else break;
	}
	WM.enqueue(-1);
	while (Waiting_PM_EM.dequeue(ptr))
	{
		temp.enqueue(ptr);
		WM.enqueue(ptr->get_ID());
	}
	WM.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		ptr2 = dynamic_cast<Emergency_Mission*>(ptr);
		if (ptr2)
		{
			Waiting_PM_EM.enqueue(ptr, ptr2->get_weighted_priority(avg_speed));
		}
		else
		{
			Waiting_PM_EM.enqueue(ptr, -1);
		}
	}
	while (Waiting_MM.dequeue(ptr))
	{
		temp.enqueue(ptr);
		WM.enqueue(ptr->get_ID());
	}
	WM.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		Waiting_MM.enqueue(ptr);
	}
}


void MarsStation::getInExecuteMission(LinkedQueue<int>& EM)
{
	Mission* ptr;
	Emergency_Mission* ptr2;
	Polar_Missions* ptr3;
	Mountainous_Missions* ptr4;
	while (inExecutionMission.dequeue(ptr))
	{
		ptr2 = dynamic_cast<Emergency_Mission*>(ptr);
		if (ptr2)
		{
			EM.enqueue(ptr->get_ID());
			EM.enqueue(ptr->get_pair()->get_RoverId());
		}
		temp.enqueue(ptr);
	}
	EM.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		inExecutionMission.enqueue(ptr, (-1)*ptr->get_CD());
	}
	while (inExecutionMission.dequeue(ptr))
	{
		ptr3 = dynamic_cast<Polar_Missions*>(ptr);
		if (ptr3)
		{
			EM.enqueue(ptr->get_ID());
			EM.enqueue(ptr->get_pair()->get_RoverId());
		}
		temp.enqueue(ptr);
	}
	EM.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		inExecutionMission.enqueue(ptr, (-1)*ptr->get_CD());
	}
	while (inExecutionMission.dequeue(ptr))
	{
		ptr4 = dynamic_cast<Mountainous_Missions*>(ptr);
		if (ptr4)
		{
			EM.enqueue(ptr->get_ID());
			EM.enqueue(ptr->get_pair()->get_RoverId());
		}
		temp.enqueue(ptr);
	}
	EM.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		inExecutionMission.enqueue(ptr, (-1)*ptr->get_CD());
	}
}


void MarsStation::getAvailableRovers(LinkedQueue<int>& AR)
{
	Rover* ptr;
	while (EmegencyRover.dequeue(ptr))
	{
		AR.enqueue(ptr->get_RoverId());
		tempRovers.enqueue(ptr);
	}
	while (tempRovers.dequeue(ptr))
	{
		EmegencyRover.enqueue(ptr, ptr->get_RoverSpeed());
	}
	AR.enqueue(-1);
	while (PolarRover.dequeue(ptr))
	{
		AR.enqueue(ptr->get_RoverId());
		tempRovers.enqueue(ptr);
	}
	while (tempRovers.dequeue(ptr))
	{
		PolarRover.enqueue(ptr, ptr->get_RoverSpeed());
	}
	AR.enqueue(-1);
	while (MountainousRover.dequeue(ptr))
	{
		AR.enqueue(ptr->get_RoverId());
		tempRovers.enqueue(ptr);
	}
	while (tempRovers.dequeue(ptr))
	{
		MountainousRover.enqueue(ptr, ptr->get_RoverSpeed());
	}
	AR.enqueue(-1);
}


void MarsStation::getInCheckupRovers(LinkedQueue<int>& CR)
{
	Rover* ptr;
	while (checkup.dequeue(ptr))
	{
		if (ptr->get_RoverType() == 'E')
		{
			CR.enqueue(ptr->get_RoverId());
		}
		tempRovers.enqueue(ptr);
	}
	CR.enqueue(-1);
	while (tempRovers.dequeue(ptr))
	{
		checkup.enqueue(ptr, (-1)*ptr->get_priority());
	}
	while (checkup.dequeue(ptr))
	{
		if (ptr->get_RoverType() == 'P')
		{
			CR.enqueue(ptr->get_RoverId());
		}
		tempRovers.enqueue(ptr);
	}
	CR.enqueue(-1);
	while (tempRovers.dequeue(ptr))
	{
		checkup.enqueue(ptr, (-1)*ptr->get_priority());
	}
	while (checkup.dequeue(ptr))
	{
		if (ptr->get_RoverType() == 'M')
		{
			CR.enqueue(ptr->get_RoverId());
		}
		tempRovers.enqueue(ptr);
	}
	CR.enqueue(-1);
	while (tempRovers.dequeue(ptr))
	{
		checkup.enqueue(ptr, (-1)*ptr->get_priority());
	}
}


void MarsStation::getCompletedMissions(LinkedQueue<int>& CR)
{
	Mission* ptr;
	Emergency_Mission* ptr2;
	Polar_Missions* ptr3;
	Mountainous_Missions* ptr4;
	while (CompleteMission.dequeue(ptr))
	{
		ptr2 = dynamic_cast<Emergency_Mission*>(ptr);
		if (ptr2 && (ptr2->get_CD()==current_day))
		{
			CR.enqueue(ptr->get_ID());
		}
		temp.enqueue(ptr);
	}
	CR.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		CompleteMission.enqueue(ptr);
	}
	while (CompleteMission.dequeue(ptr))
	{
		ptr3 = dynamic_cast<Polar_Missions*>(ptr);
		if (ptr3 && (ptr3->get_CD() == current_day))
		{
			CR.enqueue(ptr->get_ID());
		}
		temp.enqueue(ptr);
	}
	CR.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		CompleteMission.enqueue(ptr);
	}
	while (CompleteMission.dequeue(ptr))
	{
		ptr4 = dynamic_cast<Mountainous_Missions*>(ptr);
		if (ptr4 && (ptr4->get_CD() == current_day))
		{
			CR.enqueue(ptr->get_ID());
		}
		temp.enqueue(ptr);
	}
	CR.enqueue(-1);
	while (temp.dequeue(ptr))
	{
		CompleteMission.enqueue(ptr);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void MarsStation::AUTO_Promotion()
{
	int x;
	Mission* ptr; // Dummy 
	Mission* temp;
	//bool Exit; // i need this variable to check if i reach end of List
	Waiting_MM.peek(ptr); // check 1 mission which has biggest WD

	while (!Waiting_MM.isEmpty()) //Auto promotion condition
	{
		x = current_day - ptr->get_FD();
		if (x < autop) break;
		promoted++;
		Waiting_MM.dequeue(ptr);
		
		promote_mission(ptr, current_day);
		enqueueE(ptr);
		//repeat again
		Waiting_MM.peek(ptr);

	}

}


void MarsStation::sortby_CD_ED()
{
	int ED, CD;
	Mission* ptr;
	Mission* tem;
	CompleteMission.dequeue(ptr); 
	while (!CompleteMission.isEmpty())
	{
		CD = ptr->get_CD();
		do
		{
			ED = ptr->get_ED();
			temp_pri.enqueue(ptr, -1 * ED);
			if (!CompleteMission.isEmpty()) CompleteMission.dequeue(ptr);
			else ptr = nullptr;
		} while (ptr && ptr->get_CD() == CD);

		while (!temp_pri.isEmpty())
		{
			temp_pri.dequeue(tem);
			temp.enqueue(tem);
		}
	}
	if(ptr) temp.enqueue(ptr); // last  Mission
	while (!temp.isEmpty())
	{
		temp.dequeue(tem);
		CompleteMission.enqueue(tem);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void MarsStation::enqueueAvilableRover(Rover*& ptr) // enqueu  Rover in the waiting list
{
	if (ptr->get_RoverType() == 'E')
	{
		EmegencyRover.enqueue(ptr, ptr->get_RoverSpeed());
	}
	else if (ptr->get_RoverType() == 'M')
	{
		MountainousRover.enqueue(ptr, ptr->get_RoverSpeed());
	}

	else if (ptr->get_RoverType() == 'P')
	{
		PolarRover.enqueue(ptr, ptr->get_RoverSpeed());
	}


}

void MarsStation::enqueueCheckRover(Rover*& ptr)
{
	ptr->set_checkPriority(current_day);
	checkup.enqueue(ptr, -1 * ptr->get_priority());
}

void MarsStation::enqueueExecutionRover(Rover*& ptr1, Mission*& ptr2)
{
	inExecutionRover.enqueue(ptr1, -1 * ptr2->get_CD());

}

void  MarsStation::MovingRoverFromCheckup()
{

	while (!checkup.isEmpty())
	{
		Rover* ptr;
		checkup.peek(ptr);
		int x = ptr->get_priority();
		if (x == current_day)
		{
			checkup.dequeue(ptr);
			enqueueAvilableRover(ptr);

			ptr->ZeroMcount(); // returning num of missions done to zero
		}
		else break;
	}

}

void  MarsStation::MovingRoverFromExccution(Rover*& ptr)
{
	if (ptr->get_Mcount() == ptr->get_NumOfMissions())
	{
		inExecutionRover.dequeue(ptr);
		enqueueCheckRover(ptr);
	}
	else
	{
		inExecutionRover.dequeue(ptr);
		enqueueAvilableRover(ptr);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

bool MarsStation::EndOfProgram() // checks if all lists are empty except the completed mission list and available rover list
{
	if (EventList.isEmpty() && Waiting_MM.isEmpty() && Waiting_PM_EM.isEmpty() && inExecutionMission.isEmpty())
	{
		if (inExecutionRover.isEmpty() && checkup.isEmpty())
			return true;
	}
	else return false;

}


void MarsStation::set_number_mountainous()
{
	noM++; // increament number of mountainous missions with every mission formulated
}