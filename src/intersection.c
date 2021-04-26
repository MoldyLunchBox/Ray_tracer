/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:50:05 by amya              #+#    #+#             */
/*   Updated: 2021/04/22 17:06:58 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void static	closest_hit(double *t1, t_sol t, t_obj *obj, double *val)
{
	if (t.tmin != -1)
	{
		if (*t1 == -1)
		{
			*t1 = t.tmin;
			if (obj->type == 3)
				*val = 1;
		}
		else
		{
			if (*t1 > t.tmin)
			{
				*t1 = t.tmin;
				if (obj->type == 3)
					*val = 1;
			}
		}
	}
}

double	find_obj_scnd(t_all data, t_ray hit_to_light, t_obj *pos, double *val)
{
	t_obj		*header;
	t_sol		t;
	double		t1;

	*val = 0;
	t1 = -1;
	header = data.obj;
	while (header->next)
	{
		if (header->id == pos->id)
		{
			header = header->next;
			continue ;
		}
		if (!header->is_negative)
			t = header->inter(header, hit_to_light);
		else
			init_sol(&t);
		t = cyl_inter_negative(t, header, data, hit_to_light);
		closest_hit(&t1, t, header, val);
		header = header->next;
	}
	return (t1);
}

static t_sol	intersect(t_obj *header, t_ray ray)
{
	t_sol	t;

	if (!header->is_negative)
		t = header->inter(header, ray);
	else
		init_sol(&t);
	return (t);
}

t_obj	*find_closest(t_all data, t_ray ray)
{
	t_find_closest	var;

	var.t1 = -1;
	init_sol(&var.t);
	var.header = data.obj;
	var.pos = var.header;
	while (var.header->next)
	{
		var.t = intersect(var.header, ray);
		var.t = cyl_inter_negative(var.t, var.header, data, ray);
		if (var.t.tmin != -1)
		{
			if (var.t1 == -1)
				var.pos = var.header;
			var.t1 = if_t1_isnull(var.t1, var.t);
			if (var.t1 > var.t.tmin)
				var.pos = var.header;
			var.t1 = if_t1_isbigger(var.t1, var.t);
		}
		var.header = var.header->next;
	}
	var.pos->t = var.t1;
	return (var.pos);
}
