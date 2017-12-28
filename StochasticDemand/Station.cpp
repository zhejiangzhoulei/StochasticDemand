#include "Station.h"
int Station::_count = 0;

Station::Station(string no)
{
	_id = _count;
	_count++;
}

void Station::setNodeId(int startId)
{
	int countId = startId;
	for (auto&node : _nodeList)
	{
		node->setId(countId);
		countId++;
	}
}

void Station::mergeNode()
{
	int size = _nodeList.size();
	
	if ( size <= 1)
	{
		return;
	}

	int i = 0;
	int j = 1;
	while (j < size)
	{
		if (_nodeList[i]->getDepLegList().empty() || _nodeList[j]->getArrLegList().empty())
		{
			_nodeList[j]->merge(_nodeList[i]);
			_nodeList.erase(_nodeList.begin()+i+1);//erase the (i+1)th element with index = i
		}
		else
		{
			++i;
			++j;
		}
	}
}

myNode * Station::getCountNode()
{
	if (_nodeList.empty())
	{
		return NULL;
	}
	if (_nodeList.size() == 1)
	{
		return _nodeList.front();
	}

	for (int i = 0; i < _nodeList.size()-1; ++i)
	{
		time_t curBgt = _nodeList[i]->getBeginTime();
		time_t nextBgt = _nodeList[i+1]->getBeginTime();

		if (curBgt <= Util::countTime&&nextBgt >= Util::countTime)
		{
			return _nodeList[i];
		}

		//struct tm timeinfo;
		//char buffer[80];
		//localtime_s(&timeinfo, &curBgt);
		//int t1 = timeinfo.tm_hour * 3600 + timeinfo.tm_min * 60;
		//localtime_s(&timeinfo, &nextBgt);
		//int t2 = timeinfo.tm_hour * 3600 + timeinfo.tm_min * 60;
		//if (t1 < t2 && t1 <= Util::countTime&&t2 >= Util::countTime)
		//{
		//	return _nodeList[i];
		//}
		//if (t1 > t2 && (t1 <= Util::countTime || t2 >= Util::countTime))
		//{
		//	return _nodeList[i];
		//}

	}

	return _nodeList.back();
	
}

void Station::print()
{
	cout << "sta_" << _id << "\tno:" << _no << endl;
}

void Station::printNodeList()
{
	for (auto&node : _nodeList)
	{
		cout << "\t";
		node->print();
	}
}
