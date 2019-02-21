

#include <iostream>
#include <vector>

#include "ComputeEngine.h"
#include "Temperture.h"



int main(int argc, char **argv) {
	
	Temperture temp;
	
	temp.ReadFile("temp_lincolnshire_short.txt");
	
	int output = 0;

	ComputeEngine eng;
	eng.Init("max.cl");
	eng.AddBuffer(CL_MEM_READ_WRITE, temp.AirTemp().size() * sizeof(int), temp.AirTemp());
	eng.AddBuffer(CL_MEM_READ_WRITE, sizeof(int));

	const char* name = "Max";
	eng.Execute(name, temp.AirTemp().size() * sizeof(int), output);

	
	cout << output << endl;

	system("pause");

	return 0;
}