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

/** \file include/SDL_mask.h 
 * \brief Public header file for the SDL_mask library.
 * \details This file contains the declarations of the public functions. */

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
