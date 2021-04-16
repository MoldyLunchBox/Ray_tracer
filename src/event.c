/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:33:06 by amya              #+#    #+#             */
/*   Updated: 2021/04/15 16:33:16 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	event_alias(t_all *data)
{
	SDL_Rect	dest;
	SDL_Texture	*aalias;

	aalias = NULL;
	dest.x = WIN_W / 2 - WIN_W / 3 / 2;
	dest.y = WIN_H / 5 * 0 + (WIN_H / 5 / 5 * 1);
	dest.w = WIN_W / 3;
	dest.h = WIN_H / 5;
	if (data->aalias == 0)
		aalias = IMG_LoadTexture(data->rend, "./textures/not_antialias.png");
	if (data->aalias == 1)
		aalias = IMG_LoadTexture(data->rend, "./textures/antialias.png");
	if (inside_rect(data, dest) == 1)
	{
		data->aalias = 1 - data->aalias;
		if (data->aalias == 0)
			aalias = IMG_LoadTexture(data->rend,
					"./textures/not_antialias.png");
		if (data->aalias == 1)
			aalias = IMG_LoadTexture(data->rend, "./textures/antialias.png");
	}
	SDL_RenderCopy(data->rend, aalias, NULL, &dest);
}

static void	load_texture(t_all *data, SDL_Texture	*filter)
{
	if (data->filter == 2)
		data->filter = 0;
	else
		data->filter++;
	if (data->filter == 0)
		filter = IMG_LoadTexture(data->rend, "./textures/no_filter.png");
	if (data->filter == 1)
		filter = IMG_LoadTexture(data->rend, "./textures/filter1.png");
	if (data->filter == 2)
		filter = IMG_LoadTexture(data->rend, "./textures/filter2.png");
}

void	event_filter(t_all *data)
{
	SDL_Rect	dest_r1;
	SDL_Texture	*filter;

	filter = NULL;
	dest_r1.x = WIN_W / 2 - WIN_W / 3 / 2;
	dest_r1.y = WIN_H / 5 * 1 + (WIN_H / 5 / 5 * 2);
	dest_r1.w = WIN_W / 3;
	dest_r1.h = WIN_H / 5;
	if (data->filter == 0)
		filter = IMG_LoadTexture(data->rend, "./textures/no_filter.png");
	if (data->filter == 1)
		filter = IMG_LoadTexture(data->rend, "./textures/filter1.png");
	if (data->filter == 2)
		filter = IMG_LoadTexture(data->rend, "./textures/filter2.png");
	if (inside_rect(data, dest_r1) == 1)
		load_texture(data, filter);
	SDL_RenderCopy(data->rend, filter, NULL, &dest_r1);
}

void	event_focus(t_all *data)
{
	SDL_Rect	dest_r2;
	SDL_Texture	*focus;

	focus = NULL;
	dest_r2.x = WIN_W / 2 - WIN_W / 3 / 2;
	dest_r2.y = WIN_H / 5 * 2 + (WIN_H / 5 / 5 * 3);
	dest_r2.w = WIN_W / 3;
	dest_r2.h = WIN_H / 5;
	if (data->deep == 0)
		focus = IMG_LoadTexture(data->rend, "./textures/no_focus.png");
	if (data->deep == 1)
		focus = IMG_LoadTexture(data->rend, "./textures/focus.png");
	if (inside_rect(data, dest_r2) == 1)
	{
		data->deep = 1 - data->deep;
		if (data->deep == 0)
			focus = IMG_LoadTexture(data->rend, "./textures/no_focus.png");
		if (data->deep == 1)
			focus = IMG_LoadTexture(data->rend, "./textures/focus.png");
	}
	SDL_RenderCopy(data->rend, focus, NULL, &dest_r2);
}

void	event_go(t_all *data)
{
	SDL_Rect	dest_r2;
	SDL_Texture	*go;

	go = NULL;
	dest_r2.x = WIN_W / 2 - WIN_W / 3 / 2;
	dest_r2.y = WIN_H / 5 * 3 + (WIN_H / 5 / 5 * 4);
	dest_r2.w = WIN_W / 3;
	dest_r2.h = WIN_H / 5;
	go = IMG_LoadTexture(data->rend, "./textures/go.png");
	if (inside_rect(data, dest_r2) == 1)
		data->ren = 1;
	SDL_RenderCopy(data->rend, go, NULL, &dest_r2);
}
