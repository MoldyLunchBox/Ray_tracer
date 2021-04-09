/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_filter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:45:48 by amya              #+#    #+#             */
/*   Updated: 2021/03/28 17:16:32 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

static void		mb_loop(t_all *rt, t_loop *loop, t_loop *filter, t_vect *c)
{
	t_loop	img;

	img.j = (int)(loop->j - 9 / 2 + filter->j + WIN_W)
		% WIN_W;
	img.i = (int)(loop->i - 9 / 2 + filter->i + WIN_H)
		% WIN_H;
	c->x += rt->screen_pixels[img.i * WIN_W + img.j].x;
	c->y += rt->screen_pixels[img.i * WIN_W + img.j].y;
	c->z += rt->screen_pixels[img.i * WIN_W + img.j].z;
}

int				set_render_draw_color(t_all *rt, t_vect c)
{
	if (SDL_SetRenderDrawColor(rt->rend,
		fmin(255., (int)(c.x / 9.0)), fmin(255., (int)(c.y / 9.0)),
		fmin(255., (int)(c.z / 9.0)), 255) != 0)
		return (-1);
	return (0);
}

void			ft_filter_mb(t_all *rt)
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
			init_vect(&c, 0.0, 0.0, 0.0);
			filter.i = -1;
			while (++filter.i < 9)
			{
				filter.j = -1;
				while (++filter.j < 9)
					mb_loop(rt, &loop, &filter, &c);
				if (set_render_draw_color(rt, c) != 0)
					sdl_error("Get color failed");
				if (SDL_RenderDrawPoint(rt->rend, loop.i, loop.j) != 0)
					sdl_error("draw point failed");
			}
		}
	}
}
