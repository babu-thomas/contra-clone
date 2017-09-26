#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Contra Clone", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 320, 240);

	SDL_Surface *bg = IMG_Load("data/background.png");
	if (!bg)
	{
		std::cout << "Cannot load background!";
		return 1;
	}

	SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, bg);
	SDL_FreeSurface(bg);

	bool quit = false;
	while (!quit)
	{
		// Handle events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
			}
		}

		// Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(bg_texture);
	SDL_Quit();

	return 0;
}