#pragma once

#include "ExportProperty.h"

namespace ScriptEngine
{
	class DLLEXPORT ScriptProcessor
	{
	public:
		//ScriptProcessor();
		static void init(char** argv);
		static void FirstFrame();
		static void render();

		static void Awake();
		static void Start();
		static void Update();
		static void FixedUpdate();
		static void LastUpdate();

		static void ScriptUpdates();
	};
}