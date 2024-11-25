#include "Timer.h"
#include <thread>
#include <Windows.h>

void Timer::DelayExecute(unsigned long miliseconds, AfterTimePassed function) {
	std::thread* delayExecute = new std::thread(function);
	Sleep(miliseconds);
	delayExecute->detach();
}