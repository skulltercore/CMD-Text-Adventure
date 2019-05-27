#include "AdventureRoom.h"

AdventureRoom::AdventureRoom(int num, string roomName, string des[], list<Object> objlist, bool vis, list<MotionTableEntry> MT) //Normal room constructor
{
	roomNum = num; //Room Number
	name = roomName;
	description[0] = des[0]; //Description Line 1
	description[1] = des[1]; //Description Line 2
	list<Object> objectLT2(objlist); //List of objects in the room
	objectsLT = objectLT2;
	//objectsLT = objlist;
	visited = vis;

	list<MotionTableEntry> motionTable2(MT); //List of motion table entries
	motionTable = motionTable2;

}
AdventureRoom::AdventureRoom(int num, string roomName, string des[], list<Object> objlist, bool vis, list<MotionTableEntry> MT, NPC n) //NPC room overload constructor
{
	roomNum = num;
	name = roomName;
	description[0] = des[0];
	description[1] = des[1];
	list<Object> objectLT2(objlist);
	objectsLT = objectLT2;
	//objectsLT = objlist;
	visited = vis;

	NPC npc2 = n; //creates NPC
	npc = npc2;
	isNPC = true;

	list<MotionTableEntry> motionTable2(MT);
	motionTable = motionTable2;

}
AdventureRoom::AdventureRoom()
{

}