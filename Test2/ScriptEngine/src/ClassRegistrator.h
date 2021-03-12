#pragma once

#include "ScriptEngine.h"
#include "../Engine/src/Helpers/vector3.h"
#include "../Engine/src/Helpers/mat3.h"

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
		static int Registration(sol::table* Lnamespace);
	private:
		static void Reg_GLMvec3(sol::table* Lnamespace);
		static void Reg_GLMvec2(sol::table* Lnamespace);
		static void Reg_GLMMat3(sol::table* Lnamespace);

		inline static bool IsReg = false;
	};
}