#include "ClassRegistrator.h"

#include <typeinfo>

namespace ScriptEngine
{
	void ClassRegistrator::Reg(std::shared_ptr<GObject> object/*, sol::table Lobject*/)
	{
		Reg(object->position);
		sol::usertype<std::shared_ptr<GObject>> usertype_table = ScriptProcessor::L.new_usertype<std::shared_ptr<GObject>>("GObject",
			"Constructor", sol::constructors<GObject()>(),
			"Translate", &GObject::Translate,
			"Rotate", &GObject::Rotate,
			"render", &GObject::render,
			"sprite", sol::property(&GObject::GetSprite, &GObject::SetSprite),
			"position", &GObject::Position,
			"cellposition", &GObject::CellPosition
			);
		//ScriptProcessor::L["object_test"] = object;
	}
	//
	//	void ClassRegistrator::Reg(std::shared_ptr<RenderEngine::Sprite> sprite, sol::table Lsprite)
	//	{
	//		
	//	}
	//
	void ClassRegistrator::Reg(glm::vec3 _vec3, sol::table* Lvec3)
	{
		*Lvec3 = ScriptProcessor::L[typeid(glm::vec3).name()].get_or_create<sol::table>();
		Lvec3->new_usertype <glm::vec3>(" vec3",
			sol::constructors <glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
			"x", &glm::vec3::x,
			"y", &glm::vec3::y,
			"z", &glm::vec3::z
			//"__add", GLMAddVecFunc <glm::vec2, float >(),
			//"__sub", GLMSubVecFunc <glm::vec2, float >(),
			//"__mul", GLMMulVecFunc <glm::vec2, float >(),
			//"__div", GLMDivVecFunc <glm::vec2, float >(),
			//"__tostring", GLMToStringFunc <glm::vec2>()
			);
	}
}