#pragma once

#include "ScriptEngine.h"
#include "../Engine/src/Helpers/vector3.h"
#include "../Engine/src/Helpers/mat3.h"
#include "../Engine/src/Renderer/Texture2D.h"

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
		static void Reg_GLMvec2(sol::table* Lnamespace);
		static void Reg_GLMivec2(sol::table* Lnamespace);
		static void Reg_GLMvec3(sol::table* Lnamespace);
		static void Reg_GLMvec4(sol::table* Lnamespace);

		static void Reg_GLMMat3(sol::table* Lnamespace);
		static void Reg_GLMMat4(sol::table* Lnamespace);

		static void Reg_ShaderProgram(sol::table* same);
		static void Reg_SubTexture2D(sol::table* LTexture2D);
		static void Reg_Texture2D(sol::table* same);
		static void Reg_Sprite(sol::table* object);
		static void Reg_GObject(sol::table* object);

		inline static bool IsReg = false;
	};
}