/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:40:26 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/17 16:51:34 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		error_check(char **ar, t_data *data)
{
	int		j;
	int		dot;
	int		i;

	i = -1;
	while (ar && ar[++i])
	{
		dot = 1;
		j = 0;
		while (ar[i][j])
		{
			if (!ft_isdigit(ar[i][j]))
			{
				if ((ar[i][j] == '-' && j == 0) || (ar[i][j] == '.'
				&& dot && j != 0 && ft_isdigit(ar[i][j + 1])))
					;
				else
					call_error(data);
				if (ar[i][j] == '.')
					dot--;
			}
			j++;
		}
	}
	return (i);
}

t_vec	split_data(t_data *data, char *str)
{
	int		i;
	char	**ar;
	t_vec	ret;

	ar = ft_strsplit(str, ' ');
	i = error_check(ar, data);
	if (i != 3)
		call_error(data);
	ret.x = ft_atof(ar[0]);
	ret.y = ft_atof(ar[1]);
	ret.z = ft_atof(ar[2]);
	free_2d(ar);
	return (ret);
}

double	get_closest(t_data *data, int x, int y, t_obj **save)
{
	double	t1;
	double	t;
	t_obj	*head;

	data->ray = get_ray(x, y, data->camera);
	t1 = -1;
	head = data->obj;
	while (head)
	{
		t = head->inter(&(data->ray), head);
		if ((t <= t1 && t1 > 0 && t > 0) || (t >= t1 && t1 < 0 && t > 0))
		{
			t1 = t;
			*save = head;
		}
		head = head->next;
	}
	return (t1);
}

void	ray_tracer(t_data *data)
{
	t_raytracer	v;

	v.y = -1;
	while (++v.y < HEIGHT)
	{
		v.x = -1;
		while (++v.x < WIDTH)
		{
			data->t = get_closest(data, v.x, v.y, &(v.save));
			if (data->t != -1)
			{
				v.color = light_it_up(data, v.x, v.y, v.save);
				data->hit = vec_add(data->ray.o,
				vec_product(data->ray.dir, data->t));
				v.shadow.o = data->light->pos;
				v.shadow.dir = normalize(vec_sub(data->hit, data->light->pos));
				v.head = data->obj;
				data->shad = v.shadow;
				get_shadow(v.head, v.save, data, &(v.color));
				data->mlx.d[(v.y * WIDTH + v.x)] = (int)v.color.x << 16
				| (int)v.color.y << 8 | (int)v.color.z;
			}
		}
	}
}

int		main(int ac, char **av)
{
	t_data	*data;
	int		bpp;
	t_mlx	f;

	if (ac != 2)
		exit(0);
	init_data(&data, av[1]);
	ft_checker(&data);
	free_2d(data->tab);
	f.ptr = mlx_init();
	f.win = mlx_new_window(f.ptr, WIDTH, HEIGHT, "RTV1");
	mlx_hook(f.win, 17, 0, ft_close, data);
	f.img = mlx_new_image(f.ptr, WIDTH, HEIGHT);
	f.d = (int *)mlx_get_data_addr(f.img, &bpp, &bpp, &bpp);
	data->mlx = f;
	ray_tracer(data);
	mlx_hook(data->mlx.win, 2, 0, keyhook, data);
	mlx_put_image_to_window(f.ptr, f.win, f.img, 0, 0);
	mlx_loop(f.ptr);
	return (0);
}
