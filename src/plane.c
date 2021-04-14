/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:58 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/14 14:45:49 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

double		slice_plane(t_obj *pln)
{
	t_vect dir_l;
	t_vect dir_r;
	t_vect dir_u;
	t_vect dir_d;

	dir_r = get_normalized(vect_cross(pln->direction, (t_vect){0, 0, 1}));
	if (pln->size != 0 && vect_scal(sub_vect(add_vect(pln->position,
	vect_mult_val(dir_r, pln->half_size)), pln->hit), dir_r) <= 0.0)
		return (-1);
	dir_l = get_normalized(vect_cross(pln->direction, (t_vect){0, 0, -1}));
	if (pln->size != 0 && vect_scal(sub_vect(add_vect(pln->position,
	vect_mult_val(dir_l, pln->half_size)), pln->hit), dir_l) <= 0.0)
		return (-1);
	dir_u = get_normalized(vect_cross(pln->direction, (t_vect){1, 0, 0}));
	if (pln->size != 0 && vect_scal(sub_vect(add_vect(pln->position,
	vect_mult_val(dir_u, pln->half_size)), pln->hit), dir_u) <= 0.0)
		return (-1);
	dir_d = get_normalized(vect_cross(pln->direction, (t_vect){-1, 0, 0}));
	if (pln->size != 0 && vect_scal(sub_vect(add_vect(pln->position,
	vect_mult_val(dir_d, pln->half_size)), pln->hit), dir_d) <= 0.0)
		return (-1);
	return (0);
}
t_sol		plane_slicing(t_obj *obj)
{
	t_vect	hit_to_slice_point;
	t_sol	t;
 
	hit_to_slice_point = sub_vect(obj->hit, obj->pos_slice);
	if (vect_scal(hit_to_slice_point, obj->slice) < 0)
	{
		t.tmin = -1;
		return (t);
	}
	return (t);
}
t_sol		intersection_ray_plan(t_obj *pln, t_ray r)
{
	double	nomi;
	double	dinomi;
	double	t;
	// int		is_slider;
	t_sol	sol;

	sol.tmin = -1;
	// is_slider = (!pln->slice.x && !pln->slice.y && !pln->slice.z) ? 0 : 1;
	nomi = vect_scal(sub_vect(r.origine, pln->position),
			pln->direction);
	dinomi = vect_scal(r.direction, pln->direction);
	if ((dinomi == 0) || (nomi <= 0 && dinomi < 0)
			|| (nomi >= 0 && dinomi > 0))
		return (sol);
	sol.tmin = -nomi / dinomi;
	if (sol.tmin < 0)
		return (sol);
	pln->hit = add_vect(r.origine,
			vect_mult_val(r.direction, sol.tmin));
	pln->t = sol.tmin;
	pln->sol = sol;
	// if (slice_plane(pln) == -1)
	// 	return (sol);
	// if (pln->slice.x || pln->slice.y || pln->slice.z)
	// 	sol = plane_slicing(pln);
	// if (is_slider == 1 && vect_scal(sub_vect(pln->pos_slice,
	// pln->hit), pln->slice) <= 0.0)
	// 	return (sol);
	pln->norm = get_normalized(pln->direction);
	return (sol);
}
