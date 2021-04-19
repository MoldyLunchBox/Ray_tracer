/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:38:38 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/17 17:56:48 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol	all_cone(t_obj *cone, t_ray r)
{
	t_sol	sol;
	t_vect	abc;
	t_vect	cp;
	t_vect	vd;
	double	angle;

	angle = cone->radius * PI / 180;
	vd = sub_vect(r.origine, cone->position);
	cp.x = vect_scal(vd, cone->direction);
	cp.y = vect_scal(r.direction, cone->direction);
	abc.x = (get_norm_2(sub_vect(r.direction,
					vect_mult_val(cone->direction, cp.y))) * pow(cos(angle), 2))
		- (pow(cp.y, 2) * pow(sin(angle), 2));
	abc.y = 2 * ((vect_scal(sub_vect(r.direction,
						vect_mult_val(cone->direction, cp.y)), sub_vect(vd,
						vect_mult_val(cone->direction, cp.x)))
				* pow(cos(angle), 2)) - (cp.y * cp.x * pow(sin(angle), 2)));
	abc.z = (get_norm_2(sub_vect(vd, vect_mult_val(cone->direction, cp.x)))
			* pow(cos(angle), 2)) - (pow(cp.x, 2) * pow(sin(angle), 2));
	cp.z = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(cp.z, abc);
	cone->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmin));
	return (sol);
}

double	cone_slicing(t_sol sol, t_obj *cone, t_ray r)
{
	t_vect	hit_to_slice_pos;

	cone->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmin));
	hit_to_slice_pos = sub_vect(cone->hit, cone->pos_slice);
	cone_norm(cone, r, sol.tmin);
	if (vect_scal(hit_to_slice_pos, cone->slice) > 0)
		return (sol.tmin);
	cone->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmax));
	hit_to_slice_pos = sub_vect(cone->hit, cone->pos_slice);
	cone_norm(cone, r, sol.tmax);
	if (vect_scal(hit_to_slice_pos, cone->slice) > 0)
		return (sol.tmax);
	return (-1);
}


t_sol           limited_object_cone(t_obj *cone, t_ray r,t_sol sol)
{
    t_vect top;
    t_vect dir;
    t_vect hit_to_slice_point;
    t_vect bottom;
    double  result_top;
    double  result_bottom;
    dir = vect_mult_val(cone->direction, cone->size);
    bottom = add_vect(cone->position,vect_mult_val(cone->direction, -cone->size));
    top= add_vect(cone->position,dir);
    result_top = vect_scal(sub_vect(top, cone->hit), cone->direction);
    result_bottom = vect_scal(sub_vect(bottom, cone->hit),vect_mult_val(cone->direction,-1));
    if (result_top < 0 || result_bottom<0)
    {
        sol.tmin = -1;
        sol.tmax = -1;
    }
    if (result_top < 0)
    {
    t_obj plane;
    plane.position = top;
    plane.direction =cone->direction;
    t_sol  plan;
    plan = intersection_ray_plan(&plane, r);
    if (plan.tmin != -1)
        {
            double radius;
            t_vect top_vect;
            top_vect = sub_vect(cone->position,top);
            double distance = sqrt(top_vect.x *top_vect.x + top_vect.y * top_vect.y +top_vect.z *top_vect.z);
            radius = (distance/ cos(cone->radius * PI / 180));
            radius = sqrt((radius*radius) -(distance*distance));
            t_vect len;
            len = sub_vect(plane.hit, plane.position);
            double dot = sqrt(len.x*len.x + len.y*len.y + len.z * len.z);
            if (dot <= radius)
            {
                sol.tmin = plan.tmin;
                cone->t = sol.tmin;
                cone->hit = plane.hit;
                cone->norm = get_normalized(plane.direction);
            }
        }
    }
    if (result_bottom <0)
    {
    t_obj plane;
    plane.position = bottom;
    plane.direction =cone->direction;
    t_sol  plan;
    plan = intersection_ray_plan(&plane, r);
    if (plan.tmin != -1)
        {
            double radius;
            t_vect bottom_vect;
            bottom_vect = sub_vect(cone->position,bottom);
            double distance = sqrt(bottom_vect.x *bottom_vect.x + bottom_vect.y * bottom_vect.y +bottom_vect.z *bottom_vect.z);
            radius = (distance/ cos(cone->radius * PI / 180));
            radius = sqrt((radius*radius) -(distance*distance));
            t_vect len;
            len = sub_vect(plane.hit, plane.position);
            double dot = sqrt(len.x*len.x + len.y*len.y + len.z * len.z);
            if (dot <= radius)
            {
                sol.tmin = plan.tmin;
                cone->t = sol.tmin;
                cone->hit = plane.hit;
                plane.direction = vect_mult_val(plane.direction, -1);
                cone->norm = get_normalized(plane.direction);
            }
        }
    }
    return(sol);
}

