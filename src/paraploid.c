/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraploid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:45:59 by amya              #+#    #+#             */
/*   Updated: 2021/04/02 19:03:36 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol			intersection_ellipsoid(t_obj *eli, t_ray r)
{
	t_vect		x;
	t_vect		abc;
	double		delta;
	t_vect		a1;
	t_sol		sol;

	x = sub_vect(r.origine, eli->position);
	eli->radius2 = eli->radius * eli->radius;
	a1.x = 2.0 * eli->size * vect_scal(r.direction, eli->direction);
	a1.y = eli->radius2 + 2.0 * eli->size * vect_scal(x, eli->direction)
		- eli->size;
	abc.x = 4.0 * eli->radius2 * vect_scal(r.direction, r.direction)
		- (a1.x * a1.x);
	abc.y = 2.0 * (4.0 * eli->radius2 * vect_scal(r.direction, x)
		- (a1.x * a1.y));
	abc.z = 4.0 * eli->radius2 * vect_scal(x, x) - (a1.y * a1.y);
	delta = abc.y * abc.y - 4.0 * abc.z * abc.x;
	sol = find_solution(delta, abc);
	eli->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmin));
	eli->norm = get_normalized(vect_mult_val(eli->hit, 1 / eli->radius));
	return (sol);
}

t_vect			norm_para(t_obj *para)
{
	t_vect		mk;
	t_vect		norm;
	double		m;
	t_vect		pc;

	m = vect_scal(sub_vect(para->hit, para->position), para->direction);
	pc = sub_vect(para->hit, para->position);
	mk = vect_mult_val(para->direction, m + para->radius);
	norm = get_normalized(sub_vect(pc, mk));
	return (norm);
}

t_sol			intersection_paraploid(t_obj *para, t_ray r)
{
	t_vect		abc;
	double		delta;
	t_sol		sol;
	t_vect		x;

	x = sub_vect(r.origine, para->position);
	abc.x = vect_scal(r.direction, r.direction) - pow(vect_scal(r.direction,
	para->direction), 2);
	abc.y = 2.0 * (vect_scal(r.direction, x)
			- vect_scal(r.direction, para->direction) *
			(vect_scal(x, para->direction)
				+ 2.0 * para->radius));
	abc.z = vect_scal(x, x) - vect_scal(x, para->direction) *
		(vect_scal(x, para->direction)
		+ 4.0 * para->radius);
	delta = abc.y * abc.y - 4.0 * abc.z * abc.x;
	sol = find_solution(delta, abc);
	para->hit = add_vect(r.origine, vect_mult_val(r.direction, sol.tmin));
	para->norm = norm_para(para);
	return (sol);
}
