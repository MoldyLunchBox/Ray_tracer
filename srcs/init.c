/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:13:37 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/11 17:22:10 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_data(t_data **data, char *av)
{
	int			i;
	char		**tab;
	int			count;
	int			fd;

	i = 0;
	fd = open(av, O_RDONLY);
	count = ft_lines(fd);
	fd = open(av, O_RDONLY);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	while (get_next_line(fd, &tab[i]))
		i++;
	close(fd);
	tab[i] = NULL;
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->tab = tab;
	(*data)->camera = (t_camera *)malloc(sizeof(t_camera));
	(*data)->obj = malloc(sizeof(t_obj));
	(*data)->obj = NULL;
	(*data)->light = malloc(sizeof(t_light));
	(*data)->camera->look_from = (t_vec){0, 5, 0};
	(*data)->camera->cam_dir = (t_vec){0, 0, 0};
	(*data)->camera->up = (t_vec){0, 1, 1e-6};
	(*data)->camera->fov = 20;
}

t_vec	get_camera_direction(t_camera cam, t_vec get_ray)
{
	t_vec	ray;

	cam.low_left_corner = vec_add(cam.look_from, get_ray);
	ray = vec_sub(cam.low_left_corner, cam.look_from);
	return (ray);
}

double	ft_min_ray(double t1, double t2, double t)
{
	if (t2 <= 0 && t1 <= 0)
		return (-1);
	else if (t1 >= 0 && t2 <= 0)
		t = t1;
	else if (t2 >= 0 && t1 <= 0)
		t = t2;
	else
		t = fmin(t1, t2);
	return (t);
}

t_ray	get_ray(double u, double v, t_camera *camera)
{
	t_get_ray	r;

	u = 2 * (u + 2) / (HEIGHT) - 1;
	v = 1 - 2 * (v + 2) / (HEIGHT);
	r.new.o = camera->look_from;
	r.half_h = 2.0 * tan((camera->fov * M_PI / 180) / 2);
	r.half_w = r.half_h;
	r.cam_w = normalize(vec_sub(camera->look_from, camera->cam_dir));
	r.cam_u = normalize(vec_cross(camera->up, r.cam_w));
	r.cam_v = vec_cross(r.cam_w, r.cam_u);
	r.horizontal = vec_product(r.cam_u, r.half_w);
	r.vertical = vec_product(r.cam_v, r.half_h);
	camera->low_left_corner = vec_sub(camera->look_from, r.cam_w);
	camera->low_left_corner = vec_sub(camera->low_left_corner,
	vec_product(r.horizontal, 1 / 2));
	camera->low_left_corner = vec_sub(camera->low_left_corner,
	vec_product(r.vertical, 1 / 2));
	r.new.dir = vec_sub(camera->low_left_corner, r.new.o);
	r.new.dir = vec_sub(r.new.dir, vec_product(r.horizontal, u));
	r.new.dir = vec_add(r.new.dir, vec_product(r.vertical, v));
	r.new.dir = normalize(r.new.dir);
	return (r.new);
}

int		init_obj(t_obj *temp, int i, t_data *data, int id)
{
	temp->id = id;
	temp->pos = split_data(data, data->tab[++i]);
	temp->trans = split_data(data, data->tab[++i]);
	temp->rot = split_data(data, data->tab[++i]);
	temp->color = split_data(data, data->tab[++i]);
	if (id != 4 && id != 6 && id != 7)
	{
		i++;
		if (str_isnum(data->tab[i]))
			temp->an_ra = ft_atof(ft_strdup(data->tab[i]));
		else
			call_error(data);
	}
	if (id == 6 || id == 7)
		{
			i++;
			temp->radius = ft_atof(ft_strdup(data->tab[i]));
			i++;
			temp->radius2 = ft_atof(ft_strdup(data->tab[i]));
		}
	if (id != 1)
	{
		if (id == 6 || id == 7)
			temp->axis = split_data(data, data->tab[++i]);
		else
		{
			temp->axis = split_data(data, data->tab[++i]);
			temp->axis = ft_transform_ray(temp);
		}

	}
	if (id == 1)
	{
		temp->pos = ft_translate(temp->pos, temp->trans);
	}
	return (i);
}


