#pragma once

#include "../../../src/ScriptEngine.h"
#include "Component.h"

#include <sol/sol.hpp>

class GameObject;

namespace Components
{
	class LuaScript : public Component
	{
	public:
		LuaScript(sol::protected_function& Awake, sol::protected_function& Start, sol::protected_function& Update, sol::protected_function& FixedUpdate, sol::protected_function& LastUpdate);
		LuaScript(std::string name, std::string path, std::shared_ptr<GameObject> gameObject = nullptr);
		void SetAwake(sol::protected_function& Awake);
		void SetStart(sol::protected_function& Start);
		void SetUpdate(sol::protected_function& Update);
		void SetFixedUpdate(sol::protected_function& FixedUpdate);
		void SetLastUpdate(sol::protected_function& LastUpdate);

		void LoadScript();

		void Awake() { m_Awake(); }
		void Start() { m_Start(); }
		void Update(){m_Update();}
		void FixedUpdate() { m_FixedUpdate(); }
		void LastUpdate() { m_LastUpdate(); }

		std::string m_path;
	private:
		sol::protected_function m_Awake;
		sol::protected_function m_Start;
		sol::protected_function m_Update;
		sol::protected_function m_FixedUpdate;
		sol::protected_function m_LastUpdate;
	};
}