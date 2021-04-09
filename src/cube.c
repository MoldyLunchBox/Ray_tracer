/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:44:37 by amya              #+#    #+#             */
/*   Updated: 2021/04/02 19:13:54 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_vect		norm_cube(t_obj *box, t_vect hit_point)
{
	float	epsi;
	t_vect	norm_cub;

	epsi = 0.01;
	if (fabs(hit_point.x - box->b.x) < epsi)
		norm_cub = (t_vect){-1, 0, 0};
	else if (fabs(hit_point.x - box->a.x) < epsi)
		norm_cub = (t_vect){1, 0, 0};
	else if (fabs(hit_point.y - box->b.y) < epsi)
		norm_cub = (t_vect){0, -1, 0};
	else if (fabs(hit_point.y - box->a.y) < epsi)
		norm_cub = (t_vect){0, 1, 0};
	else if (fabs(hit_point.z - box->b.z) < epsi)
		norm_cub = (t_vect){0, 0, -1};
	else if (fabs(hit_point.z - box->a.z) < epsi)
		norm_cub = (t_vect){0, 0, 1};
	return (norm_cub);
}

static void	init_box(t_obj *box, t_sol sol)
{
	init_vect(&box->a, box->position.x + box->size / 2,
	box->position.y + box->size / 2, box->position.z + box->size / 2);
	init_vect(&box->b, box->position.x - box->size / 2,
	box->position.y - box->size / 2, box->position.z - box->size / 2);
	sol.tmin = -1;
}

t_sol		intersection_cube(t_obj *box, t_ray r)
{
	t_bb b;
	t_sol	sol;

	init_box(box, sol);
	b.min = (t_vect){box->a.x, box->a.y, box->a.z};
	b.max = (t_vect){box->b.x, box->b.y, box->b.z};
	b.t1x = (b.min.x - r.origine.x) / r.direction.x;
	b.t2x = (b.max.x - r.origine.x) / r.direction.x;
	b.txmin = fmin(b.t1x, b.t2x);
	b.txmax = fmax(b.t1x, b.t2x);
	b.t1y = (b.min.y - r.origine.y) / r.direction.y;
	b.t2y = (b.max.y - r.origine.y) / r.direction.y;
	b.tymin = fmin(b.t1y, b.t2y);
	b.tymax = fmax(b.t1y, b.t2y);
	b.t1z = (b.min.z - r.origine.z) / r.direction.z;
	b.t2z = (b.max.z - r.origine.z) / r.direction.z;
	b.tzmin = fmin(b.t1z, b.t2z);
	b.tzmax = fmax(b.t1z, b.t2z);
	b.tmin = fmin(fmin(b.txmax, b.tymax), b.tzmax);
	b.tmax = fmax(fmax(b.txmin, b.tymin), b.tzmin);
	if (b.tmin - b.tmax <= 0)
		return (sol);
	box->hit = add_vect(r.origine, vect_mult_val(r.direction, b.tmin));
	box->norm = norm_cube(box, box->hit);
	sol.tmin = b.tmin;
	return (sol);
}
