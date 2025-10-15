#include "SDL_mask_priv.h"
#include <ctest.h>

int main(void) {
	CTEST(!SDL_Init(SDL_INIT_EVERYTHING));
	CTEST(IMG_Init(IMG_INIT_PNG));

	SDL_Surface *img = IMG_Load("../img_test.png");
	CTEST(img);
	SDL_Surface *mask = IMG_Load("../mask_test.png");
	CTEST(mask);
	SDL_Surface *tmp = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA8888, 0);
	CTEST(tmp);
	img = tmp;
	tmp = SDL_ConvertSurfaceFormat(mask, SDL_PIXELFORMAT_RGBA8888, 0);
	CTEST(tmp);
	mask = tmp;
	CTEST(mask->format == img->format);

	SDL_Color mask_col = {0, 0, 0, 0};
	SDL_Color target_col = {0, 0, 0, 0};

	create_masked_surface(img, mask, mask_col, target_col);

	Uint32 *img_pixels = (Uint32*)img->pixels;
	Uint32 *mask_pixels = (Uint32*)mask->pixels;
	Uint32 img_pitch = (Uint32)img->pitch / 4;
	Uint32 mask_pitch = (Uint32)mask->pitch / 4;

	for (Uint32 y = 0; y < (Uint32)img->h; y++) {
		for (Uint32 x = 0; x < (Uint32)img->w; x++) {
			Uint32 imgpi = y * img_pitch + x;
			Uint32 maskpi = y * mask_pitch + x;
			Uint32 maskp = mask_pixels[maskpi];
			Uint32 imgp = img_pixels[imgpi];
			SDL_Color col;
			SDL_GetRGBA(maskp, mask->format, &col.r, &col.g, &col.b, &col.a);
			if (
				col.r == mask_col.r && col.g == mask_col.g &&
				col.b == mask_col.b && col.a == mask_col.a)
			{
				SDL_GetRGBA(imgp, img->format, &col.r, &col.g, &col.b, &col.a);
				CTEST(col.r == target_col.r);
				CTEST(col.g == target_col.g);
				CTEST(col.b == target_col.b);
				CTEST(col.a == target_col.a);
			}
		}
	}

	IMG_Quit();
	SDL_Quit();

	ctest_print_results();

	return 0;
}
