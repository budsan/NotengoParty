#if defined(SDL_IMPL)

#include "Engine.h"
#include "Input.h"
#include "LightVector.h"

#include <SDL.h>

void Input_SetRelativeMouseMode(Engine* engine, int mode)
{
	SDL_SetRelativeMouseMode(mode != INPUT_DISABLE ? SDL_TRUE : SDL_FALSE);
}

tKeyboard Input_GetKeyboard(Engine* engine)
{
	tKeyboard keyboard;
	keyboard.impl = (tKeyboard::KeyboardImpl) SDL_GetKeyboardState(NULL);

	return keyboard;
}

SDL_Keycode KeyboardKeyToSDLKey(tKeyboard::Key _key)
{
	SDL_Keycode key;
	switch (_key)
	{
	case tKeyboard::Key_LShift:    key = SDLK_LSHIFT; break;
	case tKeyboard::Key_RShift:    key = SDLK_RSHIFT; break;
	case tKeyboard::Key_LControl:  key = SDLK_LCTRL; break;
	case tKeyboard::Key_RControl:  key = SDLK_RCTRL; break;
	case tKeyboard::Key_LAlt:      key = SDLK_LALT; break;
	case tKeyboard::Key_RAlt:      key = SDLK_RALT; break;
	case tKeyboard::Key_LSystem:   key = SDLK_LGUI; break;
	case tKeyboard::Key_RSystem:   key = SDLK_RGUI; break;
	case tKeyboard::Key_Menu:      key = SDLK_MENU; break;
	case tKeyboard::Key_Escape:    key = SDLK_ESCAPE; break;
	case tKeyboard::Key_SemiColon: key = SDLK_SEMICOLON; break;
	case tKeyboard::Key_Slash:     key = SDLK_SLASH; break;
	case tKeyboard::Key_Equal:     key = SDLK_EQUALS; break;
	case tKeyboard::Key_Dash:      key = SDLK_MINUS; break;
	case tKeyboard::Key_LBracket:  key = SDLK_LEFTBRACKET; break;
	case tKeyboard::Key_RBracket:  key = SDLK_RIGHTBRACKET; break;
	case tKeyboard::Key_Comma:     key = SDLK_COMMA; break;
	case tKeyboard::Key_Period:    key = SDLK_PERIOD; break;
	case tKeyboard::Key_Quote:     key = SDLK_QUOTE; break;
	case tKeyboard::Key_BackSlash: key = SDLK_BACKSLASH; break;
	case tKeyboard::Key_Space:     key = SDLK_SPACE; break;
	case tKeyboard::Key_Return:    key = SDLK_RETURN; break;
	case tKeyboard::Key_BackSpace: key = SDLK_BACKSPACE; break;
	case tKeyboard::Key_Tab:       key = SDLK_TAB; break;
	case tKeyboard::Key_PageUp:    key = SDLK_PAGEUP; break;
	case tKeyboard::Key_PageDown:  key = SDLK_PAGEDOWN; break;
	case tKeyboard::Key_End:       key = SDLK_END; break;
	case tKeyboard::Key_Home:      key = SDLK_HOME; break;
	case tKeyboard::Key_Insert:    key = SDLK_INSERT; break;
	case tKeyboard::Key_Delete:    key = SDLK_DELETE; break;
	case tKeyboard::Key_Add:       key = SDLK_KP_PLUS; break;
	case tKeyboard::Key_Subtract:  key = SDLK_KP_MINUS; break;
	case tKeyboard::Key_Multiply:  key = SDLK_KP_MULTIPLY; break;
	case tKeyboard::Key_Divide:    key = SDLK_KP_DIVIDE; break;
	case tKeyboard::Key_Pause:     key = SDLK_PAUSE; break;
	case tKeyboard::Key_F1:        key = SDLK_F1; break;
	case tKeyboard::Key_F2:        key = SDLK_F2; break;
	case tKeyboard::Key_F3:        key = SDLK_F3; break;
	case tKeyboard::Key_F4:        key = SDLK_F4; break;
	case tKeyboard::Key_F5:        key = SDLK_F5; break;
	case tKeyboard::Key_F6:        key = SDLK_F6; break;
	case tKeyboard::Key_F7:        key = SDLK_F7; break;
	case tKeyboard::Key_F8:        key = SDLK_F8; break;
	case tKeyboard::Key_F9:        key = SDLK_F9; break;
	case tKeyboard::Key_F10:       key = SDLK_F10; break;
	case tKeyboard::Key_F11:       key = SDLK_F11; break;
	case tKeyboard::Key_F12:       key = SDLK_F12; break;
	case tKeyboard::Key_F13:       key = SDLK_F13; break;
	case tKeyboard::Key_F14:       key = SDLK_F14; break;
	case tKeyboard::Key_F15:       key = SDLK_F15; break;
	case tKeyboard::Key_Left:      key = SDLK_LEFT; break;
	case tKeyboard::Key_Right:     key = SDLK_RIGHT; break;
	case tKeyboard::Key_Up:        key = SDLK_UP; break;
	case tKeyboard::Key_Down:      key = SDLK_DOWN; break;
	case tKeyboard::Key_Numpad0:   key = SDLK_KP_0; break;
	case tKeyboard::Key_Numpad1:   key = SDLK_KP_1; break;
	case tKeyboard::Key_Numpad2:   key = SDLK_KP_2; break;
	case tKeyboard::Key_Numpad3:   key = SDLK_KP_3; break;
	case tKeyboard::Key_Numpad4:   key = SDLK_KP_4; break;
	case tKeyboard::Key_Numpad5:   key = SDLK_KP_5; break;
	case tKeyboard::Key_Numpad6:   key = SDLK_KP_6; break;
	case tKeyboard::Key_Numpad7:   key = SDLK_KP_7; break;
	case tKeyboard::Key_Numpad8:   key = SDLK_KP_8; break;
	case tKeyboard::Key_Numpad9:   key = SDLK_KP_9; break;
	case tKeyboard::Key_Q:         key = SDLK_q; break;
	case tKeyboard::Key_W:         key = SDLK_w; break;
	case tKeyboard::Key_E:         key = SDLK_e; break;
	case tKeyboard::Key_R:         key = SDLK_r; break;
	case tKeyboard::Key_T:         key = SDLK_t; break;
	case tKeyboard::Key_Y:         key = SDLK_y; break;
	case tKeyboard::Key_U:         key = SDLK_u; break;
	case tKeyboard::Key_I:         key = SDLK_i; break;
	case tKeyboard::Key_O:         key = SDLK_o; break;
	case tKeyboard::Key_P:         key = SDLK_p; break;
	case tKeyboard::Key_A:         key = SDLK_a; break;
	case tKeyboard::Key_S:         key = SDLK_s; break;
	case tKeyboard::Key_D:         key = SDLK_d; break;
	case tKeyboard::Key_F:         key = SDLK_f; break;
	case tKeyboard::Key_G:         key = SDLK_g; break;
	case tKeyboard::Key_H:         key = SDLK_h; break;
	case tKeyboard::Key_J:         key = SDLK_j; break;
	case tKeyboard::Key_K:         key = SDLK_k; break;
	case tKeyboard::Key_L:         key = SDLK_l; break;
	case tKeyboard::Key_Z:         key = SDLK_z; break;
	case tKeyboard::Key_X:         key = SDLK_x; break;
	case tKeyboard::Key_C:         key = SDLK_c; break;
	case tKeyboard::Key_V:         key = SDLK_v; break;
	case tKeyboard::Key_B:         key = SDLK_b; break;
	case tKeyboard::Key_N:         key = SDLK_n; break;
	case tKeyboard::Key_M:         key = SDLK_m; break;
	case tKeyboard::Key_Num0:      key = SDLK_0; break;
	case tKeyboard::Key_Num1:      key = SDLK_1; break;
	case tKeyboard::Key_Num2:      key = SDLK_2; break;
	case tKeyboard::Key_Num3:      key = SDLK_3; break;
	case tKeyboard::Key_Num4:      key = SDLK_4; break;
	case tKeyboard::Key_Num5:      key = SDLK_5; break;
	case tKeyboard::Key_Num6:      key = SDLK_6; break;
	case tKeyboard::Key_Num7:      key = SDLK_7; break;
	case tKeyboard::Key_Num8:      key = SDLK_8; break;
	case tKeyboard::Key_Num9:      key = SDLK_9; break;
	default:                       key = SDLK_UNKNOWN; break;
	}

	return key;
}

