#pragma once
#include"Util.h"
class Fleet
{
private:
	int _id;
	static int _count;

	string _name;

	int _capacity;

public:
	Fleet(string name);

	int getId() { return _id; }

	void setCap(int cap) { _capacity = cap; }
	int getCap() { return _capacity; }
};

