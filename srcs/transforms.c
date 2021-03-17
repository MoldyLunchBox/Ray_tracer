/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:54:06 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/10 10:16:04 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	ft_rotate_x(t_vec v, double angle)
{
	t_vec res;

	res.x = v.x;
	res.y = v.y * cos(angle) + v.z * sin(angle);
	res.z = -v.y * sin(angle) + v.z * cos(angle);
	return (res);
}

t_vec	ft_rotate_y(t_vec v, double angle)
{
	t_vec	res;

	res.y = v.y;
	res.x = v.x * cos(angle) + v.z * sin(angle);
	res.z = -v.x * sin(angle) + v.z * cos(angle);
	return (res);
}

t_vec	ft_transform_ray(t_obj *o)
{
	o->axis = ft_rotate(o->axis, o->rot);
	o->pos = ft_translate(o->pos, o->trans);
	return (o->axis);
}

t_vec	ft_rotate_z(t_vec v, double angle)
{
	t_vec	res;

	res.z = v.z;
	res.x = v.x * cos(angle) - v.y * sin(angle);
	res.y = v.x * sin(angle) + v.y * cos(angle);
	return (res);
}

t_vec	ft_rotate(t_vec v, t_vec rot)
{
	t_vec	res;

	res = ft_rotate_x(v, rot.x * M_PI / 180);
	res = ft_rotate_y(res, rot.y * M_PI / 180);
	res = ft_rotate_z(res, rot.z * M_PI / 180);
	return (res);
}

