#ifndef SDL_MASK_H
#define SDL_MASK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/** Creates a masked texture.
 * \param ren Renderer to be used for creating the new texture.
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
	SDL_Color target_col);

/** Returns a string containing the latest error information if
 * exists or NULL. */
const char *SDL_MaskGetError();

#endif
