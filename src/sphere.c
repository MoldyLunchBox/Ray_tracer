/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:24:13 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 15:34:46 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

double	sphere_slicing(t_sol sol, t_obj *sph, t_ray r)
{
	t_vect	hit_to_pos_slice;

	sph->norm = get_normalized(sub_vect(sph->hit, sph->position));
	hit_to_pos_slice = sub_vect(sph->hit, sph->pos_slice);
	if (vect_scal(hit_to_pos_slice, sph->slice) > 0)
		return (sol.tmin);
	sph->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmax));
	hit_to_pos_slice = sub_vect(sph->hit, sph->pos_slice);
	sph->norm = get_normalized(sub_vect(sph->hit, sph->position));
	sph->norm = vect_mult_val(sph->norm, -1);
	if (vect_scal(hit_to_pos_slice, sph->slice) > 0)
		return (sol.tmax);
	else
		return (-1);
}

t_sol	intersection_ray_sphere(t_obj *sph, t_ray r)
{
	t_vect		abc;
	double		delta;
	t_sol		sol;

	abc.x = get_norm_2(r.direction);
	abc.y = 2 * vect_scal(r.direction, sub_vect(r.origine, sph->position));
	abc.z = get_norm_2(sub_vect(r.origine, sph->position))
		- (sph->radius * sph->radius);
	delta = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(delta, abc);
	sph->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmin));
	sph->norm = get_normalized(sub_vect(sph->hit, sph->position));
	if (sph->slice.x || sph->slice.y || sph->slice.z)
		sol.tmin = sphere_slicing(sol, sph, r);
	return (sol);
}
