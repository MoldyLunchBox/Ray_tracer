/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:36:32 by amya              #+#    #+#             */
/*   Updated: 2021/03/29 15:36:48 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void			cone_norm(t_obj *cone, t_ray r, double t)
{
	double	k;
	double	m;

	k = tan((cone->radius * PI / 180) / 2);
	m = vect_scal(r.direction, vect_mult_val(cone->direction, t))
		+ vect_scal(sub_vect(r.origine, cone->position), cone->direction);
	cone->norm = get_normalized(sub_vect(sub_vect(cone->hit, cone->position)
				, vect_mult_val(cone->direction, (1 + k + k) * m)));
}

t_sol			find_solution(double delta, t_vect abc)
{
	t_sol	sol;
	double	temp;

	if (delta < 0)
		return ((t_sol){-1., -1.});
	sol.tmin = (-1 * abc.y - sqrt(delta)) / (2 * abc.x);
	sol.tmax = (-1 * abc.y + sqrt(delta)) / (2 * abc.x);
	if (sol.tmin < 0 && sol.tmax < 0)
		return ((t_sol){-1., -1.});
	else if (sol.tmin > 0 && sol.tmax < 0)
		sol.tmax = -1;
	else if ((sol.tmax > 0 && sol.tmin < 0))
	{
		sol.tmin = sol.tmax;
		sol.tmax = -1;
	}
	else
	{
		temp = fmin(sol.tmin, sol.tmax);
		sol.tmax = fmax(sol.tmin, sol.tmax);
		sol.tmin = temp;
	}
	return (sol);
}
