#pragma once

#ifndef LUA_SCRIPT_H
#define LUA_SCRIPT_H

#include "API/ExportPropety.h"

#include "Script.h"
#include "Component.h"

#include <sol/sol.hpp>
#include <string>

class GameObject;

class DLLEXPORT LuaScript : public Component, public Script
{
public:
	LuaScript(sol::protected_function& Awake, sol::protected_function& Start, sol::protected_function& Update, sol::protected_function& FixedUpdate, sol::protected_function& LastUpdate);
	LuaScript(std::string_view name, std::string_view path, std::shared_ptr<sol::state> L, std::shared_ptr<GameObject> gameObject = nullptr);
	LuaScript(LuaScript&& script) noexcept;
	LuaScript(const LuaScript& script);
	void SetAwake(const sol::protected_function& Awake);
	void SetStart(const sol::protected_function& Start);
	void SetUpdate(const sol::protected_function& Update);
	void SetFixedUpdate(const sol::protected_function& FixedUpdate);
	void SetLastUpdate(const sol::protected_function& LastUpdate);

	void LoadScript(std::shared_ptr<sol::state> L);

	void Awake();
	void Start();
	void Update(uint32_t currentFrame);
	void FixedUpdate();
	void LastUpdate();

	std::string m_path;
	GENERATETYPE(LuaScript)
private:
	sol::protected_function m_Awake;
	sol::protected_function m_Start;
	sol::protected_function m_Update;
	sol::protected_function m_FixedUpdate;
	sol::protected_function m_LastUpdate;
};
#endif //LUASCRIPT