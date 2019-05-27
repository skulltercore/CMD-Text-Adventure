#pragma once
#ifndef  NPC_H
#define NPC_H
#include <iostream>
#include "Object.h"
using namespace std;

class NPC
{
public:
	string name, dialouge1, dialouge2, dialouge3, need, rewardName;
	Object reward;

	bool complete = false;

	NPC(string npcName, string n, Object r, string d1, string d2, string d3);

	NPC();


	void talk();


	void use();

};

#endif