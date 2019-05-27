#include "Player.h"


Player::Player() //Initialise Inventory in Constructor
{
	inventory[0] = Object("EMPTY");
	inventory[1] = Object("EMPTY");
	inventory[2] = Object("EMPTY");
	inventory[3] = Object("EMPTY");
	inventory[4] = Object("EMPTY");
}

//------------------------------------------------------------------------->Display Inventory
void Player::displayInventory()
{
	cout << "\n|| INVENTORY ||" << endl;

	for (int i = 0; i < 5; i++) //Loops through and displays each OBJ name
	{
		cout << "--> " << inventory[i].name << "||" << endl;
	}

	cout << "" << endl; //Space
}

//----------------------------------------------------------------------->>Take Object
bool Player::takeObj(Object obj)
{
	for (int i = 0; i < 5; i++)
	{
		if (inventory[i].name == "EMPTY") //Adds OBJ to next Empty Slot In the Inventory 
		{
			inventory[i] = obj;
			cout << "\nThe " << inventory[i].name << " has been added to your inventory\n" << endl;

			return true;
			break;
		}

		if (i == 4) //Inventory Is full
		{
			cout << "\nYour inventory is full" << endl;
			return false;
		}
	}
}

void Player::drop(int inv)
{

	cout << "\nYou droped the " << inventory[inv].name << endl; //Drop Message

	if (inv != 4)
	{
		for (int i = inv + 1; i < 5; i++) //Loops Through Inventory
		{
			inventory[i - 1] = inventory[i]; //Moves all OBJ Bellow the droped OBJ UP One  

			if (i == 4)
			{
				inventory[i] = Object("EMPTY"); //Replaces OBJ With Empty OBJ
			}
		}
	}
	else
	{
		inventory[inv] = Object("EMPTY"); //Replaces OBJ With Empty OBJ
	}
}

void Player::use(int inv)
{

	cout << "\nYou used the " << inventory[inv].name << endl; //Use Message

	if (inv != 4)
	{
		for (int i = inv + 1; i < 5; i++)
		{
			inventory[i - 1] = inventory[i]; //Moves all OBJ Bellow the Used OBJ UP One  

			if (i == 4)
			{
				inventory[i].name = "EMPTY"; //Make OBJ Empty
			}
		}
	}
	else
	{
		inventory[inv].name = "EMPTY"; //Make OBJ Empty
	}
}