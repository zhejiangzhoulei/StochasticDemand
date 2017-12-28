#include "myNode.h"



myNode::myNode(Leg * leg, bool isDep)
{
	if (isDep)
	{
		_beginTime = leg->getDepTime();
		_endTime = _beginTime;
		_station = leg->getDepStation();

		_depLegList.push_back(leg);
	}
	else
	{
		_beginTime = leg->getArrTime();
		_endTime = _beginTime;
		_station = leg->getArrStation();

		_arrLegList.push_back(leg);
	}
}

myNode::myNode(time_t bt, time_t et, Station * sta):
	_beginTime(bt),_endTime(et),_station(sta)
{
}

void myNode::merge(myNode * node)
{
	if (_beginTime > node->getBeginTime())
	{
		_beginTime = node->getBeginTime();
	}

	if (_endTime < node->getEndTime())
	{
		_endTime = node->getEndTime();
	}

	vector<Leg*> legs = node->getDepLegList();
	_depLegList.insert(_depLegList.end(), legs.begin(), legs.end());
	legs = node->getArrLegList();
	_arrLegList.insert(_arrLegList.end(), legs.begin(), legs.end());

}

bool myNode::passCountTime()
{
	if (_beginTime <= Util::countTime&&_endTime >= Util::countTime)
	{
		return true;
	}
	return false;
}

bool myNode::cmpByTime(myNode * a, myNode * b)
{
	if (a->getBeginTime() < b->getBeginTime())
	{
		return true;
	}

	if (a->getBeginTime() > b->getBeginTime())
	{
		return false;
	}

	if (a->getEndTime() <= b->getEndTime())
	{
		return true;
	}

	return false;
}

void myNode::print()
{
	cout << "node_" << _id
		<< "\t" << Util::getTimeStr(_beginTime) << "\t" << Util::getTimeStr(_endTime)
		<< "\t#dep:" << _depLegList.size() << "\t#arr:" << _arrLegList.size() << endl;
}
