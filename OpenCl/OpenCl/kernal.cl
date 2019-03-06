kernel  void Min(global int* data, global int* min)
{
	int id = get_global_id(0);
	int N = get_global_size(0);

	min[id] = data[id];

	barrier(CLK_GLOBAL_MEM_FENCE); //wait for all threads to init and copy


	//calculate stride lengths so all data is calculted
	for (int i = 1; i < N; i *= 2) { 
		if (!(id % (i * 2)) && ((id + i) < N))
			if (min[id] > min[id + i])
			{
				min[id] = min[id + i];
			}

		barrier(CLK_GLOBAL_MEM_FENCE);
	}
}

kernel void Max(global int* data, global int* max)
{
	
}

kernel void Sum(global int* A, global int* B)
{
	int id = get_global_id(0);
	int N = get_global_size(0);

	B[id] = A[id];

	barrier(CLK_GLOBAL_MEM_FENCE);

	for (int i = 1; i < N; i += 2) { //i is a stride
		if (!(id % (i * 2)) && ((id + 1) < N))
			B[id] += B[id + 1];
		barrier(CLK_GLOBAL_MEM_FENCE);
	}
}


kernel void Sort(global int* data, global int* sortedData)
{

}


