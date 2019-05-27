// 5COSC001W - CW - Joseph Calabro

//If you see errors everywhere - Right Click On "5COSC001W - CW - Joseph Calabro" in the Solution Explorer, select "Retarget Projects" and click "OK".
//After doing this the code will run, the errors will still be displayed though. To get rid of them fully, close and open visual studio.

using namespace std;

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <fstream>
#include <Windows.h> 

#include "Object.h"
#include "Player.h"
#include "NPC.h"
#include "MotionTableEntry.h"
#include "AdventureRoom.h"

#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)

string name = "", winOBJ = "", winMes = "", startMes = "";
int rmCount = 0; //number of rooms
int moves; //Number of moves it takes to win the game

//Commands
string CMD[12];

bool win = false; //has the player won (Are they holding the obj that makes them win)

string input;
std::vector<std::string> tokens; //Vector for storing each word in a string

enum concol // enumeration type
{
	black = 0, dark_blue = 1, dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};

//---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---//
//------FUNCTIONS------//

//Set Commands
void SetCMD()
{
	CMD[0] = "NORTH";
	CMD[1] = "SOUTH";
	CMD[2] = "EAST";
	CMD[3] = "WEST";
	CMD[4] = "INVENTORY";
	CMD[5] = "TAKE";
	CMD[6] = "DROP";
	CMD[7] = "LOOK";
	CMD[8] = "HELP";
	CMD[9] = "TALK";
	CMD[10] = "USE";
	CMD[11] = "OPEN";
}

//Set Colour
void setcolor(concol textcol, concol backcol)
{
	unsigned short wAttributes = (backcol << 4) | textcol;
	SetConsoleTextAttribute(std_con_out, wAttributes);
} 

//Splits String into Vector
void splitLine(string in) //Splits string into each word and places each work in a new vector position
{
	tokens.clear();

	std::string str(in);
	std::string buf;                 // Create a buffer string
	std::stringstream ss(str);       // Put string in a stream

	while (ss >> buf)
		tokens.push_back(buf);
}

//Read in Number of Rooms in the Text File
void CountRooms() //Opens the text file and counts the number of rooms
{
	string line = "";

	fstream stream;
	stream.open("Game1.txt");

	if (stream.is_open())
	{
		//cout << "File successfully open";
	}

	while (getline(stream, line))
	{
		if (line == "$$--NEW--ROOM--$$") // "$$--NEW--ROOM--$$" represents the start of a new room and so increments the room count
			rmCount++;
	}

	stream.close();
} 

