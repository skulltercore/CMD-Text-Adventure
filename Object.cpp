
#include "Object.h"

    Object::Object(string objName) //Normal OBJ
	{
		name = objName; //OBJ Name
	}
	Object::Object(string objName, string k, string r) //OBJ That Needs A Key To Open It (Chest)
	{
		name = objName; //OBJ Name
		key = k; //Name of OBJ needed to open It
		reward = r; //The name of the OBJ Inside, Given to the player once opened
		locked = true; //Whether or not the OBJ has been opened yet.
	}
	Object::Object()
	{

	}
