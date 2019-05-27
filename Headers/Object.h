#pragma once
#ifndef  OBJECT_H
#define OBJECT_H
#include <iostream>
#include <string>
using namespace std;

class Object
{
public:
	string name, key, reward;

	bool locked = false;

	Object(string objName);

	Object(string objName, string k, string r);

	Object();

};

#endif