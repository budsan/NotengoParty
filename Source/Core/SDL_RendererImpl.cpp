#ifdef SDL_IMPL

#include "Engine.h"
#include "Renderer.h"

#include "SDL_CommonImpl.h"
#include <SDL_opengl.h>
#include <math.h>

void Renderer_ImGui_NewFrame(Engine* engine)
{
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	//ImGui_ImplSdl_NewFrame(window->sdl_window);
}

void Renderer_Create(Engine* engine)
{
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	Renderer_SDLImpl* renderer = (Renderer_SDLImpl*) SysMalloc(sizeof(Renderer_SDLImpl));
	engine->renderer = renderer;

	renderer->context = SDL_GL_CreateContext((SDL_Window*)window->sdl_window);
	SDL_GL_MakeCurrent((SDL_Window*)window->sdl_window, renderer->context);

	renderer->current.Blend = true;
	glEnable(GL_BLEND);

	renderer->current.BlendFunc = RNDR_BLEND(BlendSourceAlpha, BlendOneMinusSourceAlpha);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renderer->current.DepthTest = true;
	glEnable(GL_DEPTH_TEST);

	renderer->current.DepthTestFunc = DepthTestLessEqual;
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//ImGui_ImplSdl_Init(window->sdl_window);
}

void Renderer_Destroy(Engine* engine)
{
	SYS_ASSERT(engine->renderer != NULL);
	//ImGui_ImplSdl_Shutdown();

	Renderer_SDLImpl* renderer = (Renderer_SDLImpl*)engine->renderer;
	SDL_GL_DeleteContext((SDL_GLContext*)renderer->context);
	SysFree(renderer);
	engine->renderer = NULL;
}

void Renderer_Clear(Engine* engine, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	//SYS_ASSERT(engine->renderer != NULL);
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
	GLdouble fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void Renderer_SetViewport(float width, float height)
{
	GLfloat ratio = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspectiveGL(45.0f, ratio, 0.1f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Renderer_DrawLogic(Engine* engine, DrawList* drawlist)
{
	Renderer_SDLImpl* renderer = (Renderer_SDLImpl*)engine->renderer;

	glLoadIdentity();
	glTranslatef(drawlist->cam.x, drawlist->cam.y, drawlist->cam.zoom);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	const uint8_t* vtx_buffer = (const uint8_t*)&drawlist->vtx_buffer.front();
	for (int i = 0; i < drawlist->cmds.Size; ++i)
	{
		DrawCmd& cmd = drawlist->cmds[i];
		const DrawList::IdxType* idx_buffer = (&drawlist->idx_buffer.front()) + cmd.ElemStart;
		glVertexPointer(2, GL_FLOAT, sizeof(DrawVertex), (void*)(vtx_buffer + OFFSETOF(DrawVertex, pos)));
		glTexCoordPointer(2, GL_FLOAT, sizeof(DrawVertex), (void*)(vtx_buffer + OFFSETOF(DrawVertex, uv)));
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(DrawVertex), (void*)(vtx_buffer + OFFSETOF(DrawVertex, col)));
		glDrawElements(GL_TRIANGLES, (GLsizei)cmd.ElemCount, sizeof(DrawList::IdxType) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer);	
	}
	#undef OFFSETOF

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Renderer_Present(Engine* engine)
{
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_GL_SwapWindow(window->sdl_window);
}

#endif