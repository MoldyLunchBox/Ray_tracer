/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:45:35 by amya              #+#    #+#             */
/*   Updated: 2021/04/26 11:59:00 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	init_li(t_light *li, t_data_light *light, t_obj *obj, t_ray ray, t_all data)
{
	double	in1;

	li->ambi = vect_mult_val(obj->color, light->ambient);
	li->rm = get_normalized(sub_vect(light->position, obj->hit));
	li->rm = sub_vect(vect_mult_val
			(obj->norm, 2 *vect_scal(li->rm, obj->norm)), li->rm);
	li->diff = vect_mult_val(obj->color, fmax
			(0.0, 0.5 *vect_scal(get_normalized
					(sub_vect(light->position, obj->hit)), obj->norm)));
	li->spec = vect_mult_val(light->color, 0.5 * pow
			(fmax(0.0, vect_scal(li->rm, get_normalized
						(sub_vect(ray.origine, obj->hit)))), 60));
	in1 = light->intensity / get_norm_2(sub_vect(light->position, obj->hit));
	if (data.shadow == 1)
	li->spec = (t_vect){0,0,0};
	li->col.x = fmin(255, li->col.x + in1 * (li->diff.x + li->spec.x));
	li->col.y = fmin(255, li->col.y + in1 * (li->diff.y + li->spec.y));
	li->col.z = fmin(255, li->col.z + in1 * (li->diff.z + li->spec.z));
}


int	is_under_shadow(t_obj *obj, t_all data)
{
	t_2d_d			dis_shad_inter_lum;
	double			t1;
	t_data_light	*light;
	double			val;

	light = data.light;
	while (light->next)
	{
		light->norm_light = get_normalized(sub_vect(light->position, obj->hit));
		init_ray(&light->to_light, add_vect(obj->hit,
				vect_mult_val(light->norm_light, 1)), light->norm_light);
		t1 = find_obj_scnd(data, light->to_light, obj, &val);
		if (t1 != -1)
		{
			dis_shad_inter_lum = shadow(obj, light, t1);
			if (val == 1)
				val = 0.7;
			else
				val = 0.5;
			if ((dis_shad_inter_lum.y > dis_shad_inter_lum.x))
			return (1);
		}
		light = light->next;
	}
	return (0);
}

t_vect	light_n_shadow(t_obj *obj, t_all data, t_ray ray, t_vect col)
{
	data.shadow = is_under_shadow(obj, data);
	col = add_vect(light_obj(obj, data, ray), col);
	col = on_shadow(obj, data, col);
	return (col);
}
