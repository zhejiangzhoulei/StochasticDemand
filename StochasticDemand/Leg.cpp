#include "Leg.h"

int Leg::_count = 0;

Leg::Leg(string no, time_t depT, time_t arrT, Station * depSta, Station * arrSta):
	_no(no),_depTime(depT),_arrTime(arrT),_depSta(depSta),_arrSta(arrSta)
{
	_id = _count;
	_count++;
}

int Leg::getDemand(int snrId)
{
	if (snrId >= _demandList.size())
	{
		cout << "Error:getDemand" << endl;
		return -1;
	}

	return _demandList[snrId];
}

bool Leg::passCountTime()
{
	if (_depTime <= Util::countTime&&_arrTime >= Util::countTime)
	{
		return true;
	}
	
	//struct tm timeinfo;
	//char buffer[80];
	//localtime_s(&timeinfo, &_depTime);
	//int dep = timeinfo.tm_hour * 3600 + timeinfo.tm_min * 60;
	//localtime_s(&timeinfo, &_arrTime);
	//int arr = timeinfo.tm_hour * 3600 + timeinfo.tm_min * 60;
	//if (dep<arr&&dep <= Util::countTime&&arr >= Util::countTime)
	//{
	//	return true;
	//}
	//if (dep > arr && (dep <= Util::countTime || arr >= Util::countTime))
	//{
	//	return true;
	//}
	
	return false;
}
