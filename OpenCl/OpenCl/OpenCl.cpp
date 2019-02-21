// OpenCl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <CL/opencl.h>
#include "Temperture.h"

int main()
{
	Temperture temp;

	cout << "Loading Files" << endl;
	temp.ReadFile("temp_lincolnshire_short.txt");
	cout << "Files Loaded" << endl;

	temp.Table(1);


	system("pause");
}
