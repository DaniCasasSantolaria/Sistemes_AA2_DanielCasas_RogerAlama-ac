#pragma once
#include <functional>

static class Timer {
public:
	typedef std::function<void()> AfterTimePassed;
	static void DelayExecute(unsigned long seconds, AfterTimePassed function);
};