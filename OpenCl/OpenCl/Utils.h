#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <CL/cl.hpp>


using namespace std;

template <typename T>
ostream& operator<< (ostream& out, const vector<T>& v);
string GetPlatformName(int platform_id);
string GetDeviceName(int platform_id, int device_id);
const char *getErrorString(cl_int error);
void CheckError(cl_int error);
void AddSources(cl::Program::Sources& sources, const string& file_name);
string ListPlatformsDevices();
cl::Context GetContext(int platform_id, int device_id);
enum ProfilingResolution {
	PROF_NS = 1,
	PROF_US = 1000,
	PROF_MS = 1000000,
	PROF_S = 1000000000
};
string GetFullProfilingInfo(const cl::Event& evnt, ProfilingResolution resolution);