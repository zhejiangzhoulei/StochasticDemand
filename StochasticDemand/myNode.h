#pragma once
#include"Util.h"
#include"Leg.h"
class Station;
class myNode
{
private:
	int _id;

	time_t _beginTime;
	time_t _endTime;
	
	Station* _station;

	vector<Leg*> _depLegList;
	vector<Leg*> _arrLegList;

public:
	myNode(Leg* leg,bool isDep);
	myNode(time_t bt,time_t et,Station* sta);

	void setId(int id) { _id = id; }
	int getId() { return _id; }

	time_t getBeginTime() { return _beginTime; }
	time_t getEndTime() { return _endTime; }

	Station* getStation() { return _station; }

	vector<Leg*> getDepLegList() { return _depLegList; }
	vector<Leg*> getArrLegList() { return _arrLegList; }

	void merge(myNode* node);

	bool passCountTime();

	static bool cmpByTime(myNode* a, myNode* b);

	void print();
};

