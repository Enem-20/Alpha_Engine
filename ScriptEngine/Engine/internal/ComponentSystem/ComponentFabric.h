#pragma once

#ifndef COMPONENTFABRIC
#define COMPONENTFABRIC

#include "Component.h"
#include "../../UI/src/UIelement.h"
#include "../../UI/src/Button.h"

class ComponentFabric {
public:
	template<class ComponentType>
	static ComponentType& makeComponentFrom(ComponentType* componentType) {
		auto comp = ComponentView{reinterpret_cast<void*>(componentType)};

		return comp.getComponentFromView();
	}
};

#endif //COMPONENTFABRIC