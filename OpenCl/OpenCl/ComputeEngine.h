#pragma once
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "Utils.h"



class ComputeEngine
{
public:
	ComputeEngine();
	~ComputeEngine();

	void AddBuffer(int size);

private:
	int platformID = 0;
	int deviceID = 0;
	cl::Context context;
	cl::CommandQueue queue;
	cl::Program program;
	cl::Program::Sources sources;
	vector<cl::Buffer> buffers;
};
