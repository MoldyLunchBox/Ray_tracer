/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:33:06 by amya              #+#    #+#             */
/*   Updated: 2021/04/18 17:28:55 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int		inside_left_arrow(t_all *data)
{
	SDL_Rect	box;

	box.x = WIN_W / 3 * 2 - (WIN_W / 4 / 7);
	box.y = WIN_H / 4 - WIN_H / 4 /2 ;
	box.w = WIN_W / 3 / 2 ;
	box.h = WIN_H / 3 / 3;
	if (data->event.x >= box.x && data->event.x <= box.x
		+ box.w && data->event.y >= box.y && data->event.y <= box.y + box.h)
		return (1);
	return (0);
}

int		inside_right_arrow(t_all *data)
{
	SDL_Rect	box;

	box.x = WIN_W / 3 * 2 - (WIN_W / 4 / 7) + WIN_W / 3 / 2;
	box.y = WIN_H / 4 - WIN_H / 4 /2 ;
	box.w = WIN_W / 3 / 2 ;
	box.h = WIN_H / 3 / 3;
	if (data->event.x >= box.x && data->event.x <= box.x
		+ box.w && data->event.y >= box.y && data->event.y <= box.y + box.h)
		return (1);
	return (0);
}

void	event_alias(t_all *data)
{
	if (inside_left_arrow(data))
		data->left = 1;
	if (inside_right_arrow(data))
		data->right = 1;
}

static void	load_texture(t_all *data)
{
	SDL_Rect	interface;
	SDL_Texture	*filter;

	interface.x = 0;
	interface.y = 0;
	interface.w = WIN_W;
	interface.h = WIN_H;
	if (data->filter == 0)
		filter = IMG_LoadTexture(data->rend, "./textures/interface.jpg");
	if (data->filter == 1)
		filter = IMG_LoadTexture(data->rend, "./textures/effect1.jpg");
	if (data->filter == 2)
		filter = IMG_LoadTexture(data->rend, "./textures/effect2.jpg");
	SDL_RenderCopy(data->rend, filter, NULL, &interface);
}

int		inside_filter(t_all *data)
{
	SDL_Rect	box;
	// SDL_Texture	*focus;

	// focus = IMG_LoadTexture(data->rend, "./textures/focus.png");
	box.x = WIN_W / 3 * 2;
	box.y = WIN_H / 2 - (WIN_H / 5 / 4);
	box.w = WIN_W ;
	box.h = WIN_H / 3 / 3;
	if (data->event.x >= box.x && data->event.x <= box.x + box.w && data->event.y >= box.y && data->event.y <= box.y + box.h)
		return (1);
	// SDL_RenderCopy(data->rend, focus, NULL, &box);
	return (0);
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
	if (inside_filter(data) == 1)
	{
		if (data->filter == 2)
			data->filter = 0;
		else
			data->filter++;
	}
}

int		inside_start(t_all *data)
{
	SDL_Rect	box;

	box.x = WIN_W / 3 * 2;
	box.y = WIN_H / 5 * 4 - (WIN_H / 5 /4 );
	box.w = WIN_W;
	box.h = WIN_H / 5 * 1 - (WIN_H / 5 / 3);
	if (data->event.x >= box.x && data->event.x <= box.x
		+ box.w && data->event.y >= box.y && data->event.y <= box.y + box.h)
		return (1);
	return (0);
}

void	event_start(t_all *data)
{
	SDL_Texture	*start;
	SDL_Rect	interface;

	interface.x = 0;
	interface.y = 0;
	interface.w = WIN_W;
	interface.h = WIN_H;
	start = NULL;
	// start = IMG_LoadTexture(data->rend, "./textures/interface.jpg");
	if (inside_start(data) == 1)
		data->ren = 1;
	if (data->ren)
	{
		start = IMG_LoadTexture(data->rend, "./textures/interface_start.jpg");
		SDL_RenderCopy(data->rend, start, NULL, &interface);
		SDL_RenderPresent(data->rend);
	}
	else
		load_texture(data);
		// SDL_RenderCopy(data->rend, start, NULL, &interface);
}
