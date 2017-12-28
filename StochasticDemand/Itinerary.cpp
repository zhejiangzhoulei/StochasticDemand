#include "Itinerary.h"

int Itinerary::_count = 0;

Itinerary::Itinerary()
{
	_id = _count;
	_count++;
}
