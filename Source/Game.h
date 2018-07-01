#pragma once

#include "Core/Engine.h"
#include "Core/File.h"

#include "System.h"
#include "System_Manager.h"
#include "System_DebugController.h"

struct Game
{
	System_Manager _systemManager;
	System_DebugController _systemDebugController;	

	ImDrawList* _gameDrawList;
	ImDrawList* _cmdLists[2];

	void Init(Engine* engine);
	void Update(Engine* engine);
	void Render(Engine* engine);
	void Quit(Engine* engine);
};