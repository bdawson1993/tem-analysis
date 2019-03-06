kernel  void Max(global int* A)
{
	int id = get_local_id(0);
	int N = get_local_size(0);


	for (int stride = 1; stride < N; stride *= 2)
	{
		if ((id % (stride * 2) == 0))
			if (A[id] > A[id] + stride)
			{
				A[id] = A[id + stride];
			}
			else
			{
				A[id + stride] = A[id];
			}
			

			barrier(CLK_GLOBAL_MEM_FENCE);
	}



}