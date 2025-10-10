#include "SDL_mask_priv.h"

/** Variable to save error information in. */
_Thread_local const char *g_err;

/** Creates a masked texture.
 * \param path_to_img Path to the image file to be masked (png).
 * \param path_to_mask Path to the mask file to be used (png).
 * \param mask_col The color of the mask file to be used as mask.
 * \param src_col The color in the image file to be changed. 
 * \param target_col The color to which src_col is to be changed.
 * \return The masked texture. */
SDL_Texture *SDL_CreateMaskedTexture(
	SDL_Renderer *ren,
	const char *path_to_img,
	const char *path_to_mask,
	SDL_Color mask_col,
	SDL_Color target_col)
{
	if (!path_to_img || !path_to_mask) {
		g_err = "Invalid input.";
		return NULL;
	}
	SDL_Surface *img = IMG_Load(path_to_img);
	if (!img) {
		g_err = "Failed to load image file.";
		return NULL;
	}
	SDL_Surface *mask = IMG_Load(path_to_mask);
	if (!mask) {
		g_err = "Failed to load mask file.";
		SDL_FreeSurface(img);
		return NULL;
	}
	if (img->w != mask->w || img->h != mask->h) {
		g_err = "Size of mask does not match the same of img.";
		SDL_FreeSurface(img);
		SDL_FreeSurface(mask);
		return NULL;
	}
	SDL_Surface *tmp = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA8888, 0);
	if (!tmp) {
		g_err = "Failed to convert img pixel format.";
		SDL_FreeSurface(img);
		SDL_FreeSurface(mask);
		return NULL;
	}
	img = tmp;
	tmp = SDL_ConvertSurfaceFormat(mask, SDL_PIXELFORMAT_RGBA8888, 0);
	if (!tmp) {
		g_err = "Failed to convert mask pixel format.";
		SDL_FreeSurface(img);
		SDL_FreeSurface(mask);
		return NULL;
	}
	mask = tmp;

	create_masked_surface(img, mask, mask_col, target_col);

	SDL_Texture *masked_texture = SDL_CreateTextureFromSurface(ren, img);
	if (!masked_texture) {
		g_err = "Failed to create masked texture.";
		SDL_FreeSurface(img);
		SDL_FreeSurface(mask);
		return NULL;
	}

	SDL_FreeSurface(img);
	SDL_FreeSurface(mask);

	return masked_texture;
}

/** Returns a string containing the latest error information if
 * exists or NULL. */
const char *SDL_MaskGetError() {
	return g_err;
}
