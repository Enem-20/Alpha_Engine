#pragma once

#include "ScriptEngine.h"

namespace ScriptEngine
{
	class ClassRegistrator
	{
	public:
		ClassRegistrator() = delete;
		ClassRegistrator(ClassRegistrator&&) = delete;
		ClassRegistrator(const ClassRegistrator&) = delete;
		~ClassRegistrator() = delete;
		ClassRegistrator& operator=(const ClassRegistrator&) = delete;
	public:
		template<class T>
		static void Registration(T object, std::string name);
	private:
		static void Reg(std::shared_ptr<GObject> object/*, sol::table Lobject*/);
		static void Reg(std::shared_ptr<RenderEngine::Sprite> sprite, sol::table Lsprite);
		static void Reg(glm::vec3 _vec3, sol::table* Lvec3 = nullptr);
	};

	template<class T>
	void ClassRegistrator::Registration(T object, std::string name)
	{
		//sol::table Lobject = ScriptProcessor::L[name].get_or_create<sol::table>();
		if (typeid(T).name() == "class std::shared_ptr<GObject>")
		{
			Reg(object/*, Lobject*/);
		}
	}
}