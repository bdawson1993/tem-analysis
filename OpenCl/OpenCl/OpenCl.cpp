#pragma once

#include <iostream>
#include <vector>

#include "ComputeEngine.h"
#include "Temperture.h"
#include "Timer.h"

#include "Utils.h"
using namespace Timer;


int print_V(vector<int> values)
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
	temp.ReadFile("temp_lincolnshire_short.txt");
	EndTimer("Loading Files");
	
	cout << "Computing..." << endl;

	//min
	ComputeEngine minEng;
	minEng.Init("kernal.cl");

	//vector<int> data = { 10,10,10,10,10 };
	vector<int> min(temp.AirTemp().size(),0);
	cout << min.size();

	StartTimer();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	EndTimer("Memory Copying");
	

	minEng.Execute("Sort", min, false);

	
	print_V(min);

	system("pause");

	return 0;
}