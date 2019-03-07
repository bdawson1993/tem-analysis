#pragma once
#include <ctime>
#include <string>
#include <iostream>


namespace Timer
{
	using namespace std;

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
		cout << "------- " <<  name << " took " << (int)timer / CLOCKS_PER_SEC << " seconds, " << (timer) / (CLOCKS_PER_SEC/1000) <<  " Miliseconds" << endl;

	}

}
