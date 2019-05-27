#pragma once

#include <iostream>
#include "Object.h"
using namespace std;

class Player
{
private:


public:

	Object inventory[5];

	Player();


	//------------------------------------------------------------------------->Display Inventory
	void displayInventory();


	//----------------------------------------------------------------------->>Take Object
	bool takeObj(Object obj);


	void drop(int inv);


	void use(int inv);

};