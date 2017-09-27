#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

struct Sprite
{
	SDL_Texture *sheet;
	int x, y;
	int frame_width, frame_height;
	int current_frame;
	bool is_moving;
	SDL_RendererFlip flip;
};

SDL_Texture* tex_from_image(const std::string& path, SDL_Renderer *renderer);

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Contra Clone", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 320, 240);

	std::string bg_path = "data/background.png";
	SDL_Texture *bg_texture = tex_from_image(bg_path, renderer);
	if (!bg_texture)
	{
		return 1;
	}

	std::string hero_path = "data/hero_sheet.png";
	SDL_Texture *hero_texture = tex_from_image(hero_path, renderer);
	if (!hero_texture)
	{
		return 1;
	}

	Sprite hero = { hero_texture, 60, 60, 40, 50, 5, false, SDL_FLIP_NONE };

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
				break;
			}
		}
		const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

		//Update world
		bool left_pressed = keyboard_state[SDL_SCANCODE_LEFT];
		bool right_pressed = keyboard_state[SDL_SCANCODE_RIGHT];
		bool jump_pressed = keyboard_state[SDL_SCANCODE_UP];

		if (left_pressed)
		{
			hero.flip = SDL_FLIP_HORIZONTAL;
		}
		else if (right_pressed)
		{
			hero.flip = SDL_FLIP_NONE;
		}

		// Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

		SDL_Rect src_hero = { hero.frame_width*hero.current_frame, 0, hero.frame_width,
			hero.frame_height };

		SDL_Rect dest_hero = { hero.x, hero.y, hero.frame_width, hero.frame_height };

		SDL_RenderCopyEx(renderer, hero.sheet, &src_hero, &dest_hero, 0, NULL, hero.flip);
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(hero_texture);
	SDL_Quit();

	return 0;
}

SDL_Texture* tex_from_image(const std::string& path, SDL_Renderer *renderer)
{
	SDL_Surface *surface = IMG_Load(path.c_str());
	if (!surface)
	{
		std::cout << "Cannot load texture from: " << path;
		return NULL;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return tex;
}