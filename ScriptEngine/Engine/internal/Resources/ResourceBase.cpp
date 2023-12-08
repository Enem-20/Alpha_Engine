#include "ResourceBase.h"

#include "ResourceManager.h"

//template<class Derived>
ResourceBase/*<Derived>*/::ResourceBase(std::string_view name/*, Derived* whatShouldBeStored*/)
	: name(name)
{
	/*ResourceManager::addResource<Derived>(whatShouldBeStored);
	derived = ResourceManager::getResource(name);*/
}

//template<class Derived>
ResourceBase/*<Derived>*/::~ResourceBase() {
	/*ResourceManager::removeResource<Derived>(name);*/
}
