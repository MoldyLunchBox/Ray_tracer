/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:56:14 by amya              #+#    #+#             */
/*   Updated: 2021/04/20 16:48:21 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol	slice_it_four_times(t_obj *plane, t_ray ray, double size)
{
	t_vect		template;
	t_4vects	slicers;
	t_sol		sol;

	template = sorting(plane->direction);
	slicers = slicer_maker(template);
	sol = intersection_ray_plan(plane, ray);
	if (sol.tmin != -1 && !slice_it(plane, size, slicers))
		sol.tmin = -1;
	return (sol);
}

t_obj	box_sides(t_vect plane_direction, t_obj *box, t_ray ray)
{
	t_vect	plane_position;
	t_obj	plane;

	plane_position = add_vect(vect_mult_val(plane_direction,
				box->size), box->position);
	plane.direction = plane_direction;
	plane.position = plane_position;
	plane.size = 0;
	plane.slice = (t_vect){0, 0, 0};
	plane.sol = slice_it_four_times(&plane, ray, box->size);
	return (plane);
}

void	init_box(t_obj plane, t_obj *box, t_sol *closest)
{
	box->direction = plane.direction;
	box->hit = plane.hit;
	box->norm = plane.norm;
	box->t = plane.t;
	closest->tmin = plane.sol.tmin;
}

t_sol	intersection_box(t_obj *box, t_ray ray)
{
	t_obj	plane;
	t_sol	min;

	min.tmin = -1;
	plane = box_sides((t_vect){0, 1, 0}, box, ray);
	if (min.tmin == -1 || min.tmin > plane.sol.tmin)
		init_box(plane, box, &min);
	plane = box_sides((t_vect){0, -1, 0}, box, ray);
	if (min.tmin == -1 || (min.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &min);
	plane = box_sides((t_vect){1, 0, 0}, box, ray);
	if (min.tmin == -1 || (min.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &min);
	plane = box_sides((t_vect){-1, 0, 0}, box, ray);
	if (min.tmin == -1 || (min.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &min);
	plane = box_sides((t_vect){0, 0, -1}, box, ray);
	if (min.tmin == -1 || (min.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &min);
	plane = box_sides((t_vect){0, 0, 1}, box, ray);
	if (min.tmin == -1 || (min.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &min);
	return (min);
}
