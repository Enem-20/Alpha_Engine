#include "InitializeEventsInterface.h"

InitializeEventsInterface::InitializeEventsInterface(const std::vector<std::function<void()>>& onBeforeListeners, const std::vector<std::function<void()>>& onAfterListeners)
	: OnBeforeInitializelisteners(onBeforeListeners)
	, OnAfterInitializelisteners(onAfterListeners)
{}

void InitializeEventsInterface::OnBeforeInitialize() {
	for (auto it : OnBeforeInitializelisteners) {
		it();
	}
	OnBeforeInitializelisteners.clear();
}

void InitializeEventsInterface::OnAfterInitialize() {
	for (auto it : OnAfterInitializelisteners) {
		it();
	}
	OnAfterInitializelisteners.clear();
}

void InitializeEventsInterface::addOnBeforeInitializeListener(const std::function<void()>& listener) {
	OnBeforeInitializelisteners.push_back(listener);
}

void InitializeEventsInterface::addOnAfterInitializeListener(const std::function<void()>& listener) {
	OnAfterInitializelisteners.push_back(listener);
}