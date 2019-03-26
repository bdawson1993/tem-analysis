#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "ComputeEngine.h"
#include "Temperture.h"
#include "Timer.h"

#include "Utils.h"
using namespace Timer;
using namespace std;

void print_V(vector<int> values)
{
	cout << "{ ";
	for (int index = 0; index < values.size() - 1; index++)
	{
		cout << values[index] << ", ";
	}
	cout << "}";
}

int main(int argc, char **argv) {
	
	Temperture temp;
	
	cout << "Loading Files..." << endl;
	StartTimer();
	temp.ReadFile("temp_lincolnshire.txt");
	EndTimer("Loading Files");
	
	cout << "Computing..." << endl;

	//min
	ComputeEngine minEng;
	minEng.Init("kernal.cl");

	//vector<int> data = { 10,10,10,10,10 };
	vector<int> min(temp.AirTemp().size(),0);
	

	StartTimer();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	EndTimer("Memory Copying");
	

	//serial sort
	//vector<int> sorted = temp.AirTemp();
	//sort(sorted.begin(), sorted.end());

	//compute sum
	//minEng.Execute("Sum", min, true);
	//cout << "Temperature AVG: " << min[0] / temp.AirTemp().size() << endl;

	//compute min
	//minEng.Execute("Min", min, false);
	//cout << "Min : " << min[0] << endl;

	//compute max
	//minEng.Execute("Max", min, false);
	//cout << "Max : " << min[0] << endl;

	//sort
	minEng.Execute("MaxL", min, true);
	cout << min[0] << endl;
	//print_V(min);
	system("pause");

	return 0;
}