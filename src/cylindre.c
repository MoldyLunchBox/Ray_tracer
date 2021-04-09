/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:38:44 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/03 11:58:23 by amya             ###   ########.fr       */
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
