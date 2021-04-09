/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:43:23 by amya              #+#    #+#             */
/*   Updated: 2021/03/28 15:43:35 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

char	*ft_copy_imgdata(t_rt *rt, int *img, int width, int height)
{
	int		i;
	char	*buffer;
	int		*data;

	buffer = malloc(4 * width * height);
	if (!buffer)
		free_garbage(rt);
	garbage_collector(rt, buffer);
	data = (int*)buffer;
	i = -1;
	while (++i < width * height)
		data[i] = img[i];
	return (buffer);
}

int		select_kth(int *data)
{
	t_loop	p;
	int		x;

	p.i = -1;
	while (++p.i < FILTERSIZE)
	{
		p.j = p.i + 1;
		while (--p.j > 0 && data[p.j - 1] > data[p.j])
		{
			x = data[p.j];
			data[p.j] = data[p.j - 1];
			data[p.j - 1] = x;
		}
	}
	return (FILTERSIZE / 2);
}

void	ft_fill_data(int *data, t_loop *loop, int **col, int mlx_width)
{
	int		indice;
	int		c1;
	int		c2;
	int		c3;

	indice = loop->j * mlx_width + loop->i;
	c1 = clamp(col[1][select_kth(col[1])], 255, 0);
	c2 = clamp(col[2][select_kth(col[2])], 255, 0);
	c3 = clamp(col[3][select_kth(col[3])], 255, 0);
	data[indice] = rgb_int(c1, c2, c3);
}

void	ft_filter_loop(t_rt *rt, int **c, int *d, t_loop *l)
{
	t_loop		filter_l;
	t_loop		img_loop;
	int			n;

	n = 0;
	filter_l.j = -1;
	while (++filter_l.j < FILTER_C_H)
	{
		filter_l.i = -1;
		while (++filter_l.i < FILTER_C_W)
		{
			img_loop.i = (l->i - FILTER_C_W / 2 + filter_l.i + WIN_W)
			% WIN_W;
			img_loop.j = (l->j - FILTER_C_H / 2 + filter_l.j + WIN_H)
			% WIN_H;
			c[1][n] = r(c[0][img_loop.j * WIN_W + img_loop.i]);
			c[2][n] = g(c[0][img_loop.j * WIN_W + img_loop.i]);
			c[3][n] = b(c[0][img_loop.j * WIN_W + img_loop.i]);
			n++;
		}
	}
	ft_fill_data(d, l, c, WIN_W);
}

void	cartoon_filter(t_all *rt)
{
	t_loop	loop;
	int		*col[4];

	if (!(col[0] = (int *)ft_copy_imgdata(rt, data, WIN_W, WIN_H)) ||
	!(col[1] = (int *)ft_memalloc(4 * WIN_H * WIN_W)) ||
	!(col[2] = (int *)ft_memalloc(4 * WIN_H * WIN_W)) ||
	!(col[3] = (int *)ft_memalloc(4 * WIN_H * WIN_W)))
		free_garbage(rt);
	garbage_collector(rt, col[1]);
	garbage_collector(rt, col[2]);
	garbage_collector(rt, col[3]);
	loop.i = -1;
	while (++loop.i < WIN_W)
	{
		loop.j = -1;
		while (++loop.j < WIN_H)
		{
			ft_filter_loop(rt, col, data, &loop);
		}
	}
	free(col[0]);
	free(col[1]);
	free(col[2]);
	free(col[3]);
}
