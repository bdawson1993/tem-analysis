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

void print_V(vector<int> values);
int Max();
int Min();
int Sum();
int Sum(vector<int> values);
vector<int> Sort();
vector<int> SubtractAndSqaure(int mean);

ComputeEngine minEng;
Temperture temp;


int main(int argc, char **argv) {
	
	
	
	cout << "Loading Files..." << endl;
	StartTimer();
	temp.ReadFile("temp_lincolnshire.txt");
	EndTimer("Loading Files");
	
	cout << "Computing..." << endl;
	minEng.Init("kernal.cl");

	//output results
	//max
	StartTimer();
	cout << "Max : " << Max() << endl;
	EndTimer("Max");

	//min
	StartTimer();
	cout << "Min : " << Min() << endl;
	EndTimer("Min");

	//Mean
	StartTimer();
	cout << "Mean: " << Sum() / temp.AirTemp().size() << endl;
	EndTimer("Mean");


	//STD
	StartTimer();
	int avg = Sum() / temp.AirTemp().size();
	vector<int>subtractedVector = SubtractAndSqaure(avg);
	int sigma = Sum(subtractedVector);
	cout << "Standard Divation: " << float(sigma / temp.AirTemp().size()) << endl;
	EndTimer("Standard Divation");


	StartTimer();
	vector<int> sortedData = Sort();
	EndTimer("Sort");

	print_V(sortedData);

	//serial functions
	
	


	system("pause");

	return 0;
}

void print_V(vector<int> values)
{
	cout << "{ ";
	for (int index = 0; index < values.size() - 1; index++)
	{
		cout << values[index] << ", ";
	}
	cout << "}";
}

int Max()
{
	vector<int> value(temp.AirTemp().size(),0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("MaxL", value, true);

	return value[0];
}

int Min()
{
	vector<int> value(temp.AirTemp().size(), 0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("MinL", value, true);

	return value[0];
}

int Sum()
{
	vector<int> value(temp.AirTemp().size(), 0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("Sum", value, true);


	return value[0];
}

int Sum(vector<int> values)
{
	vector<int> value(values.size(), 0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, values);
	minEng.AddBuffer(CL_MEM_READ_WRITE, values.size() * sizeof(int));
	minEng.Execute("Sum", value, true);
	
	return value[0];

}

vector<int> Sort()
{
	vector<int> values(temp.AirTemp().size(), 0);

	minEng.Clean();

	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("OddEvenSort", values);

	return values;

}

vector<int> SubtractAndSqaure(int mean)
{
	vector<int> value(temp.AirTemp().size(), 0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_ONLY, mean);
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("SubtractAndSq", value, false);

	return value;
}
