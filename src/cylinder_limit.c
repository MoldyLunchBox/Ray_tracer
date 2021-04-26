/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_limit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:59:47 by amya              #+#    #+#             */
/*   Updated: 2021/04/20 16:54:11 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol	bottom_cap(t_obj *cyl, t_vect bottom, t_ray r, t_sol sol)
{
	t_obj	plane;
	t_sol	plan;
	t_vect	len;
	double	dot;

	plane.position = bottom;
	plane.direction = cyl->direction;
	plane.slice = (t_vect){0, 0, 0};
	plane.size = 0;
	plan = intersection_ray_plan(&plane, r);
	if (plan.tmin != -1)
	{
		len = sub_vect(plane.hit, plane.position);
		dot = sqrt(len.x * len.x + len.y * len.y + len.z * len.z);
		if (dot <= cyl->radius)
		{
			sol.tmin = plan.tmin;
			cyl->t = sol.tmin;
			cyl->hit = plane.hit;
			plane.direction = vect_mult_val(plane.direction, -1);
			cyl->norm = get_normalized(plane.direction);
		}
	}
	return (sol);
}

t_sol	top_cap(t_obj *cyl, t_vect top, t_ray r, t_sol sol)
{
	t_obj	plane;
	t_sol	plan;
	t_vect	len;
	double	dot;

	plane.position = top;
	plane.direction = cyl->direction;
	plane.slice = (t_vect){0, 0, 0};
	plane.size = 0;
	plan = intersection_ray_plan(&plane, r);
	if (plan.tmin != -1)
	{
		len = sub_vect(plane.hit, plane.position);
		dot = sqrt(len.x * len.x + len.y * len.y + len.z * len.z);
		if (dot <= cyl->radius)
		{
			sol.tmin = plan.tmin;
			cyl->t = sol.tmin;
			cyl->hit = plane.hit;
			cyl->norm = get_normalized(plane.direction);
		}
	}
	return (sol);
}

t_sol	limited_object(t_obj *cyl, t_ray r, t_sol sol, t_vect top)
{
	t_vect	dir;
	t_vect	bottom;
	double	result_top;
	double	result_bottom;

	dir = vect_mult_val(cyl->direction, cyl->size);
	bottom = add_vect(cyl->position, vect_mult_val
			(cyl->direction, -cyl->size));
	top = add_vect(cyl->position, dir);
	result_top = vect_scal(sub_vect(top, cyl->hit), cyl->direction);
	result_bottom = vect_scal(sub_vect(bottom, cyl->hit), vect_mult_val
			(cyl->direction, -1));
	if (result_top < 0 || result_bottom < 0)
	{
		sol.tmin = -1;
		sol.tmax = -1;
	}
	if (result_top < 0)
		sol = top_cap(cyl, top, r, sol);
	if (result_bottom <0)
		sol = bottom_cap(cyl, bottom, r, sol);
	return (sol);
}
