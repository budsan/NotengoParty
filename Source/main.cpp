#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Core/Engine.h"
#include "Game.h"

#define FIXED_TIMESTEP	16

int main(int argc, char* argv[])
{
	Engine engine;
	engine.Init("NotengoParty", 800, 600);

	Game game;
	game.Init(&engine);

	uint32_t last_time = System_Ticks();

	uint16_t frames_rendered = 0;
	uint16_t fps_counter = 60;
	uint16_t timer_onesec = 0;

	while (engine.IsRunning())
	{
		uint32_t current_time = System_Ticks();
		engine.delta_time = FIXED_TIMESTEP;
		engine.running_time += engine.delta_time;
		last_time = current_time;
		timer_onesec += engine.delta_time;
		if (timer_onesec > 1000) //It's a feature
		{
			timer_onesec -= 1000;
			fps_counter = frames_rendered;
			frames_rendered = 0;
		}

		static char window_title[64];
		sprintf_s(window_title, "NotengoParty | %d FPS | %d ms", fps_counter, engine.delta_time);
		Window_SetTitle(&engine, window_title);

		engine.Update();
		game.Update(&engine);

		game.Render(&engine);
		frames_rendered++;
		uint32_t wait_time = current_time + FIXED_TIMESTEP;
		while (!SYS_TICKS_PASSED(System_Ticks(), wait_time))
		{
			uint32_t time_left = wait_time - System_Ticks();
			if ((time_left) > 2 && (time_left < 15))
			{
				System_Sleep(time_left);
			}
		}
	}

	game.Quit(&engine);
	engine.Quit();

	return 0;
}
