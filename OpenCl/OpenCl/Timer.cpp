#include "pch.h"
#include "Timer.h"

namespace Timer
{
	using namespace std;

	void Timer::StartTimer()
	{
		Timer::timer = clock();
	}

	void Timer::EndTimer()
	{
		Timer:timer = clock() - Timer::timer;
		cout << (float)Timer::timer / CLOCKS_PER_SEC << "seconds"

	}
}
