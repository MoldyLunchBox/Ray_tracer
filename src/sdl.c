#include "../header/rt.h"

void	sdl_error(char *message)
{
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();
	exit(-1);
}

void	init_sdl(t_all *data)
{
	data->win = NULL;
	data->rend = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init
		(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
		sdl_error("initialisation SDL");
	data->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!data->win)
		sdl_error("Creation window");
	data->rend = SDL_CreateRenderer(data->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!data->rend)
		sdl_error("Creation render");
	if (SDL_SetRenderDrawColor(data->rend, 255, 0, 0, 255) != 0)
		sdl_error("Get color failed");
}

void	event_conditions(SDL_Event event, t_all *data)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
	{
		data->ren = 1;
		SDL_RenderClear(data->rend);
		threading(*data);
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
	{
		data->ren = 0;
		SDL_RenderClear(data->rend);
		threading(*data);
	}
	if (event.type == SDL_MOUSEBUTTONDOWN
		&& event.button.button == SDL_BUTTON_LEFT)
	{
		SDL_GetMouseState(&(data->event.x), &(data->event.y));
		if (data->ren == 0)
			{SDL_RenderClear(data->rend);
			threading(*data);}
	}
}

void	loop_program(t_all *data)
{
	SDL_bool	prog_launched;
	SDL_Event	event;

	SDL_RenderPresent(data->rend);
	prog_launched = SDL_TRUE;
	while (prog_launched)
	{
		while (SDL_WaitEvent(&event))
		{
			if ((event.type == SDL_KEYDOWN && event.key.keysym.sym
					== SDLK_ESCAPE) || event.type == SDL_QUIT)
			{
				ft_free_obj(data);
				prog_launched = SDL_FALSE;
				exit(1);
			}
			event_conditions(event, data);
		}
	}
	SDL_DestroyRenderer(data->rend);
	SDL_DestroyWindow(data->win);
	SDL_Quit();
}
