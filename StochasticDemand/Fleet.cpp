#include "Fleet.h"

int Fleet::_count = 0;

Fleet::Fleet(string name):_name(name)
{
	_id = _count;
	_count++;
}
