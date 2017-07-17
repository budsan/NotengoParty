#pragma once

#include "Core/imgui/imgui.h"

namespace UI
{
const char* FindRenderedTextEnd(const char* text, const char* text_end);
ImVec2 CalcTextSize(ImFont* font, float font_size, const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width);
}