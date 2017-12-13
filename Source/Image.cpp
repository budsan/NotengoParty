#include "Image.h"

void Image_Load(const FileReadAsync* src, ImageLoadResult* dst)
{
	SYS_ASSERT(src != NULL);
	SYS_ASSERT(src->completed);
	SYS_ASSERT(dst != NULL);

	dst->data = stbi_load_from_memory((const stbi_uc *)src->data, src->size, &dst->width, &dst->height, &dst->channels, 0);
}

void Image_Free(ImageLoadResult* img)
{
	SYS_ASSERT(img != NULL);
	SYS_ASSERT(img->data != NULL);

	stbi_image_free(img->data);
}