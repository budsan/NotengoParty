#pragma once

#include "Core/Input.h"

namespace Input
{
const char* GetHatStateName(size_t i);
ControllerState::HatType AxisToHat(ControllerState::AxisType x, ControllerState::AxisType y);
ControllerState::HatType AxisToHat(const ControllerState* state);
}