SDL_Keycode KeyboardKeyToSDLScancodeKey(tKeyboard::Key _key)
{
	SDL_Keycode key;
	switch (_key)
	{
	case tKeyboard::Key_LShift:    key = SDL_SCANCODE_LSHIFT; break;
	case tKeyboard::Key_RShift:    key = SDL_SCANCODE_RSHIFT; break;
	case tKeyboard::Key_LControl:  key = SDL_SCANCODE_LCTRL; break;
	case tKeyboard::Key_RControl:  key = SDL_SCANCODE_RCTRL; break;
	case tKeyboard::Key_LAlt:      key = SDL_SCANCODE_LALT; break;
	case tKeyboard::Key_RAlt:      key = SDL_SCANCODE_RALT; break;
	case tKeyboard::Key_LSystem:   key = SDL_SCANCODE_LGUI; break;
	case tKeyboard::Key_RSystem:   key = SDL_SCANCODE_RGUI; break;
	case tKeyboard::Key_Menu:      key = SDL_SCANCODE_MENU; break;
	case tKeyboard::Key_Escape:    key = SDL_SCANCODE_ESCAPE; break;
	case tKeyboard::Key_SemiColon: key = SDL_SCANCODE_SEMICOLON; break;
	case tKeyboard::Key_Slash:     key = SDL_SCANCODE_SLASH; break;
	case tKeyboard::Key_Equal:     key = SDL_SCANCODE_EQUALS; break;
	case tKeyboard::Key_Dash:      key = SDL_SCANCODE_MINUS; break;
	case tKeyboard::Key_LBracket:  key = SDL_SCANCODE_LEFTBRACKET; break;
	case tKeyboard::Key_RBracket:  key = SDL_SCANCODE_RIGHTBRACKET; break;
	case tKeyboard::Key_Comma:     key = SDL_SCANCODE_COMMA; break;
	case tKeyboard::Key_Period:    key = SDL_SCANCODE_PERIOD; break;
	case tKeyboard::Key_BackSlash: key = SDL_SCANCODE_BACKSLASH; break;
	case tKeyboard::Key_Space:     key = SDL_SCANCODE_SPACE; break;
	case tKeyboard::Key_Return:    key = SDL_SCANCODE_RETURN; break;
	case tKeyboard::Key_BackSpace: key = SDL_SCANCODE_BACKSPACE; break;
	case tKeyboard::Key_Tab:       key = SDL_SCANCODE_TAB; break;
	case tKeyboard::Key_PageUp:    key = SDL_SCANCODE_PAGEUP; break;
	case tKeyboard::Key_PageDown:  key = SDL_SCANCODE_PAGEDOWN; break;
	case tKeyboard::Key_End:       key = SDL_SCANCODE_END; break;
	case tKeyboard::Key_Home:      key = SDL_SCANCODE_HOME; break;
	case tKeyboard::Key_Insert:    key = SDL_SCANCODE_INSERT; break;
	case tKeyboard::Key_Delete:    key = SDL_SCANCODE_DELETE; break;
	case tKeyboard::Key_Add:       key = SDL_SCANCODE_KP_PLUS; break;
	case tKeyboard::Key_Subtract:  key = SDL_SCANCODE_KP_MINUS; break;
	case tKeyboard::Key_Multiply:  key = SDL_SCANCODE_KP_MULTIPLY; break;
	case tKeyboard::Key_Divide:    key = SDL_SCANCODE_KP_DIVIDE; break;
	case tKeyboard::Key_Pause:     key = SDL_SCANCODE_PAUSE; break;
	case tKeyboard::Key_F1:        key = SDL_SCANCODE_F1; break;
	case tKeyboard::Key_F2:        key = SDL_SCANCODE_F2; break;
	case tKeyboard::Key_F3:        key = SDL_SCANCODE_F3; break;
	case tKeyboard::Key_F4:        key = SDL_SCANCODE_F4; break;
	case tKeyboard::Key_F5:        key = SDL_SCANCODE_F5; break;
	case tKeyboard::Key_F6:        key = SDL_SCANCODE_F6; break;
	case tKeyboard::Key_F7:        key = SDL_SCANCODE_F7; break;
	case tKeyboard::Key_F8:        key = SDL_SCANCODE_F8; break;
	case tKeyboard::Key_F9:        key = SDL_SCANCODE_F9; break;
	case tKeyboard::Key_F10:       key = SDL_SCANCODE_F10; break;
	case tKeyboard::Key_F11:       key = SDL_SCANCODE_F11; break;
	case tKeyboard::Key_F12:       key = SDL_SCANCODE_F12; break;
	case tKeyboard::Key_F13:       key = SDL_SCANCODE_F13; break;
	case tKeyboard::Key_F14:       key = SDL_SCANCODE_F14; break;
	case tKeyboard::Key_F15:       key = SDL_SCANCODE_F15; break;
	case tKeyboard::Key_Left:      key = SDL_SCANCODE_LEFT; break;
	case tKeyboard::Key_Right:     key = SDL_SCANCODE_RIGHT; break;
	case tKeyboard::Key_Up:        key = SDL_SCANCODE_UP; break;
	case tKeyboard::Key_Down:      key = SDL_SCANCODE_DOWN; break;
	case tKeyboard::Key_Numpad0:   key = SDL_SCANCODE_KP_0; break;
	case tKeyboard::Key_Numpad1:   key = SDL_SCANCODE_KP_1; break;
	case tKeyboard::Key_Numpad2:   key = SDL_SCANCODE_KP_2; break;
	case tKeyboard::Key_Numpad3:   key = SDL_SCANCODE_KP_3; break;
	case tKeyboard::Key_Numpad4:   key = SDL_SCANCODE_KP_4; break;
	case tKeyboard::Key_Numpad5:   key = SDL_SCANCODE_KP_5; break;
	case tKeyboard::Key_Numpad6:   key = SDL_SCANCODE_KP_6; break;
	case tKeyboard::Key_Numpad7:   key = SDL_SCANCODE_KP_7; break;
	case tKeyboard::Key_Numpad8:   key = SDL_SCANCODE_KP_8; break;
	case tKeyboard::Key_Numpad9:   key = SDL_SCANCODE_KP_9; break;
	case tKeyboard::Key_Q:         key = SDL_SCANCODE_Q; break;
	case tKeyboard::Key_W:         key = SDL_SCANCODE_W; break;
	case tKeyboard::Key_E:         key = SDL_SCANCODE_E; break;
	case tKeyboard::Key_R:         key = SDL_SCANCODE_R; break;
	case tKeyboard::Key_T:         key = SDL_SCANCODE_T; break;
	case tKeyboard::Key_Y:         key = SDL_SCANCODE_Y; break;
	case tKeyboard::Key_U:         key = SDL_SCANCODE_U; break;
	case tKeyboard::Key_I:         key = SDL_SCANCODE_I; break;
	case tKeyboard::Key_O:         key = SDL_SCANCODE_O; break;
	case tKeyboard::Key_P:         key = SDL_SCANCODE_P; break;
	case tKeyboard::Key_A:         key = SDL_SCANCODE_A; break;
	case tKeyboard::Key_S:         key = SDL_SCANCODE_S; break;
	case tKeyboard::Key_D:         key = SDL_SCANCODE_D; break;
	case tKeyboard::Key_F:         key = SDL_SCANCODE_F; break;
	case tKeyboard::Key_G:         key = SDL_SCANCODE_G; break;
	case tKeyboard::Key_H:         key = SDL_SCANCODE_H; break;
	case tKeyboard::Key_J:         key = SDL_SCANCODE_J; break;
	case tKeyboard::Key_K:         key = SDL_SCANCODE_K; break;
	case tKeyboard::Key_L:         key = SDL_SCANCODE_L; break;
	case tKeyboard::Key_Z:         key = SDL_SCANCODE_Z; break;
	case tKeyboard::Key_X:         key = SDL_SCANCODE_X; break;
	case tKeyboard::Key_C:         key = SDL_SCANCODE_C; break;
	case tKeyboard::Key_V:         key = SDL_SCANCODE_V; break;
	case tKeyboard::Key_B:         key = SDL_SCANCODE_B; break;
	case tKeyboard::Key_N:         key = SDL_SCANCODE_N; break;
	case tKeyboard::Key_M:         key = SDL_SCANCODE_M; break;
	case tKeyboard::Key_Num0:      key = SDL_SCANCODE_0; break;
	case tKeyboard::Key_Num1:      key = SDL_SCANCODE_1; break;
	case tKeyboard::Key_Num2:      key = SDL_SCANCODE_2; break;
	case tKeyboard::Key_Num3:      key = SDL_SCANCODE_3; break;
	case tKeyboard::Key_Num4:      key = SDL_SCANCODE_4; break;
	case tKeyboard::Key_Num5:      key = SDL_SCANCODE_5; break;
	case tKeyboard::Key_Num6:      key = SDL_SCANCODE_6; break;
	case tKeyboard::Key_Num7:      key = SDL_SCANCODE_7; break;
	case tKeyboard::Key_Num8:      key = SDL_SCANCODE_8; break;
	case tKeyboard::Key_Num9:      key = SDL_SCANCODE_9; break;
	default:                       key = SDL_SCANCODE_UNKNOWN; break;
	}

	return key;
}

