

#include <iostream>
#include <vector>

#include "ComputeEngine.h"
#include "Temperture.h"



int main(int argc, char **argv) {
	
	Temperture temp;
	
	cout << "Loading Files..." << endl;
	temp.ReadFile("temp_lincolnshire_short.txt");
	
	

	cout << "Computing..." << endl;

	//min
	ComputeEngine minEng;
	minEng.Init("kernal.cl");
	minEng.AddBuffer(CL_MEM_READ_ONLY, temp.AirTemp().size() * sizeof(int), temp.AirTemp());
	minEng.AddBuffer(CL_MEM_READ_WRITE, sizeof(int));
	


	vector<int> min;
	min.push_back(0);
	minEng.Execute("Min", temp.AirTemp().size() * sizeof(int), min);
	cout << "Min: " << min[0] << endl;

	vector<int> max;
	max.push_back(0);
	minEng.Execute("Max", temp.AirTemp().size() * sizeof(int), max);
	cout << max[0] << endl;




	system("pause");

	return 0;
}