/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:38:44 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/17 17:12:24 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

double			intersection_slice(t_obj *cyl, t_ray r, t_sol sol, t_vect sly)
{
	cyl->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmax));
	if (sol.tmax > 0 &&
			vect_scal(sub_vect(cyl->pos_slice, cyl->hit), sly) > 0.0)
	{
		cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit,
		cyl->position), vect_mult_val(cyl->direction,
		vect_scal(cyl->direction, sub_vect(cyl->hit, cyl->position)))));
		return (sol.tmax);
	}
	return (-1);
}

double			intersection_slice2(t_obj *cyl, t_ray r, t_sol sol, t_vect sly)
{
	cyl->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmax));
	if (sol.tmax > 0 && vect_scal(sub_vect(add_vect(cyl->position,
		vect_mult_val(cyl->direction, cyl->half_size)), cyl->hit),
				cyl->direction) > 0.0)
	{
		cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit,
						cyl->position),
					vect_mult_val(cyl->direction, vect_scal(cyl->direction,
							sub_vect(cyl->hit, cyl->position)))));
		return (sol.tmax);
	}
	return (-1);
}

double			intersection_slice3(t_obj *cyl, t_ray r, t_sol sol, t_vect sly)
{
	cyl->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmax));
	if (sol.tmax > 0 && vect_scal(sub_vect(add_vect(cyl->position,
		vect_mult_val(cyl->direction, -cyl->half_size)), cyl->hit),
				cyl->direction) < 0.0)
	{
		cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit,
						cyl->position),
					vect_mult_val(cyl->direction, vect_scal(cyl->direction,
							sub_vect(cyl->hit, cyl->position)))));
		return (sol.tmax);
	}
	return (-1);
}

t_sol			all(t_obj *cyl, t_ray r)
{
	t_vect	f;
	t_vect	g;
	t_vect	abc;
	double	delta;
	t_sol	sol;

	g = sub_vect(r.origine, cyl->position);
	f = sub_vect(r.direction, vect_mult_val(cyl->direction,
				vect_scal(r.direction, cyl->direction)));
	g = sub_vect(g, vect_mult_val(cyl->direction,
				vect_scal(g, cyl->direction)));
	abc.x = get_norm_2(f);
	abc.y = 2 * vect_scal(f, g);
	abc.z = get_norm_2(g) - (cyl->radius * cyl->radius);
	delta = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(delta, abc);
	cyl->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmin));
	return (sol);
}

