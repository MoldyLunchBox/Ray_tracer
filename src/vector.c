/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:49:12 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:49:18 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		normalize(t_vect *v)
{
	double	norm;

	norm = sqrt(get_norm_2(*v));
	v->x /= norm;
	v->y /= norm;
	v->z /= norm;
}

t_vect		get_normalized(t_vect v)
{
	t_vect	v1;

	v1 = v;
	normalize(&v1);
	return (v1);
}

t_vect		vect_cross(t_vect a, t_vect b)
{
	t_vect	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.x * b.z) - (a.z * b.x);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

t_vect		rot_vect_xyz(t_vect v, t_vect rot)
{
	init_vect(&rot, rot.x * (PI / 180), rot.y *
			(PI / 180), rot.z * (PI / 180));
	init_vect(&v, v.x, (v.y * cos(rot.x) - v.z *
				sin(rot.x)), (v.y * sin(rot.x) + v.z * cos(rot.x)));
	init_vect(&v, (v.x * cos(rot.y) + v.z * sin(rot.y)),
			v.y, (-v.x * sin(rot.y) + v.z * cos(rot.y)));
	init_vect(&v, (v.x * cos(rot.z) - v.y * sin(rot.z)),
			(v.x * sin(rot.z) + v.y * cos(rot.z)), v.z);
	return (v);
}

t_vect		trans_vect_xyz(t_vect v, t_vect tra)
{
	init_vect(&v, v.x + tra.x, v.y, v.z);
	init_vect(&v, v.x, v.y + tra.y, v.z);
	init_vect(&v, v.x, v.y, v.z + tra.z);
	return (v);
}
