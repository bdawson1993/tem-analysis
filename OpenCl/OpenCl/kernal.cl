kernel  void Min(global const int* data, global int* min)
{
	//Reduction on local
	int id = get_global_id(0);
	int N = get_global_size(0);


	min[id] = data[id];

	barrier(CLK_GLOBAL_MEM_FENCE); //wait for all threads to init and copy


	//calculate stride lengths so all data is calculted
	for (int i = 0; i < N; i += 2) {
		if (!(id % (i * 2)) && ((id + i) < N))
			if (min[id] > min[id + i])
			{
				min[id] = min[id + i];
			}

		barrier(CLK_GLOBAL_MEM_FENCE);
	}
}

//reduce using local memory (so called privatisation)
kernel void Max(global const int* A, global int* B, local int* scratch) {
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

	//we add results from all local groups to the first element of the array
	//serial operation! but works for any group size
	//copy the cache to output array
	if (!lid)
	{
		B[0] += scratch[lid];
	}



	//if (!lid) {
	//	atomic_add(&B[0], scratch[lid]);
	//}

}

kernel void Sum(global int* data, global int* sum)
{

}

#define intswap(A,B) {int temp=A;A=B;B=temp;}
kernel void Sort(global int* data, global int* sortedData)
{
	int id = get_global_id(0);
	int size = get_global_size(0);
	barrier(CLK_GLOBAL_MEM_FENCE);


	for (int i = 1; i < size; i++)
	{

		if ((i % 2 != 0) && (data[i] > data[i + 1]))
		{
			intswap(data[i], data[i + 1])
		}

		barrier(CLK_GLOBAL_MEM_FENCE);
		if ((i % 2 == 0) && (data[i] > data[i + 1]))
		{
			intswap(data[i], data[i + 1])
		}
	}


	//block and write results
	barrier(CLK_GLOBAL_MEM_FENCE);
	sortedData[id] = data[id];

}
	


