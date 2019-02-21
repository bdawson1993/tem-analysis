#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define __CL_ENABLE_EXCEPTIONS

#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "Utils.h"
#include "Temperture.h"

void print_help() {
	std::cerr << "Application usage:" << std::endl;

	std::cerr << "  -p : select platform " << std::endl;
	std::cerr << "  -d : select device" << std::endl;
	std::cerr << "  -l : list all platforms and devices" << std::endl;
	std::cerr << "  -h : print this message" << std::endl;
}

int main(int argc, char **argv) {
	//Part 1 - handle command line options such as device selection, verbosity, etc.
	int platform_id = 0;
	int device_id = 0;
	int max = 0;

	Temperture temp;
	temp.ReadFile("temp_lincolnshire_short.txt");

	for (int i = 1; i < argc; i++) {
		if ((strcmp(argv[i], "-p") == 0) && (i < (argc - 1))) { platform_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-d") == 0) && (i < (argc - 1))) { device_id = atoi(argv[++i]); }
		else if (strcmp(argv[i], "-l") == 0) { std::cout << ListPlatformsDevices() << std::endl; }
		else if (strcmp(argv[i], "-h") == 0) { print_help(); return 0; }
	}

	//detect any potential exceptions
	try {
		//Part 2 - host operations
		//2.1 Select computing devices
		cl::Context context = GetContext(platform_id, device_id);

		//display the selected device
		std::cout << "Running on " << GetPlatformName(platform_id) << ", " << GetDeviceName(platform_id, device_id) << std::endl;

		//create a queue to which we will push commands for the device
		cl::CommandQueue queue(context);

		//2.2 Load & build the device code
		cl::Program::Sources sources;

		AddSources(sources, "max.cl");

		cl::Program program(context, sources);

		//build and debug the kernel code
		try {
			program.build();
		}
		catch (const cl::Error& err) {
			std::cout << "Build Status: " << program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(context.getInfo<CL_CONTEXT_DEVICES>()[0]) << std::endl;
			std::cout << "Build Options:\t" << program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(context.getInfo<CL_CONTEXT_DEVICES>()[0]) << std::endl;
			std::cout << "Build Log:\t " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(context.getInfo<CL_CONTEXT_DEVICES>()[0]) << std::endl;
			throw err;
		}

		
		vector<int> temps = temp.AirTemp();

		size_t vector_elements = temps.size();//number of elements
		size_t vector_size = temps.size() * sizeof(int);//size in bytes

		//host - output
		std::vector<int> C(vector_elements);

		//device - buffers

		cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, vector_size);
		cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int));

		//Part 4 - device operations

		//4.1 Copy arrays A and B to device memory

		
		queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, vector_size, &temps[0]);
		

		//4.2 Setup and execute the kernel (i.e. device code)
		cl::Kernel kernel_add = cl::Kernel(program, "Max");
		kernel_add.setArg(0, buffer_A);
		kernel_add.setArg(1, buffer_B);

		queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(vector_elements), cl::NullRange);

		//4.3 Copy the result from device to host
		queue.enqueueReadBuffer(buffer_B, CL_TRUE, 0, sizeof(int), &max);

		cout << max << endl;
	}
	catch (cl::Error err) {
		std::cerr << "ERROR: " << err.what() << ", " << getErrorString(err.err()) << std::endl;
	}

	system("pause");

	return 0;
}