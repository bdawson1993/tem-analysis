kernel  void Min(global int* data, global int* min)
{
	int id = get_global_id(0);
	int N = get_global_size(0);

	min[id] = data[id];

	barrier(CLK_GLOBAL_MEM_FENCE); //wait for all threads to init


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


