#pragma once

#include <iostream>
#include <vector>

#include "ComputeEngine.h"
#include "Temperture.h"
#include "Timer.h"

using namespace Timer;

int main(int argc, char **argv) {
	
	Temperture temp;
	
	cout << "Loading Files..." << endl;
	StartTimer();
	temp.ReadFile("temp_lincolnshire_short.txt");
	EndTimer("Loading Files");
	
	

	cout << "Computing..." << endl;

	//min
	ComputeEngine minEng;
	minEng.Init("kernal.cl");

	StartTimer();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp().size() * sizeof(int), temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, sizeof(int));
	EndTimer("Memory Copying");
	


	vector<int> min;
	min.push_back(0);
	minEng.Execute("Min", temp.AirTemp().size() * sizeof(int), min);
	cout << "Min: " << min[0] << endl;

	vector<int> max;
	max.push_back(0);
	minEng.Execute("Sum", temp.AirTemp().size() * sizeof(int), max);

	float avg = max[0] / temp.AirTemp().size() - 1;
	cout <<  "AVG: " << max[0] << endl;




	system("pause");

	return 0;
}