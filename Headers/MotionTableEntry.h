#pragma once
#ifndef  MTE_H
#define MTE_H
#include <iostream>
using namespace std;

class MotionTableEntry
{
public:
	string direction, key;
	int room;
	bool locked = false;

	MotionTableEntry(string dir, int rm);

	MotionTableEntry(string dir, int rm, string k);


};

#endif