#include <windows.h>
#include <iostream>
#include "Timer.h"
#include <map>
#include <string>
#include <fstream>
#include <opencv2/core/core.hpp>

#define _MAX_NUM_COUNTER (30)
 double PCFreq = 0.0;
 __int64 CounterStart = 0;
 __int64 CounterStartEx[_MAX_NUM_COUNTER] = { 0 };
 std::map<std::string, double > mapCounter;
 std::map<std::string, float > mapCounterIncrement;


void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	//PCFreq = double(li.QuadPart) / 1000.0;
	PCFreq = double(li.QuadPart);
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void StartCounter(const std::string & TimerName)
{

	mapCounter[TimerName] = cv::getTickCount();
	mapCounterIncrement[TimerName] = 0;
}

void StartIncCounter(const std::string & TimerName)
{
	mapCounter[TimerName] = cv::getTickCount();
	auto it = mapCounterIncrement.find(TimerName);
	if (it == mapCounterIncrement.end())  // if the name not exist
	{
		mapCounterIncrement[TimerName] = 0;
	}
}

double GetCounter(const std::string & TimerName)
{
	double curr  = cv::getTickCount();
	auto it = mapCounter.find(TimerName);
	if (it != mapCounter.end())
	{
		return (curr - it->second) / cv::getTickFrequency();
	}
	return 0;
}

void StopAndRecCounter(const std::string & TimerName)
{
	
	auto it = mapCounter.find(TimerName);
	if (it != mapCounter.end())
	{
		double curr = cv::getTickCount();
		double Time = (curr - it->second) / cv::getTickFrequency();
		double OriTime = mapCounterIncrement[TimerName];
		mapCounterIncrement[TimerName] += Time;
	}
}

void LogTimer(const std::string &logPath)
{
	std::string path = logPath + "\\Timer.txt";
	std::ofstream outputFile(path);

	for (auto const &it : mapCounterIncrement)
	{
		outputFile << it.first << "    " << (float)it.second << " sec" << std::endl;
	}
	mapCounter.clear();
	mapCounterIncrement.clear();

}

void ClearTimer()
{
	mapCounter.clear();
	mapCounterIncrement.clear();
}