#ifndef SDL_MASK_PRIV_H
#define SDL_MASK_PRIV_H

#include "SDL_mask.h"

/** Variable to save error information in. */
extern _Thread_local const char *g_err;

static inline void create_masked_surface(
	SDL_Surface *img,
	SDL_Surface *mask,
	SDL_Color mask_col,
	SDL_Color target_col)
{
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
				Uint32 newp = SDL_MapRGBA(
					img->format,
					target_col.r,
					target_col.g,
					target_col.b,
					target_col.a);
				img_pixels[imgpi] = newp;
			}
		}
	}
}

#endif
