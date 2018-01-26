#pragma once

#include "Core/Engine.h"
#include "Core/File.h"

#include "DebugController.h"

struct Game
{
	DebugController _debugController;

	ImDrawList* _gameDrawList;
	ImDrawList* _cmdLists[2];

	void Init(Engine* engine);
	void Update(Engine* engine);
	void Render(Engine* engine);
	void Quit(Engine* engine);
};