

//works on small data set
kernel  void Min(global const int* data, global int* min)
{
	//Reduction on local
	int id = get_global_id(0);
	int N = get_global_size(0);
	min[id] = data[id];

	barrier(CLK_GLOBAL_MEM_FENCE); //wait for all threads to init and copy


	for (int i = 0; i < N; i += 2) {
		if (!(id % (i * 2)) && ((id + i) < N))
			if (min[id] > min[id + i])
			{
				min[id] = min[id + i];
			}

		barrier(CLK_GLOBAL_MEM_FENCE); 
	}
}

//works on small data set
kernel  void Max(global const int* data, global int* min)
{
	//Reduction on local
	int id = get_global_id(0);
	int N = get_global_size(0);
	

	barrier(CLK_GLOBAL_MEM_FENCE); //wait for all threads to init and copy


	for (int i = 0; i < N; i += 2) {
		if (!(id % (i * 2)) && ((id + i) < N))
			if (min[id] < min[id + i])
			{
				min[id] = min[id + i];
			}

		barrier(CLK_GLOBAL_MEM_FENCE);
	}
}


//reduce using local memory (so called privatisation)
kernel void Sum(global const int* A, global int* B, local int* scratch) {
	int id = get_global_id(0);
	int lid = get_local_id(0);
	int N = get_local_size(0);

	//cache all N values from global memory to local memory
	scratch[lid] = A[id];

	barrier(CLK_LOCAL_MEM_FENCE);//wait for all local threads to finish copying from global to local memory

	for (int i = 1; i < N; i *= 2) {
		if (!(lid % (i * 2)) && ((lid + i) < N))
			scratch[lid] += scratch[lid + i];

		barrier(CLK_LOCAL_MEM_FENCE);
	}

	

	if (!lid) {
		atomic_add(&B[0], scratch[lid]);
	}

}


//sort functions
#define intswap(A,B) {int temp=A;A=B;B=temp;}
kernel void OddEvenSort(global int * data, global int * sortedData)
{
	int id = get_global_id(0);
	int size = get_global_size(0);
	sortedData[id] = data[id];
	barrier(CLK_GLOBAL_MEM_FENCE);

	//odd pass
	for (int i = 1; i < size - 1; i++)
	{
		if (((i % 2) != 0) && ((id % 2) != 0))
		{
			if (sortedData[id] > sortedData[id + 1])
			{
				intswap(sortedData[id], sortedData[id + i]);
			}
			else
			{
				intswap(sortedData[id + 1], sortedData[id - 1]);
			}
		}
		barrier(CLK_GLOBAL_MEM_FENCE);

	}

	//even pass
	for (int i = 1; i < size - 1; i++)
	{
		if (((i % 2) == 0) && ((id % 2) == 0))
		{
			if (sortedData[id] > sortedData[id + 1])
			{
				intswap(sortedData[id], sortedData[id + i]);
			}
			else
			{
				intswap(sortedData[id + 1], sortedData[id - 1]);
			}
		}
		barrier(CLK_GLOBAL_MEM_FENCE);
	}
}

kernel void BubbleSort(global int* data, global int * sortedData)
{
	int id = get_global_id(0);
	int N = get_global_size(0);
	sortedData[id] = data[id];
	barrier(CLK_GLOBAL_MEM_FENCE);

	for (int i = 0; i < N; i += 2)
	{
		for (int j = 1; i < N - i; j++)
		{
			if (sortedData[j] > sortedData[j + 1])
			{
				intswap(sortedData[j], sortedData[j + 1]);
			}
			else
			{
				intswap(sortedData[j + 1], sortedData[j]);
			}
			barrier(CLK_GLOBAL_MEM_FENCE);
		}
	}
}



