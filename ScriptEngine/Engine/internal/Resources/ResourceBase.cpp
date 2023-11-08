#include "ResourceBase.h"



ResourceBase::ResourceBase(const std::string& name) 
	: name(name)
{}
ResourceBase::ResourceBase(const ResourceBase& resourceBase) 
	: name(resourceBase.name)
{}
ResourceBase::ResourceBase(ResourceBase&& resourceBase) noexcept 
	: name(std::move(resourceBase.name))
{}