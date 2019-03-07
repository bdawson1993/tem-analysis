kernel  void Min(global const int* data, global int* min)
{
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

kernel void Max(global int* data, global int* max)
{
	
}

kernel void Sum(global int* data, global int* sum)
{
	
}


kernel void Sort(global int* data, global int* sortedData)
{

}


