#include "NPC.h"

    NPC::NPC(string npcName, string n, Object r, string d1, string d2, string d3)
	{
		name = npcName; //name of the NPC
		need = n; //Object the player needs to use on the NPC
		dialouge1 = d1; //Dialouge Before Needed Object Is used
		dialouge2 = d2; //Dialouge While Needed Object Is used
		dialouge3 = d3; //Dialouge After Needed Object Is used
		rewardName = r.name; //Name of the reward Object given to the player after the need object is used
		//Object reward2 = r;
		reward = r;
	}
    NPC::NPC()
	{

	}

	void NPC::talk()
	{
		if (complete) //Print dialouge 3 if the needed Object has been used
		{
			system("cls");
			std::cout << "\n[ " << name << " ]:" << endl;
			std::cout << dialouge3 << endl;
		}
		else //Print dialouge 1 if the needed Object has not been used
		{
			system("cls");
			std::cout << "\n[ " << name << " ]:" << endl;
			std::cout << dialouge1 << endl;
		}

	}

	void NPC::use() //Print dialouge 2 if the needed Object is being used 
	{
		//system("cls");
		std::cout << "\n[ " << name << " ]:" << endl;
		std::cout << dialouge2 << endl;
		complete = true;
	}
