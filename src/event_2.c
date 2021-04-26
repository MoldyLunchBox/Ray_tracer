/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:03:23 by amya              #+#    #+#             */
/*   Updated: 2021/04/24 10:07:29 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int	inside_left_arrow(t_all *data)
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

int	inside_right_arrow(t_all *data)
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

void	orbiter(t_all *data)
{
	double	rad;

	data->orbit_angle += 5;
	rad = sqrt(data->camera->pos.x * data->camera->pos.x + (data->camera->pos.y
				* data->camera->pos.y) + data->camera->pos.z
			* data->camera->pos.z);
	if (data->left)
	{
		data->camera->pos.x = data->camera->dir.x
			+ (rad * cos(data->orbit_angle));
		data->camera->pos.z = data->camera->dir.z
			+ (rad * sin(data->orbit_angle));
		set_camera_dir(data->camera);
	}
}

void	event_orbiter(t_all *data)
{
	if (inside_left_arrow(data))
		data->left = 1;
	if (inside_right_arrow(data))
		data->right = 1;
}

int	inside_filter(t_all *data)
{
	SDL_Rect	box;

	box.x = WIN_W / 3 * 2;
	box.y = WIN_H / 2 - (WIN_H / 5 / 4);
	box.w = WIN_W ;
	box.h = WIN_H / 3 / 3;
	if (data->event.x >= box.x && data->event.x <= box.x + box.w
		&& data->event.y >= box.y && data->event.y <= box.y + box.h)
		return (1);
	return (0);
}
