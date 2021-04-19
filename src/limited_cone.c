/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:17:31 by amya              #+#    #+#             */
/*   Updated: 2021/04/19 17:18:25 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol	top_cap_cone(t_cone_top var, t_obj *cone, t_sol sol)
{
	t_vect	len;
	double	dot;

	len = sub_vect(var.plane.hit, var.plane.position);
	dot = sqrt(len.x * len.x + len.y * len.y + len.z * len.z);
	if (dot <= var.radius)
	{
		sol.tmin = var.plan.tmin;
		cone->t = sol.tmin;
		cone->hit = var.plane.hit;
		cone->norm = get_normalized(var.plane.direction);
	}
	return (sol);
}

t_sol	cone_top(t_obj *cone, t_ray r, t_sol sol, t_vect top)
{
	t_vect		top_vect;
	double		distance ;
	t_cone_top	var;

	var.plane.position = top;
	var.plane.direction =cone->direction;
	var.plane.slice = (t_vect){0, 0, 0};
	var.plan = intersection_ray_plan(&var.plane, r);
	if (var.plan.tmin != -1)
	{
		top_vect = sub_vect(cone->position, top);
		distance = sqrt(top_vect.x * top_vect.x + top_vect.y
				* top_vect.y + top_vect.z * top_vect.z);
		var.radius = (distance / cos(cone->radius * PI / 180));
		var.radius = sqrt((var.radius * var.radius) - (distance * distance));
		sol = top_cap_cone(var, cone, sol);
	}
	return (sol);
}

t_sol	bottom_cap_cone(t_cone_bottom var, t_obj *cone, t_sol sol)
{
	t_vect	len;
	double	dot;

	len = sub_vect(var.plane.hit, var.plane.position);
	 dot = sqrt(len.x * len.x + len.y * len.y + len.z * len.z);
	if (dot <= var.radius)
	{
		sol.tmin = var.plan.tmin;
		cone->t = sol.tmin;
		cone->hit = var.plane.hit;
		var.plane.direction = vect_mult_val(var.plane.direction, -1);
		cone->norm = get_normalized(var.plane.direction);
	}
	return (sol);
}

t_sol	cone_bottom(t_obj *cone, t_ray r, t_sol sol, t_vect bottom)
{
	t_vect			bottom_vect;
	double			distance ;
	t_cone_bottom	var;

	var.plane.position = bottom;
	var.plane.direction =cone->direction;
	var.plane.slice = (t_vect){0, 0, 0};
	var.plan = intersection_ray_plan(&var.plane, r);
	if (var.plan.tmin != -1)
	{
		bottom_vect = sub_vect(cone->position, bottom);
		distance = sqrt(bottom_vect.x * bottom_vect.x + bottom_vect.y
				* bottom_vect.y + bottom_vect.z * bottom_vect.z);
		var.radius = (distance / cos(cone->radius * PI / 180));
		var.radius = sqrt((var.radius * var.radius) - (distance * distance));
		sol = bottom_cap_cone(var, cone, sol);
	}
	return (sol);
}

t_sol	limited_object_cone(t_obj *cone, t_ray r, t_sol sol)
{
	t_vect	top;
	t_vect	dir;
	t_vect	bottom;
	double	result_top;
	double	result_bottom;

	dir = vect_mult_val(cone->direction, cone->size);
	bottom = add_vect(cone->position,
			vect_mult_val(cone->direction, -cone->size));
	top = add_vect(cone->position, dir);
	result_top = vect_scal(sub_vect(top, cone->hit), cone->direction);
	result_bottom = vect_scal(sub_vect(bottom, cone->hit),
			vect_mult_val(cone->direction, -1));
	sol = out_of_range(result_top, result_bottom, sol);
	if (result_top < 0)
		sol = cone_top(cone, r, sol, top);
	if (result_bottom < 0)
		sol = cone_bottom(cone, r, sol, bottom);
	return (sol);
}
