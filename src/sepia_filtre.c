/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia_filtre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:48:49 by yoelguer          #+#    #+#             */
/*   Updated: 2021/03/28 18:50:46 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

static t_vect	sepia(t_vect c)
{
	t_vect v;

	v.x = fmin((c.x * .393) + (c.y * .769) + (c.z * .189), 255.0);
	v.y = fmin((c.x * .349) + (c.y * .686) + (c.z * .168), 255.0);
	v.z = fmin((c.x * .272) + (c.y * .534) + (c.z * .131), 255.0);
	return (v);
}

void			sepia_filtre(t_all *rt)
{
	t_loop		loop;
	t_loop		filter;
	t_vect		c;

	loop.i = -1;
	while (++loop.i < WIN_W)
	{
		loop.j = -1;
		while (++loop.j < WIN_H)
		{
			rt->screen_pixels[loop.i * WIN_W + loop.j] =
			sepia(rt->screen_pixels[loop.i * WIN_W + loop.j]);
			if (SDL_SetRenderDrawColor(rt->rend,
				rt->screen_pixels[loop.i * WIN_W + loop.j].x,
				rt->screen_pixels[loop.i * WIN_W + loop.j].y,
				rt->screen_pixels[loop.i * WIN_W + loop.j].z, 255) != 0)
				sdl_error("Get color failed");
			if (SDL_RenderDrawPoint(rt->rend, loop.i, loop.j) != 0)
				sdl_error("draw point failed");
		}
	}
}
