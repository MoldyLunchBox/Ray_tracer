/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:06:01 by amya              #+#    #+#             */
/*   Updated: 2021/04/26 11:23:51 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_vect	safe_color(t_vect p)
{
	t_vect	col;

	col.x = fmin(255, p.x);
	col.y = fmin(255, p.y);
	col.z = fmin(255, p.z);
	return (col);
}

int	paralell_light(t_data_light *light, t_obj *objet, t_light *li)
{
	t_vect	spot_drection;
	t_vect	light_dir;
	double	teta;
	double	beta;

	if (light->type == !2 && light->type == !1)
		return (1);
	if (light->type == 1)
		beta = 0;
	else
		beta = 0.94;
	spot_drection = sub_vect(light->look_at, light->position);
	spot_drection = get_normalized(spot_drection);
	spot_drection = vect_mult_val(spot_drection, -1);
	light_dir = sub_vect(light->position, objet->hit);
	light_dir = get_normalized(light_dir);
	teta = vect_scal(light_dir, spot_drection);
	li->ambi = vect_mult_val(objet->color, 0.1);
	if (teta >= beta)
	{
		return (1);
	}
	return (0);
}

t_vect	light_obj(t_obj *obj, t_all data, t_ray ray)
{
	t_light			li;
	t_data_light	*ligth;

	if (ft_strcmp(obj->texture, ".") != 0)
		texturing(obj);
	ligth = data.light;
	init_vect(&li.col, 0., 0., 0.);
	while (ligth->next)
	{
		if (paralell_light(ligth, obj, &li))
			init_li(&li, ligth, obj, ray, data);
		ligth = ligth->next;
	}
	li.col = safe_color(add_vect(li.ambi, li.col));
	return (li.col);
}

t_2d_d	shadow(t_obj *pos, t_data_light *light, double t1)
{
	t_vect			hit_sec;
	t_2d_d			light_dest;

	hit_sec = add_vect(pos->hit, vect_mult_val(light->to_light.direction, t1));
	light_dest.x = get_norm_2(sub_vect(hit_sec, pos->hit
				)) * get_norm_2(sub_vect(hit_sec, pos->hit));
	light_dest.y = get_norm_2(sub_vect(light->position,
				pos->hit)) * get_norm_2(sub_vect(light->position, pos->hit));
	return (light_dest);
}

t_vect	on_shadow(t_obj *pos, t_all data, t_vect col)
{
	t_2d_d			dis_shad_inter_lum;
	double			t1;
	t_data_light	*light;
	double			val;

	light = data.light;
	while (light->next)
	{
		light->norm_light = get_normalized(sub_vect(light->position, pos->hit));
		init_ray(&light->to_light, add_vect(pos->hit,
				vect_mult_val(light->norm_light, 1)), light->norm_light);
		t1 = find_obj_scnd(data, light->to_light, pos, &val);
		if (t1 != -1)
		{
			dis_shad_inter_lum = shadow(pos, light, t1);
			if (val == 1)
				val = 0.7;
			else
				val = 0.5;
			if ((dis_shad_inter_lum.y > dis_shad_inter_lum.x))
				init_vect(&col, col.x * val, col.y * val, col.z * val);
		}
		light = light->next;
	}
	return (col);
}