bool Input_IsKeyPressed(tKeyboard keyboard, tKeyboard::Key key)
{
	const uint8_t* state = (const uint8_t*)keyboard.impl;
	return state[KeyboardKeyToSDLScancodeKey(key)] > 0;
}

struct tMouseImpl
{
	int32_t x;
	int32_t y;
	uint32_t state;
};

tMouseImpl s_mouseImpl;

Mouse Input_GetMouse(Engine* engine)
{
	s_mouseImpl.state = SDL_GetMouseState((int*)(&s_mouseImpl.x), (int*)(&s_mouseImpl.y));
	
	Mouse mouse;
	mouse.impl = (Mouse::MouseImpl) &s_mouseImpl;
	return mouse;
}

void Input_GetPosition(Mouse mouse, int32_t* x, int32_t* y)
{
	tMouseImpl* mouseImpl = (tMouseImpl*) mouse.impl;
	*x = mouseImpl->x;
	*y = mouseImpl->y;
}

bool Input_IsButtonPressed(Mouse mouse, Mouse::Button button)
{
	tMouseImpl* mouseImpl = (tMouseImpl*)mouse.impl;
	int sdlbutton;
	switch (button)
	{
	case Mouse::Button_Unknown: sdlbutton = 0; break;
	case Mouse::Button_Left:    sdlbutton = SDL_BUTTON_LEFT; break;
	case Mouse::Button_Middle:  sdlbutton = SDL_BUTTON_MIDDLE; break;
	case Mouse::Button_Right:   sdlbutton = SDL_BUTTON_RIGHT; break;
	default:                     sdlbutton = 0; break;
	}

	return (mouseImpl->state & SDL_BUTTON(sdlbutton)) > 0;
}