//Read Data From Text File and Create Game Rooms
void ReadFromFile(AdventureRoom* room)
{
	string line = "";

	fstream stream;

	//Set up all the variables we need to read data into from the text file
	//once all the appropriate data is gathered we will create a new room object using it

	bool start = false, npc = false;
	int num = 0;
	string des[2];
	string npcName, npcNeed, npcd1, npcd2, npcd3, npcReward;

	NPC npcOBJ;

	list<Object> objList;
	list<MotionTableEntry> mtList;

	stream.open("Game1.txt");

	while (getline(stream, line)) //Goes through each line of the text file
	{
		splitLine(line); //Splits each line into words using the function above //tokens[0] represents the first word in a line, tokens[1] is the second... etc...

		if (line == "$$--NEW--ROOM--$$") //START NEW ROOM (Indicates the start of a new room)
		{
			start = true;
		}

		if (tokens.size() > 1) //If there are multiple words in a line and the first word is a key word, then we know the next is data we need
		{
			if (tokens[0] == "NUM") //GET ROOM NUMBER
			{
				num = stoi(tokens[1]);
			}
			else
			if (tokens[0] == "NAME") //GET ROOM NAME
			{
					name = tokens[1];
			}
			if (tokens[0] == "WIN") //GET Win Object
			{
				winOBJ = tokens[1];
			}
			else 
			if (tokens[0] == "OBJ") //GET OBJECTS
			{
				if (tokens.size() > 2)
				{
					Object obj = Object(tokens[1], tokens[2], tokens[3]); //Chest OBJ (Obj that needs a key to open its and contains an object inside //takes name, key and reward)
					objList.push_back(obj); //ADD TO LIST
				}
				else
				{
					Object obj = Object(tokens[1]); //Normal OBJ
					objList.push_back(obj); //ADD TO LIST
				}
			}
			else
			if (tokens[0] == "MT") //GET Motion Table OBJECTS
			{
				if (tokens.size() > 3) // We know it will take 3 arguments so must be a locked door 
				{
					MotionTableEntry MT = MotionTableEntry(tokens[1], stoi(tokens[2]), tokens[3]); //Locked Door(Direction, room it leads to, key needed)
					mtList.push_back(MT);
				}
				else
				{
					MotionTableEntry MT = MotionTableEntry(tokens[1], stoi(tokens[2]));
					mtList.push_back(MT);
				}
			}
        }

		//If a key word is the only word on a line then we know that the next few lines will contain the data we need

		if (line == "DES") //GET DESCRIPTION - the next two line have the rooms description so we add them to an array
		{
			getline(stream, des[0]);
			getline(stream, des[1]);
		}

		if (line == "WIN-MES") //WIN MESSAGE
		{
			getline(stream, winMes); //win message
		}

		if (line == "START-MES") //START MESSAGE
		{
			getline(stream, startMes); //start message
		}

		if (line == "NPC") //GET NPC
		{
			npc = true;

			getline(stream, npcName); //name
			getline(stream, npcNeed); //need - Item needed to get reward

			getline(stream, npcd1); //Talk1 - Dialouge before given Item
			getline(stream, npcd2); //Talk2 - Dialouge when item is given
			getline(stream, npcd3); //Talk3 - Dialouge after given Item

			getline(stream, npcReward); //reward - Item recieved after using the needed item on the NPC

			splitLine(npcReward); //split the reward to check whether it's a normal OBJ or Chest OBJ

			if (tokens.size() > 1)
			{
				Object reward = Object(tokens[0], tokens[1], tokens[2]); //Chest OBJ
				NPC npc = NPC(npcName, npcNeed, reward, npcd1, npcd2, npcd3); //Create NPC
				npcOBJ = npc;
			}
			else
			{
				Object reward = Object(tokens[0]); //Normal OBJ
				NPC npc = NPC(npcName, npcNeed, reward, npcd1, npcd2, npcd3); //Create NPC
				npcOBJ = npc;
			}
		}

		if (line == "//--END--ROOM--//") // We've reached the end of the room so we need to create the room and reset the values for the next room
		{
			if (npc)
			{
				room[num - 1] = AdventureRoom(num, name, des, objList, true, mtList, npcOBJ); //room with NPC
			}
			else
			{
				room[num - 1] = AdventureRoom(num, name, des, objList, true, mtList); //room without NPC
			}


			//Reset Variables
			start = false,
			npc = false;
			num = 0;
			name = "";
			des[0] = "";
			des[1] = "";
			npcName = "";
			npcNeed = "";
			npcd1 = "";
			npcd2 = "";
			npcd3 = "";
			npcReward = "";
			objList.clear();
			mtList.clear();
		}

		//Do everything again until there are no more lines
	}

	stream.close(); //close text file
}

//---//---//---//---//

//Checks if input direction is applicable to the current room and changes room 
int ChangeRoom(AdventureRoom* room, Player p, int currentRoom, string input) //Checks if player can go in the input direction and if they can returns the new room
{
	for (list<MotionTableEntry>::iterator i = room[currentRoom].motionTable.begin(); i != room[currentRoom].motionTable.end(); i++) //iterate through rooms motion table list
	{

		if (i->direction == input) //If they can go that way
		{
			if (i->locked == false) //rm isn't locked
			{
				currentRoom = i->room - 1; //change the room to the new one
				system("cls");

				return currentRoom;
			}
			else //Room is locked
			{
				for (int j = 0; j < 5; j++) //loop through inventory
				{
					if (i->key == p.inventory[j].name) //player has key
					{
						system("cls");
						i->locked = false;
						std::cout << "\nYou used the " << i->key << " to get through\n" << endl; // Used Key
						currentRoom = i->room - 1; //change the room to the new one

						return currentRoom;
					}

					if (j == 4) //Player doesn't have the key
					{
						system("cls");
						std::cout << "\nYou will probably need the " << i->key << " to go that way\n" << endl;
						
						return currentRoom;
					}
				}
			}
		}

		if ((i != room[currentRoom].motionTable.end()) && (next(i) == room[currentRoom].motionTable.end())) // the player can't go in that direction
		{
			system("cls");
			std::cout << "\nYou can't go that way!\n" << "" << endl;
			return currentRoom;
		}
	}
}

