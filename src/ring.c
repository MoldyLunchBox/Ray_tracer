/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:48:49 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/02 19:10:16 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol			intersection_ray_ring(t_obj *ring, t_ray r)
{
	double	nomi;
	double	dinomi;
	t_sol	sol;

	nomi = vect_scal(sub_vect(r.origine, ring->position),
			ring->direction);
	dinomi = vect_scal(r.direction, ring->direction);
	if ((dinomi == 0) || (nomi <= 0 && dinomi < 0)
			|| (nomi >= 0 && dinomi > 0))
		return (sol);
	sol.tmin = -nomi / dinomi;
	if (sol.tmin < 0)
		return (sol);
	ring->hit = add_vect(r.origine,
			vect_mult_val(r.direction, sol.tmin));
	if (get_norm_2(sub_vect(ring->hit, ring->position)) > ring->radius)
		return (sol);
	if (get_norm_2(sub_vect(ring->hit, ring->position)) < ring->size)
		return (sol);
	ring->norm = get_normalized(ring->direction);
	return (sol);
}
