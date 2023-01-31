#pragma once

#include "API/ExportProperty.h"

#include <sol/sol.hpp>
#include <memory>

class Timer;


class ClassRegistrator;

class DLLEXPORT ScriptProcessor
{
public:
	//ScriptProcessor();
	static sol::state& getL();
	static void init(char** argv);
	static void FirstFrame();
	static void render();

	static void Awake();
	static void Start();
	static void Update();
	static void FixedUpdate();
	static void LastUpdate();

	static void ScriptUpdates();
	static std::shared_ptr<Timer>& GeneralTimer();
private:
	static std::shared_ptr<Timer> GenTimer;
	static std::shared_ptr<sol::state> L;
};
