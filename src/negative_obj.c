/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:31:44 by amya              #+#    #+#             */
/*   Updated: 2021/04/26 10:50:51 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_sol	cyl_inter_negative(t_sol t, t_obj *header, t_all data, t_ray hit_light)
{
	if (t.tmin != -1 && ft_strequ(header->name, (char const *)"cylinder"))
	{
		t = look_for_negative(header, data, t, hit_light);
		if (t.tmin == -1)
			t.tmin = t.tmax;
	}
	return (t);
}

void	cylinder_surface_normal(t_obj *obj, double t, t_ray ray)
{
	obj->hit = add_vect(ray.origine, vect_mult_val(ray.direction, t));
	obj->norm = get_normalized(sub_vect(sub_vect(obj->hit, obj->position),
				vect_mult_val(obj->direction, vect_scal(obj->direction,
						sub_vect(obj->hit, obj->position)))));
	obj->norm = vect_mult_val(obj->norm, -1);
}

t_sol	return_new_sol(t_obj *obj, t_sol *t, t_sol t2, t_ray ray, t_obj *sphere)
{
	t->tmin = -1;
	if (t2.tmax <= t->tmax && t2.tmax >= t->tmin)
	{
		obj->hit = add_vect(ray.origine, vect_mult_val(ray.direction, t2.tmin));
		obj->norm = get_normalized(sub_vect(obj->hit, sphere->position));
		t2.tmin = t2.tmax;
		return (t2);
	}
	
	if (t->tmax <= t2.tmax && t->tmax >= t2.tmin)
	{
		t->tmax = -1;
		return (*t);
	}
	cylinder_surface_normal(obj, t->tmax, ray);
	return (*t);
}

t_sol	look_for_negative(t_obj *obj, t_all data, t_sol t, t_ray ray)
{
	t_obj	*looper;
	t_sol	t2;

	looper = data.obj;
	while (looper->next)
	{
		if (looper->is_negative)
		{
			t2 = looper->inter(looper, ray);
			if (t.tmin <= t2.tmax && t.tmin >= t2.tmin)
				return (return_new_sol(obj, &t, t2, ray, looper));
		}
		looper = looper->next;
	}
	return (t);
}

void	init_sol(t_sol *t)
{
	t->tmin = -1;
	t->tmax = -1;
}
