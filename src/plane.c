/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:58 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/02 19:07:37 by amya             ###   ########.fr       */
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

t_sol		intersection_ray_plan(t_obj *pln, t_ray r)
{
	double	nomi;
	double	dinomi;
	double	t;
	int		is_slider;
	t_sol	sol;

	sol.tmin = -1;
	is_slider = (!pln->slice.x && !pln->slice.y && !pln->slice.z) ? 0 : 1;
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
	if (slice_plane(pln) == -1)
		return (sol);
	if (is_slider == 1 && vect_scal(sub_vect(pln->pos_slice,
	pln->hit), pln->slice) <= 0.0)
		return (sol);
	pln->norm = get_normalized(pln->direction);
	return (sol);
}
