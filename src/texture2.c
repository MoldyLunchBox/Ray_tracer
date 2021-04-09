/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:54:18 by amya              #+#    #+#             */
/*   Updated: 2021/03/29 15:56:22 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_2d_i		plane_uv(t_obj *obj, t_2d_i size)
{
	double	u;
	double	v;
	t_2d_i	tex;
	t_vect	u_axis;
	t_vect	v_axis;

	u_axis = (t_vect){obj->norm.y, obj->norm.z, -obj->norm.x};
	v_axis = vect_cross(u_axis, obj->norm);
	u = vect_scal(obj->hit, u_axis) * 0.05;
	v = vect_scal(obj->hit, v_axis) * 0.05;
	u = u - floor(u);
	v = v - floor(v);
	tex.x = (int)(u * (size.x - 1));
	tex.y = (int)(v * (size.y - 1));
	return (tex);
}

int			ft_clamp(int value, int min, int max)
{
	value > max ? value = max : 0;
	value < min ? value = min : 0;
	return (value);
}

t_2d_i		sphere_uv(t_obj *obj, t_2d_i size)
{
	t_vect	vp;
	double	phi;
	double	u;
	double	v;
	t_2d_i	tex;

	vp = obj->hit;
	vp = get_normalized(sub_vect(vp, obj->position));
	phi = acos(vect_scal((t_vect){0, 1, 0}, vp));
	u = (acos(vect_scal(vp, (t_vect){1, 0, 0}) / sin(phi))) / (2 * M_PI);
	if (vect_scal((t_vect){0, 0, 1}, vp) < 0)
		u = 1 - u;
	v = phi / M_PI;
	tex.x = (int)(size.x * u);
	tex.y = (int)(size.y * v);
	tex.x = ft_clamp((int)(size.x * u) % size.x, 0, size.x - 1);
	tex.y = ft_clamp((int)(size.y * v) % size.y, 0, size.y - 1);
	return (tex);
}

double		comp(double x, double y, double z)
{
	if (x <= y)
		return (y);
	if (x >= z)
		return (z);
	return (x);
}

t_2d_i		uv_mapping_cyl_cone(t_obj *obj, t_2d_i size)
{
	double	v;
	double	u;
	t_2d_i	tex;
	t_vect	d;

	d = sub_vect(obj->hit, mult_vect(obj->position, obj->direction));
	u = (0.5 + atan2(d.z, d.x) / M_PI * 0.5) * 1;
	v = (d.y / (-10 + 0)) * 1;
	v = v - floor(v);
	tex.x = ft_clamp((int)(u * size.x), 0, size.x - 1);
	tex.y = ft_clamp((int)(v * size.y), 0, size.y - 1);
	return (tex);
}
