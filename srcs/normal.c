/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 09:11:25 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/02 17:29:32 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	get_norm(t_vec v)
{
	double	ret;

	ret = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	return (ret);
}

t_vec	normal_sphere(double t, t_ray r, t_sphere s)
{
	t_vec	hit;
	t_vec	n;

	hit = vec_add(r.o, vec_product(normalize(r.dir), t));
	n.x = hit.x - s.pos.x;
	n.y = hit.y - s.pos.y;
	n.z = hit.z - s.pos.z;
	return (normalize(n));
}

t_vec	normalize(t_vec vec)
{
	double	mod;

	mod = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
	vec.x /= mod;
	vec.y /= mod;
	vec.z /= mod;
	return (vec);
}
