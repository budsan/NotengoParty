#include "Game.h"

void Game::Init(Engine* engine)
{
	
}

void Game::Update(Engine* engine)
{
	Renderer_ImGui_NewFrame(engine);
}

void Game::Render(Engine* engine)
{
	Renderer_Clear(engine, 0, 0, 0, 255);
	ImGui::Render();
	Renderer_Present(engine);
}

void Game::Quit(Engine* engine)
{
	
}



