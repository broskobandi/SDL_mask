/* Include the library. */
#include <SDL_mask.h>

int main(void) {
	/* Initialize the SDL session. */
	SDL_Init(SDL_INIT_EVERYTHING);

	/* The library only supports png. */
	IMG_Init(IMG_INIT_PNG);
	SDL_Window *win = SDL_CreateWindow("example", 0, 0, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

	/* Set the blendmode to blend if you want to use the tool as an alpha mask. */
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	SDL_Event event;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	int is_running = 1;

	/* Specify mask_col and target_col.
	 * All pixels in img corresponding with the pixels in mask with mask_col
	 * will be modified to target_col.*/
	SDL_Color mask_col = {0, 0, 0, 0};
	SDL_Color target_col = {0, 0, 0, 0};

	/* Create the masked texture. 
	 * img_test and mask_test must be of the same size. 
	 * The pixel formats do not need to match as they get converted 
	 * to the right format implicitly. */ 
	SDL_Texture *masked_texture =
		SDL_CreateMaskedTexture(
			ren, 
			"../img_test.png",
			"../mask_test.png",
			mask_col,
			target_col);

	/* Create a rect to render the texture over. */
	SDL_Rect rect = {400, 300, 64, 64};

	/* Set up the game loop. */
	while (is_running) {
		while (SDL_PollEvent(&event)) {}
		if (keystate[SDL_SCANCODE_Q]) is_running = 0;
		SDL_SetRenderDrawColor(ren, 30, 70, 70, 255);
		SDL_RenderClear(ren);

		/* Render the texture. */
		SDL_RenderCopy(ren, masked_texture, NULL, &rect);

		SDL_RenderPresent(ren);
	}

	/* Clean up resources. */
	SDL_DestroyTexture(masked_texture);
	SDL_Quit();
	IMG_Quit();

	return 0;
}
