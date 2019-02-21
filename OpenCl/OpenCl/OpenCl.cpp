// OpenCl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <CL/opencl.h>
#include "Temperture.h"
#include "Timer.h"

int main()
{
	Temperture temp;

	//load files
	cout << "Loading Files" << endl;
	Timer::StartTimer();
	temp.ReadFile("temp_lincolnshire_short.txt");
	cout << "Files Loaded" << endl;
	Timer::EndTimer("File Loading");

	


	system("pause");
}
