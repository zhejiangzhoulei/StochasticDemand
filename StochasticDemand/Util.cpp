#include "Util.h"

string Util::OutputPath = "C:/output/";
string Util::InputPath = "C:/output/";

double Util::Epsilon = 0.0001;//0.0001
int Util::scenarioNum = 10;//# of scenarios
time_t Util::countTime = 0;//for aft num cons.

//print
string Util::getTimeStr(time_t t)
{
	struct tm timeinfo;
	char buffer[80];
	localtime_s(&timeinfo, &t);
	strftime(buffer, 80, "%Y/%m/%d %R", &timeinfo);
	//strftime(buffer, 80, "%Y/%m/%d %T", &timeinfo);
	return buffer;
}

void Util::printCurTime()
{
	time_t t = time(NULL);
	cout << ">>> PRINT TIME: " << Util::getTimeStr(t) << endl;
}

int Util::getHour(time_t t)
{
	struct tm timeinfo;
	char buffer[80];
	localtime_s(&timeinfo, &t);
	return timeinfo.tm_hour;
}

int Util::getSecond(time_t t)
{
	struct tm timeinfo;
	char buffer[80];
	localtime_s(&timeinfo, &t);
	return timeinfo.tm_sec;
}
