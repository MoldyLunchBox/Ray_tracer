/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:49:31 by amya              #+#    #+#             */
/*   Updated: 2021/04/19 17:49:35 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_vect	reflection(t_all data, t_obj *obj, int nbrbonds, t_ray ray)
{
	t_ray	reflected_ray;
	t_vect	color;
	double	n_dot_d;

	n_dot_d = vect_scal(ray.direction, obj->norm) * 2;
	reflected_ray.direction = vect_mult_val(obj->norm, n_dot_d);
	reflected_ray.direction = sub_vect(ray.direction, reflected_ray.direction);
	reflected_ray.origine = add_vect(obj->hit, vect_mult_val(obj->norm, 0.01));
	color = rend_pix(data, reflected_ray, --nbrbonds);
	return (color);
}

static t_ray	calc_refracted(t_obj *obj, t_ray ray, t_vect ref_norm)
{
	double		n1;
	double		n2;
	t_ray		refracted_ray;
	double		r;

	n2 = 1.3;
	n1 = 1;
	if (vect_scal(ray.direction, obj->norm) > 0)
	{
		n1 = 1.3;
		n2 = 1;
	}
	r = 1 - pow(n1 / n2, 2) * (1 - pow(vect_scal(ref_norm, ray.direction), 2));
	refracted_ray.origine = sub_vect(obj->hit, vect_mult_val(ref_norm, 0.001));
	refracted_ray.direction = sub_vect(vect_mult_val(sub_vect(ray.direction,
					vect_mult_val(ref_norm, vect_scal(ray.direction, ref_norm))
					), n1 / n2), vect_mult_val(ref_norm, sqrt(r)));
	return (refracted_ray);
}

t_vect	refraction(t_all data, t_obj *obj, int limit, t_ray ray)
{
	t_refraction	v;
	double			r;

	v.n1 = 1;
	v.n2 = 1.3;
	v.ref_norm = (t_vect){obj->norm.x, obj->norm.y, obj->norm.z};
	if (vect_scal(ray.direction, obj->norm) > 0)
	{
		v.n1 = 1.3;
		v.n2 = 1;
		v.ref_norm = vect_mult_val(obj->norm, -1);
	}
	r = 1 - pow(v.n1 / v.n2, 2) * (1 - pow(
				vect_scal(v.ref_norm, ray.direction), 2));
	if (r > 0)
	{
		v.refracted_ray = calc_refracted(obj, ray, v.ref_norm);
		v.col = rend_pix(data, v.refracted_ray, limit - 1);
	}
	return (safe_color(v.col));
}

t_vect	rend_pix(t_all data, t_ray ray, int nbrbonds)
{
	t_vect		col;
	t_obj		*pos;

	if (nbrbonds == 0)
		return ((t_vect){0, 0, 0});
	col = direct_light(ray, data, data.light);
	pos = find_closest(data, ray);
	if (pos->t != -1)
	{
		if (pos->disruption)
			pos->color = disruption(pos, pos->color_copy);
		if (pos->type == 2)
			col = add_vect(vect_mult_val(pos->color, pos->refl),
					reflection(data, pos, nbrbonds, ray));
		else if (pos->type == 3)
			col = add_vect(vect_mult_val(pos->color, pos->trans),
					refraction(data, pos, nbrbonds, ray));
		else
			col = light_n_shadow(pos, data, ray, col);
	}
	return (safe_color(col));
}

void	*raytracing(void *dataa)
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
			ray = new_ray(var.x, var.y, data);
			col = add_vect(col, rend_pix(data, ray, 6));
			col = filter(&data, col, var);
			set_pixel(data, col, var, ray);
		}
	}
	return (NULL);
}
