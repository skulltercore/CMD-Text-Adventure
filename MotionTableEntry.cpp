#include "MotionTableEntry.h"


	MotionTableEntry::MotionTableEntry(string dir, int rm)
	{
		direction = dir; //Direction the player can go
		room = rm; // the room that direction will lead to
	}

	MotionTableEntry::MotionTableEntry(string dir, int rm, string k) //Locked direction
	{
		direction = dir;
		room = rm;
		key = k; //the name of the key object they need to unlock the direction
		locked = true;
	}

