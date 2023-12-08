#pragma once

#ifndef DEPENDENCY_LIST
#define DEPENDENCY_LIST

#define STRING_TO_TYPE(x) (##x)

#include <array>
#include <string>
#include <tuple>
#include <span>

template<class ...Args>
class DependencyList {
protected:
	DependencyList(std::span<std::string> dependencies_names)
		: dependencies_names(dependencies_names)
	{
		inject();
	}
	virtual ~DependencyList(){}
	virtual void inject() = 0;

	std::span<std::string> dependencies_names;
};

#endif