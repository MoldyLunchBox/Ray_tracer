/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:32:14 by amya              #+#    #+#             */
/*   Updated: 2021/04/16 14:19:27 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol	plane_slicing(t_obj *obj)
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

// t_sol	intersection_ray_plan(t_obj *pln, t_ray r)
// {
// 	double	nomi;
// 	double	dinomi;
// 	t_sol	sol;

// 	sol.tmin = -1;
// 	nomi = vect_scal(sub_vect(r.origine, pln->position),
// 			pln->direction);
// 	dinomi = vect_scal(r.direction, pln->direction);
// 	if ((dinomi == 0) || (nomi <= 0 && dinomi < 0)
// 		|| (nomi >= 0 && dinomi > 0))
// 		return (sol);
// 	sol.tmin = -nomi / dinomi;
// 	if (sol.tmin < 0)
// 		return (sol);
// 	pln->hit = add_vect(r.origine,
// 			vect_mult_val(r.direction, sol.tmin));
// 	pln->t = sol.tmin;
// 	pln->sol = sol;
// 	if (pln->slice.x || pln->slice.y || pln->slice.z)
// 		sol = plane_slicing(pln);
// 	pln->norm = get_normalized(pln->direction);
// 	return (sol);
// }
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
			
	// if (slice_plane(pln) == -1)
	// 	return (sol);
	// if (is_slider == 1 && vect_scal(sub_vect(pln->pos_slice,
	// pln->hit), pln->slice) <= 0.0)
	// 	return (sol);
        pln->t = sol.tmin;
	pln->sol = sol;
	pln->norm = get_normalized(pln->direction);
	return (sol);
}

