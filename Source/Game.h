#pragma once

#include "Core/Engine.h"

struct Game
{
	uint32_t dummy;

	void Init(Engine* engine);
	void Update(Engine* engine);
	void Render(Engine* engine);
	void Quit(Engine* engine);
};