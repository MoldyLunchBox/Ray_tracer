/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:32:14 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 15:34:02 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

static t_sol	slice_it_square(t_obj *plane, t_sol sol, double size)
{
	t_vect		template;
	t_4vects	slicers;

	template = sorting(plane->direction);
	slicers = slicer_maker(template);
	if (sol.tmin != -1 && !slice_it(plane, size, slicers))
		sol.tmin = -1;
	return (sol);
}

t_sol	plane_slicing(t_obj *obj, t_sol sol)
{
	t_vect	hit_to_slice_point;
	t_sol	t;

	if (obj->size)
		sol = slice_it_square(obj, sol, obj->size);
	if (obj->slice.x || obj->slice.y || obj->slice.z)
	{
		hit_to_slice_point = sub_vect(obj->hit, obj->pos_slice);
		if (vect_scal(hit_to_slice_point, obj->slice) < 0)
		{
			t.tmin = -1;
			return (t);
		}
	}
	return (sol);
}

t_sol	intersection_ray_plan(t_obj *pln, t_ray r)
{
	double	nomi;
	double	dinomi;
	t_sol	sol;

	sol.tmin = -1;
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
	sol = plane_slicing(pln, sol);
	pln->sol = sol;
	pln->t = sol.tmin;
	pln->norm = get_normalized(pln->direction);
	return (sol);
}
