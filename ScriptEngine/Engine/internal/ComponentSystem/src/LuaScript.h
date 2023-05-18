#pragma once

#ifndef LUASCRIPT
#define LUASCRIPT

#include "Script.h"
#include "Component.h"

#include <sol/sol.hpp>
#include <string>

class GameObject;

class LuaScript : public Component, public Script
{
public:
	LuaScript(sol::protected_function& Awake, sol::protected_function& Start, sol::protected_function& Update, sol::protected_function& FixedUpdate, sol::protected_function& LastUpdate);
	LuaScript(std::string name, std::string path, std::shared_ptr<sol::state> L = nullptr, std::shared_ptr<GameObject> gameObject = nullptr);
	LuaScript(LuaScript&& script) noexcept;
	LuaScript(const LuaScript& script);
	void SetAwake(const sol::protected_function& Awake);
	void SetStart(const sol::protected_function& Start);
	void SetUpdate(const sol::protected_function& Update);
	void SetFixedUpdate(const sol::protected_function& FixedUpdate);
	void SetLastUpdate(const sol::protected_function& LastUpdate);

	void LoadScript(std::shared_ptr<sol::state> L);

	void Awake() override;
	void Start() override;
	void Update(uint32_t currentImage) override;
	void FixedUpdate() override;
	void LastUpdate() override;

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