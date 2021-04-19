/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:51:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/19 17:51:20 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_vect	negative_filter(t_vect col)
{
	col.x = 255 - col.x;
	col.y = 255 - col.y;
	col.z = 255 - col.z;
	return (col);
}

t_vect	red_blue(t_vect col, t_vect_i var)
{
	if (var.x < WIN_W / 2)
	{
		col.x += 50;
		col.y = 0;
		col.z = 0;
	}
	else
	{
		col.x = 0;
		col.y = 0;
		col.z += 50;
	}
	return (safe_color(col));
}

t_vect	filter(t_all *data, t_vect col, t_vect_i var)
{
	if (data->filter == 1)
		col = negative_filter(col);
	if (data->filter == 2)
		col = red_blue(col, var);
	return (col);
}

void	set_pixel(t_all data, t_vect col, t_vect_i var, t_ray ray)
{
	if (SDL_SetRenderDrawColor(data.rend, col.x, col.y, col.z, 255) != 0)
		sdl_error("Get color failed");
	if (SDL_RenderDrawPoint(data.rend, var.x, var.y) != 0)
		sdl_error("draw point failed");
	data.screen_pixels[var.x * WIN_W + var.y] = col;
}
