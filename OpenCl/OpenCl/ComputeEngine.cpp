#include "ComputeEngine.h"


///Init openCL
void ComputeEngine::Init(string kernalName)
{
	context = GetContext(platformID, deviceID);
	
	AddSources(sources,kernalName);
	program = cl::Program(context, sources);

	queue = cl::CommandQueue(context);
	
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
void ComputeEngine::AddBuffer(cl_mem_flags flag, vector<int> data)
{
	//pad array to fit to local size
	padding_size = data.size() % local_size;
	if (padding_size) {
		std::vector<int> A_ext(local_size - padding_size, 0);
		data.insert(data.end(), A_ext.begin(), A_ext.end());
	}

	//data stats
	input_elements = data.size();
	input_size = data.size()*sizeof(int);

	//create buffer
	try
	{
		cl::Buffer buffer(context, flag, input_size);
		buffers.push_back(buffer);

		queue.enqueueWriteBuffer(buffer, CL_TRUE, 0, input_size, &data[0]);
		
	}
	catch (const cl::Error& err)
	{
		std::cerr << "ERROR: " << err.what() << ", " << getErrorString(err.err()) << std::endl;
	}

	
}


///Execute the kernal code
void ComputeEngine::Execute(const char* funName, vector<int>& output, bool useLocal, int localCount)
{
	size_t nr_groups = input_elements / local_size;
	

	//cl_event profEvent = clCreateUserEvent(context, 0);
	//cout << nr_groups << endl;
	try
	{
		cl::Kernel kernal =  cl::Kernel(program, funName);
		
		int index = 0;
		for (index = 0;index <= buffers.size() - 1; index++)
		{
			kernal.setArg(index, buffers[index]);
		}
		
		//build local buffers
		if (useLocal)
		{
			for(index; index <= localCount+1;index++)
			{
				kernal.setArg(index, cl::Local(local_size * sizeof(int)));
			}
		}

		//execute kernal
		
		queue.enqueueNDRangeKernel(kernal, cl::NullRange, cl::NDRange(input_elements), cl::NDRange(local_size));
		queue.enqueueReadBuffer(buffers.back(), CL_TRUE, 0, output.size()*sizeof(int), &output[0],0);
		//queue.finish();
		
		
		//cout << GetFullProfilingInfo(ev, ProfilingResolution::PROF_US) << endl;
		
		
	}
	catch (const cl::Error& err)
	{
		std::cerr << "ERROR: " << err.what() << ", " << getErrorString(err.err()) << std::endl;
	}

	
	
	

}

///Clear buffer vector
void ComputeEngine::Clean()
{
	buffers.clear();
}

