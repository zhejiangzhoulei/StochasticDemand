#pragma once
#include"Leg.h"
#include"Fleet.h"
#include"Station.h"
class Schedule
{
private:
	//input
	vector<Leg*> _legList;
	vector<Fleet*> _fleetList;
	vector<Station*> _stationList;

public:
	Schedule();

	void init();
	void initPara();
	void initNetwork();
	void compressNetwork();

	void setLegList(vector<Leg*> legs) { _legList = legs; }
	vector<Leg*> getLegList() { return _legList; }
	
	void setFleetList(vector<Fleet*> fleets) { _fleetList = fleets; }
	vector<Fleet*> getFleetList() { return _fleetList; }

	void setStation(vector<Station*> stations) { _stationList = stations; }
	vector<Station*> getStationList() { return _stationList; }


};

