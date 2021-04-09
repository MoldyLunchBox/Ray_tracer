/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:48:25 by yoelguer          #+#    #+#             */
/*   Updated: 2021/03/28 19:12:51 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_vect			ft_reflection(t_obj *pos, t_all data, t_ray ray, int nbrbonds)
{
	t_vect		col;
	t_ray		ray_reflected;
	t_vect		dir_reflected;

	dir_reflected = sub_vect(ray.direction, vect_mult_val(pos->norm,
		2 * vect_scal(ray.direction, pos->norm)));
	init_ray(&ray_reflected, add_vect(pos->hit,
		vect_mult_val(pos->norm, 0.001)), dir_reflected);
	col = rend_pix(data, ray_reflected, nbrbonds - 1);
	return (safe_color(col));
}

t_vect			ft_refraction(t_obj *pos, t_all data, t_ray ray, int nbrbonds)
{
	t_vect		col;
	t_trns_parm tr;

	tr.n1 = 1;
	tr.n2 = 1.01;
	tr.nm_trns = pos->norm;
	if (vect_scal(ray.direction, pos->norm) > 0)
	{
		tr.n1 = tr.n2;
		tr.n2 = 1;
		tr.nm_trns = vect_mult_val(pos->norm, -1);
	}
	tr.rad = 1 - pow(tr.n1 / tr.n2, 2) *
		(1 - pow(vect_scal(tr.nm_trns, ray.direction), 2));
	if (tr.rad > 0)
	{
		tr.tt = vect_mult_val(sub_vect(ray.direction, vect_mult_val(tr.nm_trns,
			vect_scal(ray.direction, tr.nm_trns))), (tr.n1 / tr.n2));
		tr.tn = vect_mult_val(tr.nm_trns, sqrt(tr.rad));
		tr.dir_refr = sub_vect(tr.tt, tr.tn);
		init_ray(&(tr.ray_refr), sub_vect(pos->hit,
			vect_mult_val(tr.nm_trns, 0.001)), tr.dir_refr);
		col = rend_pix(data, tr.ray_refr, nbrbonds - 1);
	}
	return (safe_color(col));
}

double			randfrom(double min, double max)
{
	double	range;
	double	div;

	range = (max - min);
	div = RAND_MAX / range;
	return (min + (rand() / div));
}

t_ray			new_ray(int i, int j, t_all data)
{
	t_ray		ray;
	t_2d_d		an_alis;
	t_2d_d		deep;
	t_2d_i		var;

	init_2d_vect(&an_alis);
	init_2d_vect(&deep);
	if (data.aalias)
	{
		an_alis.x = randfrom(0., 1.);
		an_alis.y = randfrom(0., 1.);
	}
	if (data.deep)
	{
		deep.x = randfrom(2.5, -2.5);
		deep.y = randfrom(2.5, -2.5);
	}
	var.x = i;
	var.y = j;
	ray = init_rayy(var, data.camera, an_alis, deep);
	return (ray);
}
