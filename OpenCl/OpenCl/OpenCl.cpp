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
	vector<string> file = {"temp_lincolnshire.txt", "temp_lincolnshire_short.txt" };
	int input = 0;

	cout << "0 - full dataset" << endl;
	cout << "1 - short dataset" << endl;
	cout << "Please enter an option " << endl;
	cin >> input;

	
	
	
	
	cout << "Loading Files..." << endl;
	StartTimer();
	temp.ReadFile(file[input]);
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

///Max Value
int Max()
{
	vector<int> value(temp.AirTemp().size(),0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("MaxL", value, true);

	return value[0];
}

///Min value
int Min()
{
	vector<int> value(temp.AirTemp().size(), 0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("MinL", value, true);

	return value[0];
}

///Sum of all values
int Sum()
{
	vector<int> value(temp.AirTemp().size(), 0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("Sum", value, true);


	return value[0];
}

///Sum of all values
int Sum(vector<int> values)
{
	vector<int> value(values.size(), 0);

	minEng.Clean();
	minEng.AddBuffer(CL_MEM_READ_ONLY, values);
	minEng.AddBuffer(CL_MEM_READ_WRITE, values.size() * sizeof(int));
	minEng.Execute("Sum", value, true);
	
	return value[0];

}

///Sort setup and exectuion
vector<int> Sort()
{
	vector<int> values(temp.AirTemp().size(), 0);

	minEng.Clean();

	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int));
	minEng.Execute("OddEvenSort", values);

	return values;

}


///Subtract and Square 
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
