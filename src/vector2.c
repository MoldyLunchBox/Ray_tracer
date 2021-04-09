/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:49:23 by yoelguer          #+#    #+#             */
/*   Updated: 2021/03/28 19:04:45 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		init_2d_vect(t_2d_d *v)
{
	v->x = 0;
	v->y = 0;
}

void		init_vect(t_vect *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vect		new_vect(double x, double y, double z)
{
	t_vect v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vect		add_vect(t_vect v1, t_vect v2)
{
	t_vect v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vect		sub_vect(t_vect v1, t_vect v2)
{
	t_vect v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}