double			cylinder_slicing(t_sol sol, t_obj *cyl, t_ray r)
{
	t_vect	hit_to_pos_slice;

	cyl->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmin));
	hit_to_pos_slice = sub_vect(cyl->hit, cyl->pos_slice);
	if (vect_scal(hit_to_pos_slice, cyl->slice) < 0)
		return (sol.tmin);
	cyl->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmax));
	cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit, cyl->position),
				vect_mult_val(cyl->direction, vect_scal(cyl->direction,
				sub_vect(cyl->hit, cyl->position)))));
	hit_to_pos_slice = sub_vect(cyl->hit, cyl->pos_slice);
	if (vect_scal(hit_to_pos_slice, cyl->slice) < 0)
		return (sol.tmax);
	return (-1);
}
t_sol           limited_object(t_obj *cyl, t_ray r,t_sol sol)
{
    t_vect top;
    t_vect dir;
    t_vect hit_to_slice_point;
    t_vect bottom;
    double  result_top;
    double  result_bottom;
    dir = vect_mult_val(cyl->direction, cyl->size);
    bottom = add_vect(cyl->position,vect_mult_val(cyl->direction, -cyl->size));
    top= add_vect(cyl->position,dir);
    result_top = vect_scal(sub_vect(top, cyl->hit), cyl->direction);
    result_bottom = vect_scal(sub_vect(bottom, cyl->hit),vect_mult_val(cyl->direction,-1));
    if (result_top < 0 || result_bottom<0)
    {
        sol.tmin = -1;
        sol.tmax = -1;
    }
    if (result_top < 0)
    {
    t_obj plane;
    plane.position = top;
    plane.direction = cyl->direction;
    t_sol  plan;
    plan = intersection_ray_plan(&plane, r);
    if (plan.tmin != -1)
        {
            t_vect len;
            len = sub_vect(plane.hit, plane.position);
            double dot = sqrt(len.x*len.x + len.y*len.y + len.z * len.z);
            if (dot <= cyl->radius)
            {
                sol.tmin = plan.tmin;
                cyl->t = sol.tmin;
                cyl->hit = plane.hit;
                cyl->norm =   get_normalized(plane.direction);
            }
        }
    }
    if (result_bottom <0)
    {
    t_obj plane;
    plane.position = bottom;
    plane.direction = cyl->direction;
    t_sol  plan;
    plan = intersection_ray_plan(&plane, r);
    if (plan.tmin != -1)
        {
            t_vect len;
            len = sub_vect(plane.hit, plane.position);
            double dot = sqrt(len.x*len.x + len.y*len.y + len.z * len.z);
            if (dot <= cyl->radius)
            {
                sol.tmin = plan.tmin;
                cyl->t = sol.tmin;
                cyl->hit = plane.hit;
                plane.direction = vect_mult_val(plane.direction,-1);
                cyl->norm =   get_normalized(plane.direction);
            }
        }
    }
    return(sol);
}
t_sol			intersection_ray_cylindre(t_obj *cyl, t_ray r)
{
	t_sol	sol;
	t_vect	sly;
	int		is;

	sol = all(cyl, r);
	cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit, cyl->position),
				vect_mult_val(cyl->direction, vect_scal(cyl->direction,
				sub_vect(cyl->hit, cyl->position)))));
	if (cyl->slice.x || cyl->slice.y || cyl->slice.z)
		sol.tmin = cylinder_slicing(sol, cyl, r);
	
	// if (is == 1 && vect_scal(sub_vect(cyl->pos_slice, cyl->hit), sly) <= 0.0)
	// 	return (intersection_slice(cyl, r, sol, sly));
	// if (cyl->size != 0 && vect_scal(sub_vect(add_vect(cyl->position,
	// 	vect_mult_val(cyl->direction, cyl->half_size)), cyl->hit),
	// 			cyl->direction) <= 0.0)
	// 	return (intersection_slice2(cyl, r, sol, sly));
	// if (cyl->size != 0 && vect_scal(sub_vect(add_vect(cyl->position,
	// 	vect_mult_val(cyl->direction, -cyl->half_size)), cyl->hit),
	// 			cyl->direction) >= 0.0)
	// 	return (intersection_slice3(cyl, r, sol, sly));
	// cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit, cyl->position),
	// 			vect_mult_val(cyl->direction, vect_scal(cyl->direction,
	// 					sub_vect(cyl->hit, cyl->position)))));
	return (sol);

}

t_sol			intersection_ray_limited_cylindre(t_obj *cyl, t_ray r)
{
	t_sol	sol;
	t_vect	sly;
	int		is;

	sol = all(cyl, r);
	cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit, cyl->position),
				vect_mult_val(cyl->direction, vect_scal(cyl->direction,
				sub_vect(cyl->hit, cyl->position)))));
	sol = limited_object(cyl, r, sol);

	// if (cyl->slice.x || cyl->slice.y || cyl->slice.z)
	// sol.tmin = cylinder_slicing(sol, cyl, r);
	// sly = cyl->slice;
	// if (!sly.x && !sly.y && !sly.z)
	// 	is = 0;
	// else
	// 	is = 1;
	// if (is == 1 && vect_scal(sub_vect(cyl->pos_slice, cyl->hit), sly) <= 0.0)
	// 	return (intersection_slice(cyl, r, sol, sly));
	// if (cyl->size != 0 && vect_scal(sub_vect(add_vect(cyl->position,
	// 	vect_mult_val(cyl->direction, cyl->half_size)), cyl->hit),
	// 			cyl->direction) <= 0.0)
	// 	return (intersection_slice2(cyl, r, sol, sly));
	// if (cyl->size != 0 && vect_scal(sub_vect(add_vect(cyl->position,
	// 	vect_mult_val(cyl->direction, -cyl->half_size)), cyl->hit),
	// 			cyl->direction) >= 0.0)
	// 	return (intersection_slice3(cyl, r, sol, sly));
	// cyl->norm = get_normalized(sub_vect(sub_vect(cyl->hit, cyl->position),
	// 			vect_mult_val(cyl->direction, vect_scal(cyl->direction,
	// 					sub_vect(cyl->hit, cyl->position)))));
	return (sol);

}
