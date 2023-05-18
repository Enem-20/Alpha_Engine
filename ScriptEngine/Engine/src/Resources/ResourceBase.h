#pragma once

#ifndef RESOURCEBASE
#define RESOURCEBASE

#include <string>
#include <memory>

#define GETTYPE(ClassName) #ClassName;
#define GENERATETYPE(ClassName) inline static const std::string type = #ClassName;

class ResourceBase {
public:
	ResourceBase() = delete;
	ResourceBase(const std::string& name);
	ResourceBase(const ResourceBase& resourceBase);
	ResourceBase(ResourceBase&& resourceBase) noexcept;

	std::string name;
};

#endif