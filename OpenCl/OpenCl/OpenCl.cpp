

#include <iostream>
#include <vector>

#include "ComputeEngine.h"
#include "Temperture.h"



int main(int argc, char **argv) {
	
	Temperture temp;
	
	cout << "Loading Files..." << endl;
	temp.ReadFile("temp_lincolnshire_short.txt");
	
	

	cout << "Computing..." << endl;

	ComputeEngine eng;
	eng.Init("kernal.cl");
	eng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int), temp.AirTemp());
	eng.AddBuffer(CL_MEM_READ_WRITE, sizeof(int));


	vector<int> min;
	min.push_back(0);
	eng.Execute("Min", temp.AirTemp().size() * sizeof(int), min);
	cout << "Min: " << min[0] << endl;

	vector<int> max;
	max.push_back(0);
	eng.Execute("Max", temp.AirTemp().size() * sizeof(int), max);
	cout << "Max: " << max[0] << end;


	system("pause");

	return 0;
}