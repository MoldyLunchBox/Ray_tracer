/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:45:35 by amya              #+#    #+#             */
/*   Updated: 2021/04/19 11:08:45 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	init_li(t_light *li, t_data_light *light, t_obj *obj, t_ray ray)
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
	li->col.x = fmin(255, li->col.x + in1 * (li->diff.x + li->spec.x));
	li->col.y = fmin(255, li->col.y + in1 * (li->diff.y + li->spec.y));
	li->col.z = fmin(255, li->col.z + in1 * (li->diff.z + li->spec.z));
}
