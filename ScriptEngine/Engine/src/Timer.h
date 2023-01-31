#pragma once

#include "ExportPropety.h"

#include <ctime>

class DLLEXPORT Timer
{
public:
	Timer();
	int GetTimeSec() const;
	int GetDeltaUpdateSec() const;
	int GetDelta() const;
	int GetStart() const;
	int GetEnd() const;
	void StartUpdateTimer();
	void EndUpdateTimer();
	void StartTimer();
	void EndTimer();
	bool IsStart() const;
private:
	int start;
	int end;
	int UpdateStart;
	int UpdateEnd;
	bool isStart;
};