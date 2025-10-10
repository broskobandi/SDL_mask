/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** \file src/SDL_mask.c 
 * \brief Implementation for the SDL_mask library.
 * \details This file contains the definitions of the public functions. */

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
