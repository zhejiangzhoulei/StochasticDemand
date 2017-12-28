#pragma once
#include"Util.h"
class Station;
class Leg
{
private:
	int _id;
	static int _count;

	string _no;

	time_t _depTime;
	time_t _arrTime;

	Station* _depSta;
	Station* _arrSta;

	vector<int> _demandList;

public:
	Leg(string no,time_t depT,time_t arrT,Station* depSta,Station* arrSta);

	int getId() { return _id; }

	time_t getDepTime() { return _depTime; }
	time_t getArrTime() { return _arrTime; }

	Station* getDepStation() { return _depSta; }
	Station* getArrStation() { return _arrSta; }

	void setDemand(vector<int> demands) { _demandList = demands; }
	vector<int> getDemandList() { return _demandList; }
	int getDemand(int snrId);

	bool passCountTime();
};

