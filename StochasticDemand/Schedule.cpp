#include "Schedule.h"
#include"myNode.h"



Schedule::Schedule()
{
}

void Schedule::init()
{
	initPara();
	initNetwork();
	compressNetwork();
}

void Schedule::initPara()
{
	cout << ">>> init parameter" << endl;

	struct tm timeinfo;
	timeinfo.tm_year = 2017 - 1900;
	timeinfo.tm_mon = 5 - 1;
	timeinfo.tm_mday = 6;
	timeinfo.tm_hour = 0;
	timeinfo.tm_min = 0;
	timeinfo.tm_sec = 0;
	Util::countTime = mktime(&timeinfo);
	cout << "Util::countTime:" << Util::getTimeStr(Util::countTime) << endl;
}

void Schedule::initNetwork()
{
	for (auto&leg : _legList)
	{
		bool isDep = true;
		myNode* depNode = new myNode(leg,isDep);
		depNode->getStation()->pushNode(depNode);

		isDep = false;
		myNode* arrNode = new myNode(leg, isDep);
		arrNode->getStation()->pushNode(arrNode);
	}

	int startId = 0;
	for (auto&sta : _stationList)
	{
		sta->sortNode();
		sta->setNodeId(startId);

		startId += sta->getNodeList().size();
	}

	//print
	for (auto&sta : _stationList)
	{
		sta->print();
		sta->printNodeList();
		cout << "-------------------------------------------------------------" << endl;
	}
}

void Schedule::compressNetwork()
{
	int startId = 0;

	for (auto&sta : _stationList)
	{
		sta->mergeNode();

		sta->setNodeId(startId);
		startId += sta->getNodeList().size();
	}

	//print
	for (auto&sta : _stationList)
	{
		sta->print();
		sta->printNodeList();
		cout << "-------------------------------------------------------------" << endl;
	}
}

