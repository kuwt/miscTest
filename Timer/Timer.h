#pragma once

/***********************************
* Start Timer at 0
*************************************/
void StartCounter();
void StartCounter(const std::string &TimerName);

/***********************************
* Start Timer at previous end 
*************************************/
void StartIncCounter(const std::string & TimerName);

/***********************************
* Get Timing from previous start 
*************************************/
double GetCounter();
double GetCounter(const std::string &TimerName);

/***********************************
* Stop Timer and Record the time to name specified
*************************************/
void StopAndRecCounter(const std::string &TimerName);

/***********************************
* Write Timer log 
*************************************/
void LogTimer(const std::string &logPath = "C:\\temp");

void ClearTimer();

/***********************************
example

int main()
{
	StartCounter();
	Sleep(1000);
	std::cout << GetCounter() << "\n";
	return 0;
}
***************************************/