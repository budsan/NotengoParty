#ifdef DX11_IMPL

#include "Engine.h"
#include "Input.h"
#include "LightVector.h"

void Input_SetRelativeMouseMode(Engine* engine, int mode)
{
}

Keyboard Input_GetKeyboard(Engine* engine)
{
	static Keyboard keyboard { nullptr };
	return keyboard;
}

bool Input_IsKeyPressed(Keyboard keyboard, Keyboard::Key key)
{
	return false;
}

struct tMouseImpl
{
	int32_t x;
	int32_t y;
	uint32_t state;
};

tMouseImpl s_mouseImpl;

void Input_ShowCursor(bool enable)
{
}

Mouse Input_GetMouse(Engine* engine)
{
	static Mouse mouse { nullptr };
	return mouse;
}

void Input_GetPosition(Mouse mouse, int32_t* x, int32_t* y)
{
}

bool Input_IsButtonPressed(Mouse mouse, Mouse::Button button)
{
	return false;
}

void Input_SetControllerCallbacks(Input_ControllerCallbacks callbacks)
{
}

uint16_t Input_GetControllerInfoCount()
{
	return 0;
}

const ControllerInfo* Input_GetControllerInfo(uint16_t Id)
{
	return nullptr;
}

const ControllerState* Input_GetControllerState(uint16_t Id)
{
	return nullptr;
}

#endif
