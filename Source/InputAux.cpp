#include "InputAux.h"

namespace Input
{

const char* _HatStateName[] =
{
	"CENTERED",
	"RIGHT",
	"LEFT",
	"0011 CENTERED",
	"UP",
	"RIGHTUP",
	"LEFTUP",
	"0111 UP",
	"DOWN",
	"RIGHTDOWN",
	"LEFTDOWN",
	"1011 DOWN",
	"1100 CENTERED",
	"1101 LEFT",
	"1110 RIGHT",
	"1111 CENTERED"
};

const char* GetHatStateName(size_t i)
{
	return _HatStateName[i];
}

ControllerState::HatType AxisToHat(ControllerState::AxisType x, ControllerState::AxisType y)
{
	const ControllerState::AxisType threshold = 1 << (sizeof(ControllerState::AxisType) * 7);

	ControllerState::HatType mask = 0;
	mask |= (x > threshold) ? 1 << 0 : 0;
	mask |= (x < -threshold) ? 1 << 1 : 0;
	mask |= (y < -threshold) ? 1 << 2 : 0;
	mask |= (y > threshold) ? 1 << 3 : 0;

	return mask;
}

ControllerState::HatType AxisToHat(const ControllerState* state)
{
	return AxisToHat(state->AxisState[0], state->AxisState[1]);
}

}