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

	vector<int> part;
	part.push_back(0);

	vector<int> min;
	min.push_back(0);

	StartTimer();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	EndTimer("Memory Copying");
	

	minEng.Execute("Min", min);
	cout << "Min: " << min[0] << endl;

	




	system("pause");

	return 0;
}