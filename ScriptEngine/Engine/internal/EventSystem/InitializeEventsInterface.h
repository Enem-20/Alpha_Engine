#pragma once

#ifndef INITIALIZE_EVENTS_INTERFACE_Р
#define INITIALIZE_EVENTS_INTERFACE_Р

#include "API/ExportPropety.h"

#include <vector>
#include <functional>
#include <string>
#include <memory>

class DLLEXPORT InitializeEventsInterface {
public:
	InitializeEventsInterface(const std::vector<std::function<void()>>& onBeforeListeners, const std::vector<std::function<void()>>& onAfterListeners);
protected:
	virtual void OnBeforeInitialize();
	virtual void OnAfterInitialize();
	virtual void addOnBeforeInitializeListener(const std::function<void()>& listener);
	virtual void addOnAfterInitializeListener(const std::function<void()>& listener);
private:
	std::vector<std::function<void()>> OnBeforeInitializelisteners;
	std::vector<std::function<void()>> OnAfterInitializelisteners;
};

#endif