Player TakeObject(AdventureRoom* room, Player p, vector<string> tokens, int currentRoom)
{
	if (room[currentRoom].objectsLT.empty())
	{
		system("cls");
		setcolor(red, black);
		std::cout << "\nThere is nothing in this room worth taking!\n";

		return p;
	}
	else
	if (tokens.size() <= 1) //The player input "TAKE" but hasn't specified what to take.
	{
		system("cls");
		setcolor(red, black);
		std::cout << "\nYou reached out to take something but you didn't know what to take.\n";

		return p;
	}

	for (list<Object>::iterator i = room[currentRoom].objectsLT.begin(); i != room[currentRoom].objectsLT.end(); i++)
	{
		if (tokens.size() > 1)
		{
			if (tokens[1] == i->name) //Check if OBJ is able to be taken
			{
				system("cls");
				setcolor(magenta, black);
				if (p.takeObj(*i)) //take
					i = room[currentRoom].objectsLT.erase(i); //Remove from list || if return true

				return p;
			}

			if ((i != room[currentRoom].objectsLT.end()) && (next(i) == room[currentRoom].objectsLT.end())) //Can't be taken
			{
				system("cls");
				setcolor(red, black);
				std::cout << "\nYou can't take that!\n";
				return p;
			}
		}
	}
}

Player DropObject(AdventureRoom* room, Player p, vector<string> tokens, int currentRoom)
{
	if (tokens.size() > 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (tokens[1] == p.inventory[i].name)
			{
				system("cls");
				setcolor(magenta, black);
				room[currentRoom].objectsLT.insert(room[currentRoom].objectsLT.begin(), p.inventory[i]);
				p.drop(i);

				return p;
			}

			if (i == 4)
			{
				system("cls");
				setcolor(red, black);
				std::cout << "\nYou don't have an object with that name.\n";
				return p;
			}
		}
	}
	else
	{
		system("cls");
		setcolor(red, black);
		std::cout << "\nYou want to drop somthing but you don't know what.\n";
		return p;
	}
}

void Look(AdventureRoom* room, int currentRoom)
{
	if (room[currentRoom].objectsLT.empty())
	{
		system("cls");
		setcolor(red, black);
		std::cout << "\nYou searched the area but you found nothing!\n";
	}
	else
	{
		system("cls");
		setcolor(yellow, black);
		std::cout << "\nYou searched the area and you can see:\n";

		setcolor(magenta, black);
		for (list<Object>::iterator i = room[currentRoom].objectsLT.begin(); i != room[currentRoom].objectsLT.end(); i++)
		{

			std::cout << "\n//--->> " << i->name << "\n";
		}
	}
}

void Help()
{
	setcolor(white, black);
	system("cls");
	std::cout << "\nUse the commands NORTH, SOUTH, EAST & WEST to move from room to room.\n";
	std::cout << "\nUse the INVENTORY command to check your inventory.\n";
	std::cout << "\nUse the TAKE command with an object name to add it to your inventory.\n";
	std::cout << "\nUse the DROP command with an object to drop it.\n";
	std::cout << "\nUse the LOOK command to look around the room for objects.\n";
	std::cout << "\nUse the TALK command to talk to NPCs.\n";
	std::cout << "\nUse the USE command with an object to use it with something or someone.\n";
	std::cout << "\nUse the QUIT command to exit the game\n";
}

void Talk(AdventureRoom* room, int currentRoom)
{
	if (room[currentRoom].isNPC)
	{
		setcolor(green, black);
		room[currentRoom].npc.talk();
	}
	else
	{
		system("cls");
		setcolor(red, black);
		std::cout << "\nThere is no one here to talk to!\n";
	}
}

