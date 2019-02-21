#pragma once
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Temperture
{
public:
	Temperture()
	{

	};
	void ReadFile(string name);


private:
	vector<string> stationName;
	vector<string> year;
	vector<string> month;
	vector<string> day;
	vector<string> time;
	vector<int> airTemp;

};
