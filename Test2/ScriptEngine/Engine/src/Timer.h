#pragma once

#include <ctime>

class Timer
{
public:
	Timer() { isStart = false; start = 0; end = 0; }
	int GetTimeSec() { return clock() / CLK_TCK; }
	int GetDeltaUpdateSec() { return (UpdateEnd - UpdateStart) / CLK_TCK; }
	int GetDelta() { return (end - start) / CLK_TCK; }
	int GetStart() { return start / CLK_TCK; }
	int GetEnd() { return end / CLK_TCK; }
	void StartUpdateTimer() { UpdateStart = clock() / CLK_TCK;  }
	void EndUpdateTimer() { UpdateStart = clock() / CLK_TCK; }
	void StartTimer() { start = clock(); isStart = true; }
	void EndTimer() { end = 0; isStart = false; }
	bool IsStart() { return isStart; }
private:
	int start;
	int end;
	int UpdateStart;
	int UpdateEnd;
	bool isStart;
};