Player UseObject(AdventureRoom* room, Player p, vector<string> tokens, int currentRoom)
{
	if (tokens.size() > 1) //Did the player specify something to use
	{
		if (room[currentRoom].isNPC) //Is there an NPC in the room
		{
			if (tokens[1] == room[currentRoom].npc.need) //Is the player using the item needed by the NPC
			{
				for (int i = 0; i < 5; i++) //Loop through inventory
				{
					if (tokens[1] == p.inventory[i].name) //They have the item
					{
						system("cls");
						setcolor(magenta, black);
						p.use(i); //Use item
						setcolor(green, black);
						room[currentRoom].npc.use(); //NPC talk
						setcolor(magenta, black);
						p.takeObj(room[currentRoom].npc.reward); //Take Reward

						return p;
					}

					if (i == 4) //They don't have the item
					{
						system("cls");
						setcolor(red, black);
						std::cout << "\nYou don't have an object with that name.\n";
						return p;
					}
				}
			}
			else
			{
				system("cls");
				setcolor(red, black);
				std::cout << "\nYou can't do that!\n";
				return p;
			}
		}
		else
		{
			system("cls");
			setcolor(red, black);
			std::cout << "\nYou can't do that!\n";
			return p;
		}
	}
	else
	{
		system("cls");
		setcolor(red, black);
		std::cout << "\nYou can't do that!\n";
		return p;
	}
}

Player OpenObject(AdventureRoom* room, Player p, vector<string> tokens, int currentRoom)
{
	if (tokens.size() > 1) //Did the player specify something to open
	{
		for (int i = 0; i < 5; i++) //Loop through inventory
		{
			if (tokens[1] == p.inventory[i].name) //They have the Object to open
			{
				if (p.inventory[i].locked) //Is it locked
				{
					for (int j = 0; j < 5; j++) //Loop through inventory
					{
						if (p.inventory[j].name == p.inventory[i].key) //Do they have key
						{
							system("cls");
							setcolor(pink, black);
							std::cout << "\nYou opened the " << p.inventory[i].name << " using the " << p.inventory[i].key << " inside you found a " << p.inventory[i].reward << endl;

							setcolor(blue, black);
							room[currentRoom].objectsLT.insert(room[currentRoom].objectsLT.begin(), p.inventory[j]);//ADD TO ROOM
							p.drop(j); //drop key

							for (int k = 0; k < 5; k++) //Loop through inventory to find new loctaion
							{
								if (tokens[1] == p.inventory[k].name)
								{
									setcolor(yellow, black);
									p.takeObj(Object(p.inventory[k].reward)); //take reward
									p.inventory[k].locked = false; //unlock obj

									setcolor(blue, black);
									room[currentRoom].objectsLT.insert(room[currentRoom].objectsLT.begin(), p.inventory[k]);//ADD TO ROOM
									p.drop(k); //drop obj
								}
							}
							return p;
						}
					}
					system("cls");
					setcolor(red, black);
					std::cout << "\nYou need the " << p.inventory[i].key << " to open it!\n"; //They don't have the key
					return p;
				}
				else
				{
					system("cls");
					setcolor(red, black);
					std::cout << "\nIt's not locked!\n"; //OBJ IS NOT LOCKED
					return p;
				}
				return p;
			}
			if (i == 4) //They don't have the OBJ
			{
				system("cls");
				setcolor(red, black);
				std::cout << "\nYou can't do that!\n";
				return p;
			}
		}
	}
	else
	{
		system("cls");
		setcolor(red, black);
		std::cout << "\nOpen what?\n"; //OBJ To Open not Specified
		return p;
	}
}

int ForcedMotion(AdventureRoom* room, int currentRoom)
{
	for (list<MotionTableEntry>::iterator i = room[currentRoom].motionTable.begin(); i != room[currentRoom].motionTable.end(); i++)
	{
		if (i->direction == "FORCED")
		{
			setcolor(red, black);
			std::cout << " \n" << room[currentRoom].name << endl; //Display Room Name
			std::cout << room[currentRoom].description[0] << "\n" << room[currentRoom].description[1] << "\n" << endl; //Display Room Description

			currentRoom = i->room - 1;
			//system("cls");
			return currentRoom;
		}
	}
	return currentRoom;
}