Input_ControllerCallbacks _controller_callbacks =
{
	nullptr,
	nullptr,
	nullptr
};

struct JoystickHandler
{
	SDL_Joystick *joy;
	int32_t index;
	int32_t instanceId;
	ControllerInfo info;
};

LightVector<JoystickHandler> _joysticks;
LightVector<ControllerState> _joysticksState;

void Input_SetControllerCallbacks(Input_ControllerCallbacks callbacks)
{
	_controller_callbacks = callbacks;
}

const ControllerInfo* Input_GetControllerInfo(uint16_t Id)
{
	return (_joysticks.size() > Id && _joysticks[Id].joy != nullptr) ? &_joysticks[Id].info : nullptr;
}

void Input_SDL_Event_JoyDeviceAdded(SDL_Event* event)
{
	uint16_t joyId = 0;
	for (; joyId < _joysticks.size(); joyId++)
		if (_joysticks[joyId].joy == nullptr)
			break;

	if (_joysticks.capacity() <= joyId)
	{
		_joysticks.reserve(joyId + 32);
		_joysticksState.reserve(joyId + 32);
	}
	
	if (_joysticks.size() <= joyId)
	{
		size_t i = _joysticks.size();
		_joysticks.resize(joyId + 1);
		_joysticksState.resize(joyId + 1);
		for (; i < _joysticks.size(); i++)
			_joysticks[i].joy = nullptr;
	}

	int32_t which = event->jdevice.which;
	SDL_Joystick* joy = SDL_JoystickOpen(which);
	if (joy)
	{
		JoystickHandler& handler = _joysticks[joyId];
		handler.joy = joy;
		handler.index = which;
		handler.instanceId = SDL_JoystickInstanceID(joy);

		ControllerInfo info =
		{
			joyId,
			SDL_JoystickNumAxes(joy),
			SDL_JoystickNumButtons(joy),
			SDL_JoystickNameForIndex(which)
		};

		handler.info = info;

		if (_controller_callbacks.added != nullptr)
		{
			_controller_callbacks.added(_controller_callbacks.data, &handler.info);
		}
	}
}

