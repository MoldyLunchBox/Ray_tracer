/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:48:25 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/06 13:07:33 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void			cylinder_surface_normal(t_obj *obj, double t, t_ray ray)
{
	obj->hit = add_vect(ray.origine, vect_mult_val(ray.direction, t));
	obj->norm = get_normalized(sub_vect(sub_vect(obj->hit, obj->position),
			vect_mult_val(obj->direction, vect_scal(obj->direction,
			sub_vect(obj->hit, obj->position)))));
	obj->norm = vect_mult_val(obj->norm, -1);
}
t_sol			look_for_negative(t_obj *obj, t_all data, t_sol t, t_ray ray)
{
	t_obj	*looper;
	t_sol	t2;

	looper = data.obj;
	while (looper->next)
	{
		if (ft_strequ(looper->name, (char const *)"sphere") && looper->is_negative)
		{
			t2 = looper->inter(looper, ray);
			if (t.tmin <= t2.tmax && t.tmin >= t2.tmin)
			{
				t.tmin = -1;
				if (t.tmax <= t2.tmax && t.tmax >= t2.tmin)
				{
					t.tmax = -1;
					return (t);
				}
				cylinder_surface_normal(obj, t.tmax, ray);
				return (t);
			}
			return (t);
		}
		looper = looper->next;
	}
	return (t);
}
double			find_obj_scnd(t_all data, t_ray ray, t_ray to_light, t_obj *pos)
{
	t_obj		*header;
	t_sol		t;
	double		t1;

	t1 = -1;
	header = data.obj;
	while (header->next)
	{
		if (header->id == pos->id && (header = header->next))
			continue;
		if (!ft_strequ(header->name, (char const *)"sphere"))
			t = header->inter(header, to_light);
		else
		{
			t.tmin = -1;
			t.tmax = -1;	
		}
		if (t.tmin != -1 && ft_strequ(header->name, (char const *)"cylinder"))
		{
			t = look_for_negative(header, data, t, to_light);
			if (t.tmin == -1)
			{
				t.tmin = t.tmax;
			}
		}
		if (t.tmin != -1)
		{
			if (t1 == -1)
				t1 = t.tmin;
			else
			{
				if (t1 > t.tmin)
					t1 = t.tmin;
			}
		}
		header = header->next;
	}
	return (t1);
}


t_obj			*find_closest(t_all data, t_ray ray)
{
	t_obj		*pos;
	t_obj		*header;
	t_sol		t;
	double		t1;

	t1 = -1;
	t.tmin = -1;
	t.tmax = -1;
	header = data.obj;
	pos = header;
	while (header->next)
	{
		// if (!ft_strequ(header->name, (char const *)"sphere"))
			t = header->inter(header, ray);
		// else
		// {
		// 	t.tmin = -1;
		// 	t.tmax = -1;
		// }
		// if (t.tmin != -1 && ft_strequ(header->name, (char const *)"cylinder"))
		// {
		// 	t = look_for_negative(header, data, t, ray);
		// 	if (t.tmin == -1)
		// 	{
		// 		t.tmin = t.tmax;
		// 	}
		// }
		if (t.tmin != -1)
		{
			t1 == -1 ? pos = header : 0;
			t1 == -1 ? t1 = t.tmin : 0;
			t1 > t.tmin ? pos = header : 0;
			t1 > t.tmin ? t1 = t.tmin : 0;
		}
		header = header->next;
	}
	pos->t = t1;
	return (pos);
}

t_vect			disruption(t_obj *obj, t_vect col)
{
	double	res;
	double	res2;
	t_vect	vec;
	double	test;

	if (obj->hit.x < 0)
		res = ((int)obj->hit.x - 1) % 2;
	else
		res = ((int)obj->hit.x) % 2;
	t_vect	hit_to_pos=sub_vect(obj->hit, obj->position);
	normalize(&hit_to_pos);
	test = vect_scal(hit_to_pos, obj->norm);
	if (test <= 0.001 && test >= -0.001)
	{
		if (obj->hit.z < 0)
			res2 = ((int)obj->hit.z - 1) % 2;
		else
			res2 = ((int)obj->hit.z) % 2;
		if ((res && res2) || (!res && !res2))
			col = (t_vect){0, 0, 0};
		else
			col = (t_vect){255, 255, 255};
	}
	else
	{
		if (obj->hit.y < 0)
			res2 = ((int)obj->hit.y - 1) % 2;
		else
			res2 = ((int)obj->hit.y) % 2;
		if ((res && res2) || (!res && !res2))
			col = (t_vect){0, 0, 0};
		else
			col = (t_vect){255, 255, 255};
	}
	return (col);
}

t_vect			reflection(t_all data, t_obj *obj, int nbrbonds, t_ray ray)
{
	t_vect	light_plus_norm;
	t_vect	ray_copy;
	t_ray	reflected_ray;
	t_vect	color;

	ray_copy = ray.direction;
	light_plus_norm = add_vect(ray_copy, vect_mult_val(obj->norm, 2));
	reflected_ray.origine = vect_mult_val(obj->hit, 0.9);
	reflected_ray.direction = light_plus_norm;
	color = rend_pix(data, reflected_ray, --nbrbonds);
	return color;
}

t_vect			rend_pix(t_all data, t_ray ray, int nbrbonds)
{
	t_vect		col;
	t_obj		*pos;

	if (nbrbonds == 0)
		return ((t_vect){0, 0, 0});
	pos = find_closest(data, ray);
	col = (t_vect){0, 0, 0};
	// pos->color = disruption(pos, pos->color_copy);
	if (pos->t != -1)
	{
		if (pos->type == 2)
		{
			col = add_vect(vect_mult_val(pos->color, pos->refl), reflection(data, pos, nbrbonds, ray));
		}
		// else if (pos->type == 3)
		// 	col = add_vect(vect_mult_val(pos->color, pos->trans),);
		else if (pos->type != 3)
		{
			col = light_obj(pos, data, ray, pos->t);
			col = on_shadow(pos, data, ray, col);
		}
	}
	return (safe_color(col));
}

void			set_pixel(t_all data, t_vect col, t_vect_i var, t_ray ray)
{
	int			iten;

	if (data.light->type == 1)
	{
		iten = light_direct(data, ray);
		col = vect_mult_val(col, iten);
	}
	if (SDL_SetRenderDrawColor(data.rend, col.x, col.y, col.z, 255) != 0)
		sdl_error("Get color failed");
	if (SDL_RenderDrawPoint(data.rend, var.x, var.y) != 0)
		sdl_error("draw point failed");
	data.screen_pixels[var.x * WIN_W + var.y] = col;
}

t_vect		negative_filter(t_vect col)
{
	col.x = 255 - col.x;
	col.y = 255 - col.y;
	col.z = 255 - col.z;
	return (col);
}

void			*raytracing(void *dataa)
{
	t_vect_i	var;
	t_ray		ray;
	t_vect		col;
	t_all		data;

	data = *((t_all *)(dataa));
	var.x = data.start - 1;
	while (++var.x < data.end)
	{
		var.y = -1;
		while (++var.y < WIN_H)
		{
			init_vect(&col, 0., 0., 0.);
			var.z = -1;
			while (++var.z < ((data.aalias || data.deep) ? NBR_RAYS : 1))
			{
				ray = new_ray(var.x, var.y, data);
				col = add_vect(col, vect_mult_val(rend_pix(data, ray, 6), 1. /
					((data.aalias || data.deep) ? NBR_RAYS : 1)));
			}
			// col = negative_filter(col);
			set_pixel(data, col, var, ray);
		}
	}
	filtre(&data);
	return (NULL);
}
