#include "Engine.h"
#include "Texture.h"

#include "imgui\imgui.h"
#include "imgui_impl_core.h"

// Data
static double g_Time = 0.0f;
//static bool         g_MousePressed[3] = { false, false, false };
//static float        g_MouseWheel = 0.0f;
static TextureType g_FontTexture = 0;

void ImGui_ImplCore_RenderDrawLists(ImDrawData* draw_data)
{
	//// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
	//ImGuiIO& io = ImGui::GetIO();
	//int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	//int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	//if (fb_width == 0 || fb_height == 0)
	//    return;
	//draw_data->ScaleClipRects(io.DisplayFramebufferScale);

	//// We are using the OpenGL fixed pipeline to make the example code simpler to read!
	//// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers.
	//GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	//GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
	//glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	//glEnable(GL_SCISSOR_TEST);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnable(GL_TEXTURE_2D);
	////glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context

	//// Setup viewport, orthographic projection matrix
	//glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadIdentity();

	//// Render command lists
	//#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	//for (int n = 0; n < draw_data->CmdListsCount; n++)
	//{
	//    const ImDrawList* cmd_list = draw_data->CmdLists[n];
	//    const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
	//    const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
	//    glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
	//    glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
	//    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

	//    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
	//    {
	//        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
	//        if (pcmd->UserCallback)
	//        {
	//            pcmd->UserCallback(cmd_list, pcmd);
	//        }
	//        else
	//        {
	//            glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
	//            glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
	//            glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer);
	//        }
	//        idx_buffer += pcmd->ElemCount;
	//    }
	//}
	//#undef OFFSETOF

	//// Restore modified state
	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glBindTexture(GL_TEXTURE_2D, (GLuint)last_texture);
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glPopAttrib();
	//glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
}

static const char* ImGui_ImplCore_GetClipboardText(void* user_data)
{
	return System_GetClipboardText();
}

static void ImGui_ImplCore_SetClipboardText(void* user_data, const char* text)
{
	System_SetClipboardText(text);
}

bool ImGui_ImplCore_ProcessEvent()
{
	return false;
}

bool ImGui_ImplCore_CreateDeviceObjects(Engine* engine)
{
	// Build texture atlas
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);
	{
		Texture2D_Description desc;
		desc.width = width;
		desc.height = height;
		desc.format = TextureFormatA8;

		io.Fonts->TexID = Texture2D_Create(engine, &desc, pixels);
	}

	return true;
}

void ImGui_ImplCore_InvalidateDeviceObjects(Engine* engine)
{
	if (g_FontTexture)
	{
		Texture2D_Destroy(engine, g_FontTexture);
		ImGui::GetIO().Fonts->TexID = 0;
		g_FontTexture = 0;
	}
}

bool ImGui_ImplCore_Init(Engine* engine)
{
	ImGuiIO& io = ImGui::GetIO();

	// Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
	io.KeyMap[ImGuiKey_Tab] = Keyboard::Key_Tab;
	io.KeyMap[ImGuiKey_LeftArrow] = Keyboard::Key_Left;
	io.KeyMap[ImGuiKey_RightArrow] = Keyboard::Key_Right;
	io.KeyMap[ImGuiKey_UpArrow] = Keyboard::Key_Up;
	io.KeyMap[ImGuiKey_DownArrow] = Keyboard::Key_Down;
	io.KeyMap[ImGuiKey_PageUp] = Keyboard::Key_PageUp;
	io.KeyMap[ImGuiKey_PageDown] = Keyboard::Key_PageDown;
	io.KeyMap[ImGuiKey_Home] = Keyboard::Key_Home;
	io.KeyMap[ImGuiKey_End] = Keyboard::Key_End;
	io.KeyMap[ImGuiKey_Delete] = Keyboard::Key_Delete;
	io.KeyMap[ImGuiKey_Backspace] = Keyboard::Key_BackSpace;
	io.KeyMap[ImGuiKey_Enter] = Keyboard::Key_Return;
	io.KeyMap[ImGuiKey_Escape] = Keyboard::Key_Space;
	io.KeyMap[ImGuiKey_A] = Keyboard::Key_A;
	io.KeyMap[ImGuiKey_C] = Keyboard::Key_C;
	io.KeyMap[ImGuiKey_V] = Keyboard::Key_V;
	io.KeyMap[ImGuiKey_X] = Keyboard::Key_X;
	io.KeyMap[ImGuiKey_Y] = Keyboard::Key_Y;
	io.KeyMap[ImGuiKey_Z] = Keyboard::Key_Z;

	io.RenderDrawListsFn = ImGui_ImplCore_RenderDrawLists;   // Alternatively you can set this to NULL and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.
	io.SetClipboardTextFn = ImGui_ImplCore_SetClipboardText;
	io.GetClipboardTextFn = ImGui_ImplCore_GetClipboardText;
	io.ClipboardUserData = (void*)engine;

#ifdef _WIN32
	/*SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	io.ImeWindowHandle = wmInfo.info.win.window;*/
#else
	(void)window;
#endif

	return true;
}

void ImGui_ImplCore_Shutdown(Engine* engine)
{
	ImGui_ImplCore_InvalidateDeviceObjects(engine);
	ImGui::Shutdown();
}

void ImGui_ImplCore_NewFrame(Engine* engine)
{
	if (!g_FontTexture)
		ImGui_ImplCore_CreateDeviceObjects(engine);

	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	int w, h;
	Window_GetSize(engine, &w, &h);
	io.DisplaySize = ImVec2((float)w, (float)h);

	//int display_w, display_h;
	//SDL_GL_GetDrawableSize(window, &display_w, &display_h);
	//io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

	// Setup time step
	Uint32	time = System_Ticks();
	double current_time = time / 1000.0;
	io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
	g_Time = current_time;

	// Setup inputs
	int mx, my;
	Mouse mouse = Input_GetMouse(engine);
	Input_GetPosition(mouse, &mx, &my);
	io.MousePos = ImVec2((float)mx, (float)my);

	//Uint32 mouseMask = SDL_GetMouseState(&mx, &my);
	//if (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS)
	//    io.MousePos = ImVec2((float)mx, (float)my);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
	//else
	//    io.MousePos = ImVec2(-1,-1);

	// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
	/*io.MouseDown[0] = g_MousePressed[0] || (mouseMask & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
	io.MouseDown[1] = g_MousePressed[1] || (mouseMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
	io.MouseDown[2] = g_MousePressed[2] || (mouseMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
	g_MousePressed[0] = g_MousePressed[1] = g_MousePressed[2] = false;

	io.MouseWheel = g_MouseWheel;
	g_MouseWheel = 0.0f;*/

	// Hide OS mouse cursor if ImGui is drawing it
	Input_ShowCursor(!io.MouseDrawCursor);

	// Start the frame
	ImGui::NewFrame();
}