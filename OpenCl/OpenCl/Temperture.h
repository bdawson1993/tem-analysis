#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

using namespace std;

class Temperture
{
public:
	Temperture()
	{

	};
	void ReadFile(string name);


	vector<string> StationName();
	vector<string> Year();
	vector<string> Month();
	vector<string> Day();
	vector<string> Time();
	vector<int> AirTemp();


private:
	vector<string> stationName;
	vector<string> year;
	vector<string> month;
	vector<string> day;
	vector<string> time;
	vector<int> airTemp;

};
