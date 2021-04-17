/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:36 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/17 13:22:32 by amya             ###   ########.fr       */
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

int     paralell_light(t_data_light *light, t_obj *objet, t_ray ray, t_light *li)
{
    t_vect  spot_drection;
    t_vect  light_dir;
    double  teta;
    double  beta = 0.95;
    spot_drection = sub_vect(light->direction,light->position);
    spot_drection = get_normalized(spot_drection);
    spot_drection = vect_mult_val(spot_drection, -1);
    light_dir = sub_vect(light->position,objet->hit);
    light_dir = get_normalized(light_dir);
    teta = vect_scal(light_dir,spot_drection);
    li->ambi = vect_mult_val(objet->color, 0.1);
    if(teta > beta)
    {
        return(1);
    }
    return(0);
}

t_vect	light_obj(t_obj *obj, t_all data, t_ray ray, double t)
{
	t_light			li;
	t_data_light	*ligth;

	if (ft_strcmp(obj->texture, ".") != 0)
		texturing(obj);
	ligth = data.light;
	init_vect(&li.col, 0., 0., 0.);
	while (ligth->next)
	{
		if (paralell_light(ligth,obj ,ray ,&li))
		init_li(&li, ligth, obj, ray);
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

t_vect	on_shadow(t_obj *pos, t_all data, t_ray ray, t_vect col)
{
	double			dis_shad_lum;
	double			dis_shad_inter;
	double			t1;
	t_data_light	*light;

	light = data.light;
	while (light->next)
	{
		light->norm_light = get_normalized(sub_vect(light->position, pos->hit));
		init_ray(&light->to_light, add_vect(pos->hit,
				vect_mult_val(light->norm_light, 1)), light->norm_light);
		t1 = find_obj_scnd(data, ray, light->to_light, pos);
		if (t1 != -1)
		{
			dis_shad_inter = shadow(pos, light, t1).x;
			dis_shad_lum = shadow(pos, light, t1).y;
			if ((dis_shad_lum > dis_shad_inter))
				init_vect(&col, col.x * 0.7, col.y * 0.7, col.z * 0.7);
		}
		light = light->next;
	}
	return (col);
}
