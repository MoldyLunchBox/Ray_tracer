/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:54:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/19 17:59:27 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int	ft_clamp(int value, int min, int max)
{
	value > max ? value = max : 0;
	value < min ? value = min : 0;
	return (value);
}

t_2d_i	sphere_uv(t_obj *obj, t_2d_i size)
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


t_uv	uv_mapping_cyl_cone(t_obj *obj, t_2d_i size)
{
	double	v;
	double	u;
	t_uv	uv;
	t_vect	d;

	d = sub_vect(obj->hit, mult_vect(obj->position, obj->direction));
	u = (0.5 + atan2(d.z, d.x) / M_PI * 0.5) * 1;
	v = (d.y / (-10 + 0)) * 1;
	v = v - floor(v);
	uv.u = ft_clamp((int)(u * size.x), 0, size.x - 1);
	uv.v = ft_clamp((int)(v * size.y), 0, size.y - 1);
	return (uv);
}