//---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---///---//
//------MAIN------//

int main()
{
	SetConsoleTitle(TEXT("Text Adventure - By Joseph Calabro")); //Window Title

	SetCMD(); //Set Commands
	
	CountRooms();                                      //Count Number Of Rooms in the text file
	AdventureRoom* room = new AdventureRoom[rmCount]; //Create Rooms
	ReadFromFile(room);                              //Read Data Into Rooms

	setcolor(yellow, gray);

	Player p;                         //CREATE PLAYER IN STACK
	int currentRoom = 0;             //Start In The First Room
	std::cout << startMes; //display opening message
	setcolor(white, black);
	std::cout << "\n\n";

	while(input != "QUIT")        //while the player hasn't quit run the games main loop
	{
		input = "";

		for (int i = 0; i < 5; i++) //every game loop we want to check if the player has the win obj, if they do then we break out of the while loop
		{
			if (winOBJ == p.inventory[i].name)
			{
				win = true; //so we can display the win message
				break;     //break out of for loop
			} 
		}
		if (win)
		{
			break; //break out of while loop
		}

		//---//---//---//---//---//

		std::cout << " \n";
		setcolor(yellow, gray);
		std::cout << room[currentRoom].name << endl; //Display Room Name
		setcolor(cyan, black);
		std::cout << room[currentRoom].description[0] << "\n" << room[currentRoom].description[1] << "\n" << endl; //Display Room Description

		setcolor(yellow, black);
		while(input.find_first_not_of(' ') == std::string::npos) //The player has to input something otherwise the split will cause an error
			std::getline(cin,input); //Get User Input

		splitLine(input); //Split user input

		//---//---//---//---//---//---//---//
		//--Check The Players Input

		if (input == CMD[0] || input == CMD[1] || input == CMD[2] || input == CMD[3]) //-->>//NORTH//SOUTH//EAST//WEST
		{
			currentRoom = ChangeRoom(room, p, currentRoom, input); //Checks if the player can go the input direction
		}
		else
		if (input == CMD[4]) //-->>INVENTORY
		{
			system("cls");
			setcolor(yellow, black);
			p.displayInventory();
		}
		else
		if (tokens[0] == CMD[5]) //-->>TAKE
		{
			p = TakeObject(room, p, tokens, currentRoom);
		}
		else
		if (tokens[0] == CMD[6]) //-->>DROP
		{
			p = DropObject(room, p, tokens, currentRoom);
		}
		else
		if (input == CMD[7]) //-->>LOOK
		{
			Look(room, currentRoom);
		}
		else
		if (input == CMD[8]) //-->>HELP
		{
			Help();
			moves--; //HELP won't count towards the players move counter
		}
		else
		if (input == CMD[9]) //-->>TALK
		{
			Talk(room, currentRoom);
		} 
		else
		if (tokens[0] == CMD[10]) //-->>USE
		{
			p = UseObject(room, p, tokens, currentRoom);
		}
		else
		if (tokens[0] == CMD[11]) //-->>OPEN
		{
			p = OpenObject(room, p, tokens, currentRoom);
		}
		else
		if (input == "QUIT") //-->>EXIT GAME
		{
		}
		else //-->>UNKOWN CMD
		{
			system("cls");
			setcolor(red, black);
			std::cout << "\nUnknown Command: Try again\n";
			moves--; //Unknown Command won't count towards the players move counter
		}
		//FORCED
		currentRoom = ForcedMotion(room, currentRoom);

		moves++; //increment move counter;
	} 

	if (win)
	{
		setcolor(yellow, black);
		std::cout << winMes << endl << endl;
		std::cout << "Congratulations! you have won the game!\n";
		std::cout << "You did it in " << moves <<" moves!\n";
	}

	//system("cls");
	setcolor(red, black);
	std::cout << "\nPress Enter to Exit...";
	//std::cin.ignore();
	std::cin.get();	
}