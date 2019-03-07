#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define __CL_ENABLE_EXCEPTIONS


#include <CL/cl.hpp>
#include <vector>
#include <iostream>
#include "Utils.h"




class ComputeEngine
{
public:
	ComputeEngine()
	{

	};
	~ComputeEngine()
	{

	};


	void Init(string kernalName);

	void AddBuffer(cl_mem_flags flag, size_t size);
	void AddBuffer(cl_mem_flags flag, size_t size, vector<int> data);
	

	void Execute(const char* funName, int size, vector<int>& output);
	void Clean();

private:
	int platformID = 0;
	int deviceID = 0;
	cl::Context context;
	cl::CommandQueue queue;
	cl::Program program;
	cl::Program::Sources sources;
	vector<cl::Buffer> buffers;

	size_t local_size = 12;
	size_t padding_size = 0;
	size_t input_elements = 0;

	

};