t_sol	intersection_ray_cone(t_obj *cone, t_ray r)
{
	t_sol	sol;
	t_vect	sly;
	int		is;

	sol = all_cone(cone, r);
	cone_norm(cone, r, sol.tmax);
	// if (cone->slice.x || cone->slice.y || cone->slice.z)
	// 	sol.tmin = cone_slicing(sol, cone, r);
	// if (cone->slice.x || cone->slice.y || cone->slice.z)
	// 	sol = slice_object_cone(cone, r, sol);
	// sol = limited_object_cone(cone, r, sol);
	// sly = cone->slice;
	// if (!sly.x && !sly.y && !sly.z)
	// 	is = 0;
	// else
	// 	is = 1;
	// if (is == 1 && vect_scal(sub_vect(cone->pos_slice, cone->hit), sly) <= 0.0)
	// 	return (intersection_cone(cone, r, sol, sly));
	// if (cone->size != 0 && vect_scal(sub_vect(add_vect(cone->position,
	// 	vect_mult_val(cone->direction, cone->half_size)), cone->hit),
	// 			cone->direction) <= 0.0)
	// 	return (intersection_cone2(cone, r, sol, sly));
	// if (cone->size != 0 && vect_scal(sub_vect(add_vect(cone->position,
	// 	vect_mult_val(cone->direction, -cone->half_size)), cone->hit),
	// 			cone->direction) >= 0.0)
	// 	return (intersection_cone3(cone, r, sol, sly));
	return (sol);
}

t_sol	intersection_ray_limited_cone(t_obj *cone, t_ray r)
{
	t_sol	sol;
	t_vect	sly;
	int		is;

	sol = all_cone(cone, r);
	// cone_norm(cone, r, sol.tmax);
	// if (cone->slice.x || cone->slice.y || cone->slice.z)
	// 	sol = slice_object_cone(cone, r, sol);
	// cone_norm(cone, r, sol.tmax);
	cone_norm(cone, r, sol.tmax);
	sol = limited_object_cone(cone, r, sol);
	if (cone->slice.x || cone->slice.y || cone->slice.z)
		sol.tmin = cone_slicing(sol, cone, r);
	// sly = cone->slice;
	// if (!sly.x && !sly.y && !sly.z)
	// 	is = 0;
	// else
	// 	is = 1;
	// if (is == 1 && vect_scal(sub_vect(cone->pos_slice, cone->hit), sly) <= 0.0)
	// 	return (intersection_cone(cone, r, sol, sly));
	// if (cone->size != 0 && vect_scal(sub_vect(add_vect(cone->position,
	// 	vect_mult_val(cone->direction, cone->half_size)), cone->hit),
	// 			cone->direction) <= 0.0)
	// 	return (intersection_cone2(cone, r, sol, sly));
	// if (cone->size != 0 && vect_scal(sub_vect(add_vect(cone->position,
	// 	vect_mult_val(cone->direction, -cone->half_size)), cone->hit),
	// 			cone->direction) >= 0.0)
	// 	return (intersection_cone3(cone, r, sol, sly));

	return (sol);
}
