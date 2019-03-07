#include "ComputeEngine.h"

using namespace std;



///Init openCL
void ComputeEngine::Init(string kernalName)
{
	context = GetContext(platformID, deviceID);
	queue = cl::CommandQueue(context);
	AddSources(sources,kernalName);
	program = cl::Program(context, sources);

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
	//cout << ListPlatformsDevices() << endl;
}

///add buffer
void ComputeEngine::AddBuffer(cl_mem_flags flag, size_t size)
{
	
	buffers.push_back(cl::Buffer(context, flag, size));
}

///Add buffer and write
void ComputeEngine::AddBuffer(cl_mem_flags flag, size_t size, vector<int> data)
{
	input_elements = data.size();
	padding_size = data.size() % local_size;
	if (padding_size) {
		//create an extra vector with neutral values
		std::vector<int> A_ext(local_size - padding_size, 0);
		//append that extra vector to our input
		data.insert(data.end(), A_ext.begin(), A_ext.end());
	}

	try
	{
		cl::Buffer buffer(context, flag, size);
		buffers.push_back(buffer);

		queue.enqueueWriteBuffer(buffer, CL_TRUE, 0, size, &data[0]);
	}
	catch (const cl::Error& err)
	{
		std::cerr << "ERROR: " << err.what() << ", " << getErrorString(err.err()) << std::endl;
	}

	
}


///Execute the kernal code
void ComputeEngine::Execute(const char* funName, int size, vector<int>& output)
{
	//size_t nr_groups = input_elements / local_size;
	//cout << nr_groups << endl;
	try
	{
		cl::Kernel* kernal = new cl::Kernel(program, funName);
		for (int index = 0; index <= buffers.size() - 1; index++)
		{
			kernal->setArg(index, buffers[index]);
		}

		queue.enqueueNDRangeKernel(*kernal, cl::NullRange, cl::NDRange(size), cl::NDRange(local_size));
		queue.enqueueReadBuffer(buffers.back(), CL_TRUE, 0, sizeof(int), &output[0]);
		
	}
	catch (const cl::Error& err)
	{
		std::cerr << "ERROR: " << err.what() << ", " << getErrorString(err.err()) << std::endl;
	}

	
	


}

void ComputeEngine::Clean()
{
	//dispose of opencl resources
}

