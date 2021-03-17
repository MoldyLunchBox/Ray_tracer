/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:58:13 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/17 17:17:57 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		light_it_up(t_data *data, int x, int y, t_obj *obj)
{
	t_vec	color;
	double	k;
	double	m;

	obj->hit = vec_add(data->ray.o, vec_product(data->ray.dir, data->t));
	if (obj->id == 2)
		obj->n = normalize(vec_sub(vec_sub(obj->hit, obj->pos),
	vec_product(obj->axis, dot_product(obj->axis,
	vec_sub(obj->hit, obj->pos)))));
	else if (obj->id == 1)
		obj->n = normalize(vec_sub(obj->hit, obj->pos));
	else if (obj->id == 4)
		obj->n = normalize(obj->axis);
	else if (obj->id == 5)
	{
		k = tan((obj->an_ra * M_PI / 180) / 2);
		m = dot_product(data->ray.dir,
		vec_product(obj->axis, data->t)) +
		dot_product(vec_sub(data->ray.o, obj->pos), obj->axis);
		obj->n = normalize(vec_sub(vec_sub(obj->hit,
		obj->pos), vec_product(obj->axis, (1 + k + k) * m)));
	}
	
	color = get_color(data, obj, x, y);
	return (color);
}

t_var_light	*ft_var_light(t_data *data, t_obj *obj, t_var_light *light)
{
	light->ang_norm_light = fmax(0,
	dot_product(normalize(vec_sub(data->light->pos, obj->hit)), obj->n));
	light->l = normalize(vec_sub(data->light->pos, obj->hit));
	light->v = normalize(vec_sub(data->ray.o, obj->hit));
	light->dd = vec_product(obj->n, dot_product(light->l, obj->n));
	light->rm = vec_sub(vec_product(light->dd, 2), light->l);
	light->intensite_pixel = (pow(fmax(0,
	dot_product(light->rm, light->v)), 40));
	return (light);
}

t_vec		get_color(t_data *data, t_obj *obj, int x, int y)
{
	t_var_light		*light;
	t_vec			color;

if (obj->id == 6)
	ft_putendl("");
	light = malloc(sizeof(t_var_light));
	light = ft_var_light(data, obj, light);
	color.x = obj->color.x * 0.3;
	color.y = obj->color.y * 0.3;
	color.z = obj->color.z * 0.3;
	color.x = fmin(255, obj->color.x * light->ang_norm_light + color.x);
	color.y = fmin(255, obj->color.y * light->ang_norm_light + color.y);
	color.z = fmin(255, obj->color.z * light->ang_norm_light + color.z);
	data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16
		| (int)color.y << 8 | (int)color.z;
	color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 16) & 255)
		+ data->light->color.x * light->intensite_pixel);
	color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 8) & 255)
	+ data->light->color.y * light->intensite_pixel);
	color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] & 255)
		+ data->light->color.z * light->intensite_pixel);
	color_limit(&color);
	return (color);
}

void		color_limit(t_vec *color)
{
	if (color->x > 255)
		color->x = 255;
	if (color->y > 255)
		color->y = 255;
	if (color->z > 255)
		color->z = 255;
}

void		get_shadow(t_obj *head, t_obj *s, t_data *data, t_vec *col)
{
	double	t;
	double	len1;
	double	len2;
	t_vec	hit2;

	while (head)
	{
		t = head->inter(&(data->shad), head);
		if (t > 0 && s != head)
		{
			hit2 = vec_add(data->shad.o, vec_product(data->shad.dir, t));
			len1 = dot_product(vec_product(data->shad.dir, t),
			vec_product(data->shad.dir, t));
			len2 = dot_product(vec_sub(data->hit, data->light->pos),
			vec_sub(data->hit, data->light->pos));
			if (len1 < len2)
			{
				col->x = col->x * 0.6;
				col->y = col->y * 0.6;
				col->z = col->z * 0.6;
				break ;
			}
		}
		head = head->next;
	}
}
