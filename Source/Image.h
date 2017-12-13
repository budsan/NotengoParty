#include "Core/System.h"
#include "Core/File.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(sz)           SysMalloc(sz)
#define STBI_REALLOC(p,newsz)     SysRealloc(p,newsz)
#define STBI_FREE(p)              SysFree(p)

#include "stb_image.h"

struct ImageLoadResult
{
	int width;
	int height;
	int channels;
	uint8_t *data;
};

void Image_Load(const FileReadAsync* src, ImageLoadResult* dst);
void Image_Free(ImageLoadResult* img);