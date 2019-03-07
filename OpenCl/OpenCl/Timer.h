#pragma once
#include <ctime>
#include <string>
#include <iostream>


namespace Timer
{
	

	clock_t timer;
	void StartTimer();
	void EndTimer(string name);

	void StartTimer()
	{
		timer = clock();
	}

	void EndTimer(string name)
	{
		timer = clock() - timer;
		std::cout << "------- " <<  name << " took " << (int)timer / CLOCKS_PER_SEC << " seconds, " << (timer) / (CLOCKS_PER_SEC/1000) <<  " Miliseconds" << std::endl;

	}

}
