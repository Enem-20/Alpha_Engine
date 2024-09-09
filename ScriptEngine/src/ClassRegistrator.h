#pragma once

#ifndef CLASSREGISTRATOR_H
#define CLASSREGISTRATOR_H

#include <sol/forward.hpp>

class GameObject;

#include "API/ExportPropety.h"


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
	static void Reg_UIelement(sol::table* UIElement);
	static void Reg_Window(sol::table* Lnamespace);
	static void Reg_WindowManager(sol::table* Lnamespace);
	static void Reg_Transform(sol::table* Lnamespace);
	static void Reg_GameObject(sol::table* object);
	static void Reg_Collider2D(sol::table* object);
	static void Reg_Mesh(sol::table* object);
	static void Reg_LuaScript(sol::table* object);

	static void Reg_Timer(sol::table* Lnamespace);
	static void Reg_Hierarchy(sol::table* hierarchy);
	static void Reg_ResourceManager(sol::table* Lnamespace);
	static void Reg_Input(sol::table* Lnamespace);
	static void Reg_StringFuncs(sol::table* Lnamespace);
	static void Reg_Casts(sol::table* Lnamespace);
	static void Reg_Raycast(sol::table* Lnamespace);


	inline static bool IsReg = false;
};

#endif