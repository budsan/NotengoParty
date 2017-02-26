#include "imgui/imgui.h"
#include "Window.h"

IMGUI_API bool        ImGui_ImplCore_Init(Engine* engine);
IMGUI_API void        ImGui_ImplCore_Shutdown(Engine* engine);
IMGUI_API void        ImGui_ImplCore_NewFrame(Engine* engine);
IMGUI_API bool        ImGui_ImplCore_ProcessEvent();

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_ImplCore_InvalidateDeviceObjects(Engine* engine);
IMGUI_API bool        ImGui_ImplCore_CreateDeviceObjects(Engine* engine);

// Exposing manually RenderDrawList for application use
IMGUI_API void ImGui_ImplCore_RenderDrawLists(ImDrawData* draw_data);