void Input_SDL_Event_JoyDeviceRemoved(SDL_Event* event)
{
	size_t index = 0;
	for (; index < _joysticks.size(); index++)
	{
		if (_joysticks[index].joy && _joysticks[index].instanceId == event->jdevice.which)
		{
			break;
		}
	}

	SYS_ASSERT(index != _joysticks.size());

	JoystickHandler& handler = _joysticks[index];
	if (SDL_JoystickGetAttached(handler.joy))
		SDL_JoystickClose(handler.joy);

	handler.joy = nullptr;

	if (_controller_callbacks.removed != nullptr)
	{
		_controller_callbacks.removed(_controller_callbacks.data, &handler.info);
	}
}

void Input_SDL_JoysticksUpdateState()
{
	for (size_t i = 0; i < _joysticks.size(); i++)
	{
		JoystickHandler& handler = _joysticks[i];
		uint32_t butMask = 0;
		if (handler.joy != nullptr)
		{
			SYS_ASSERT(handler.info.NumButtons <= (sizeof(butMask) * 8));
			for (size_t butInd = 0; butInd < handler.info.NumButtons; butInd++)
			{
				butMask |= SDL_JoystickGetButton(handler.joy, butInd) << butInd;
			}
		}

		_joysticksState[i].ButtonMask = butMask;
	}
}

const ControllerState * Input_GetControllerState(uint16_t Id)
{
	SYS_ASSERT(Id <= _joysticksState.size());
	return &_joysticksState[Id];
}

#endif
