#include "Component.h"

namespace Components
{
	GameObject& Component::GetGameObject() const
	{
		return *Hierarchy::getObject(name);
	}
}