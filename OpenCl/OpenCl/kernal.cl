

//works on small data set
kernel  void Min(global const int* data, global int* min)
{
	//perform any copying
	int id = get_global_id(0);
	int N = get_global_size(0);
	min[id] = data[id];
	barrier(CLK_GLOBAL_MEM_FENCE); 

	//reduce min
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
	//perform any copying
	int id = get_global_id(0);
	int N = get_global_size(0);
	barrier(CLK_GLOBAL_MEM_FENCE); 


	//reduce max
	for (int i = 0; i < N; i += 2) {
		if (!(id % (i * 2)) && ((id + i) < N))
			if (min[id] < min[id + i])
			{
				min[id] = min[id + i];
			}

		barrier(CLK_GLOBAL_MEM_FENCE);
	}
}

//Min for Large Dataset
kernel void MinL(global const int* data, global int* min, local int* scratch)
{
	//perform any copying
	int id = get_global_id(0);
	int N = get_local_size(0);
	int lid = get_local_id(0);

	scratch[lid] = data[id];
	barrier(CLK_LOCAL_MEM_FENCE);


	//reduce min
	for (int i = 1; i < N; i *= 2) {
		if (!(lid % (i * 2)) && ((lid + i) < N))
		{
			if (scratch[lid] > scratch[lid + i])
			{
				scratch[lid] = scratch[lid + i];
			}
		}

		barrier(CLK_LOCAL_MEM_FENCE);
	}
	
	//calculte min of local
	if (!lid)
	{
		atomic_min(&min[0], scratch[lid]);
	}
}

//Max for Large Dataset
kernel void MaxL(global const int* data, global int* min, local int* scratch)
{
	int id = get_global_id(0);
	int N = get_local_size(0);
	int lid = get_local_id(0);

	scratch[lid] = data[id];
	barrier(CLK_LOCAL_MEM_FENCE); 


	//reduce max
	for (int i = 1; i < N; i *= 2) {
		if (!(lid % (i * 2)) && ((lid + i) < N))
		{
			if (scratch[lid] < scratch[lid + i])
			{
				scratch[lid] = scratch[lid + i];
			}
		}

		barrier(CLK_LOCAL_MEM_FENCE);
	}

	//calculte max of local
	if (!lid)
	{
		atomic_max(&min[0], scratch[lid]);
	}
}

kernel void Sum(global const int* data, global int* sum, local int* scratch) 
{
//perform any copying
	int id = get_global_id(0);
	int lid = get_local_id(0);
	int N = get_local_size(0);
	scratch[lid] = data[id];
	barrier(CLK_LOCAL_MEM_FENCE);

	//reduce sum
	for (int i = 1; i < N; i *= 2) {
		if (!(lid % (i * 2)) && ((lid + i) < N))
			scratch[lid] += scratch[lid + i];

		barrier(CLK_LOCAL_MEM_FENCE);
	}

	
	//calculte sum of local
	if (!lid) {
		atomic_add(&sum[0], scratch[lid]);
	}

}

kernel void SubtractAndSq(global const int* data, global const int* value, global int* output)
{
	int id = get_global_id(0);
	output[id] = data[id]; //copy all values
	barrier(CLK_GLOBAL_MEM_FENCE); //sync threads


	output[id] -= value[0] ^ 2; //minus and sq
	
}

//sort functions - doesn't work
#define intswap(A,B) {int temp=A;A=B;B=temp;}
kernel void OddEvenSort(global int * data, global int * sortedData)
{
	int id = get_global_id(0);
	int size = get_global_size(0);
	sortedData[id] = data[id];
	barrier(CLK_GLOBAL_MEM_FENCE);


	
	for (int i = 0; i < size; i+=2)
	{
		if (id % 2 == 0 && id + 1 < size) //even pass
		{
			if (sortedData[id] > sortedData[id + 1])
			{
				intswap(sortedData[id], sortedData[id + 1]);
			}
		}

		barrier(CLK_GLOBAL_MEM_FENCE);

		if (id % 2 == 1 && id + 1 < size) //odd pass
		{
			if (sortedData[id] > sortedData[id + 1])
			{
				intswap(sortedData[id], sortedData[id + 1]);

			}
		}

		barrier(CLK_GLOBAL_MEM_FENCE);
	}
	
}








