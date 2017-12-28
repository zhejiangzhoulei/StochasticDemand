#pragma once

#include<iostream>
#include<fstream>

#include<stdio.h>

#include <algorithm>
#include<vector>
#include<array>

#include<string>
#include<ctime>

//#include<process.h>
//#include<random>
//#include <iomanip>//¸¡µãÊý´òÓ¡

using namespace std;

class Util
{
public:
	static string InputPath;
	static string OutputPath;

	static double Epsilon;//0.0001

	static int scenarioNum;//# of scenarios
	static time_t countTime;//for aft num cons. seconds since 00:00

	//print
	static string getTimeStr(time_t t);
	static void printCurTime();

	//time
	static int getHour(time_t t);
	static int getSecond(time_t t);
};

