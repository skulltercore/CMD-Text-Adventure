#pragma once
#ifndef  AR_H
#define AR_H
#include <iostream>
#include <list>
#include "Object.h"
#include "NPC.h"
#include "MotionTableEntry.h"
using namespace std;

class AdventureRoom
{
public:

	int roomNum;
	std::string name;
	std::string description[2];
	list<Object> objectsLT;
	bool visited = false, isNPC = false;
	NPC npc;
	list<MotionTableEntry> motionTable;

	AdventureRoom(int num, std::string roomName, std::string des[], list<Object> objlist, bool vis, list<MotionTableEntry> MT); //Constructor

	AdventureRoom(int num, std::string roomName, std::string des[], list<Object> objlist, bool vis, list<MotionTableEntry> MT, NPC n); //Constructor if there's an NPC

	AdventureRoom();

};

#endif