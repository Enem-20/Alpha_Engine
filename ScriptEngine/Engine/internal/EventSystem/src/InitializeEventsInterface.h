#pragma once

#ifndef INITIALIZEEVENTSINTERFACE
#define INITIALIZEEVENTSINTERFACE

#include <vector>
#include <functional>
#include <string>
#include <memory>

class InitializeEventsInterface {
public:
	InitializeEventsInterface(const std::vector<std::function<void()>>& onBeforeListeners, const std::vector<std::function<void()>>& onAfterListeners);

	/*template<class ClassType, class... Args>
	std::shared_ptr<ClassType> make(const std::vector<std::function<void()>>& onBeforeListeners, const std::vector<std::function<void()>>& onAfterListeners, Args... args);*/
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