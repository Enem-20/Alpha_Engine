#pragma once

#ifndef COMPONENT_FABRIC_H
#define COMPONENT_FABRIC_H

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