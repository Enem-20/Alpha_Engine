#include "Timer.h"

	Timer::Timer() { UpdateEnd = 0; UpdateStart = 0; isStart = false; start = 0; end = 0; }
	int Timer::GetTimeSec() const{ return clock() / CLK_TCK; }
	int Timer::GetDeltaUpdateSec() const{ return (UpdateEnd - UpdateStart) / CLK_TCK; }
	int Timer::GetDelta() const{ return (end - start) / CLK_TCK; }
	int Timer::GetStart() const{ return start / CLK_TCK; }
	int Timer::GetEnd() const{ return end / CLK_TCK; }
	void Timer::StartUpdateTimer() { UpdateStart = clock() / CLK_TCK;  }
	void Timer::EndUpdateTimer() { UpdateStart = clock() / CLK_TCK; }
	void Timer::StartTimer() { start = clock(); isStart = true; }
	void Timer::EndTimer() { end = 0; isStart = false; }
	bool Timer::IsStart() const { return isStart; }