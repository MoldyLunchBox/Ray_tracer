/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 09:24:56 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/11 09:54:24 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec c;

	c.x = v1.y * v2.z - v2.y * v1.z;
	c.y = v1.z * v2.x - v2.z * v1.x;
	c.z = v1.x * v2.y - v2.x * v1.y;
	return (c);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec c;

	c.x = v1.x + v2.x;
	c.y = v1.y + v2.y;
	c.z = v1.z + v2.z;
	return (c);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec c;

	c.x = v1.x - v2.x;
	c.y = v1.y - v2.y;
	c.z = v1.z - v2.z;
	return (c);
}

t_vec	vec_product(t_vec v, double i)
{
	t_vec c;

	c.x = v.x * i;
	c.y = v.y * i;
	c.z = v.z * i;
	return (c);
}

double	dot_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}


// static int	ft_min_ray(float t1, float t2, float *t)
// {
// 	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
// 	{
// 		*t = t1;
// 		return (1);
// 	}
// 	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
// 	{
// 		*t = t2;
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// t_object	*ft_paraboloid_new(void)
// {
// 	t_object	*new;

// 	if ((new = (t_object *)ft_memalloc(sizeof(*new))))
// 	{
// 		new->type = PARABOLOID;
// 		new->name = "PARABOLOID";
// 		new->pos = (t_vec3){0.0, 0.0, 0.0};
// 		new->translate = (t_vec3){0.0, 0.0, 0.0};
// 		new->rotate = (t_vec3){0.0, 0.0, 0.0};
// 		new->scale = (t_vec3){1.0f, 1.0f, 1.0f};
// 		new->e.parab.k = 1.0;
// 		new->e.parab.v = (t_vec3){0.0, 1.0, 0.0};
// 		new->material = ft_default_material();
// 		new->next = NULL;
// 	}
// 	else
// 		ft_print_error("malloc error");
// 	return (new);
// }

// t_vec3		ft_normal_paraboloid(t_paraboloid *pa, t_vec3 p)
// {
// 	float	m;

// 	m = ft_vec3_dot(p, pa->v);
// 	return (ft_vec3_normalized(ft_vec3_sub(p, ft_vec3_kmult(m + pa->k,
// 						pa->v))));
// }

// int			ft_paraboloid_compute(t_object *p, t_intersect *in)
// {
// 	t_ray		r;

// 	r = in->ray;
// 	if (!ft_paraboloid_intersect(&p->e.parab, &r, &in->t))
// 		return (0);
// 	in->current = p;
// 	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
// 	in->n = ft_normal_paraboloid(&p->e.parab, in->p);
// 	if (p->material.bump)
// 		in->n = ft_normal_bump(in);
// 	in->p = ft_translate_vec3(in->p, p->translate, 0);
// 	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
// 	in->p = ft_scale_vec3(in->p, p->scale, 0);
// 	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
// 	in->n = ft_scale_vec3(in->n, p->scale, -1);
// 	in->n = ft_vec3_normalized(in->n);
// 	return (1);
// }

// int			ft_paraboloid_intersect(t_paraboloid *p, t_ray *r, float *t)
// {
// 	t_vec3	x;
// 	t_delta	d;

// 	x = r->start;
// 	d.a = ft_vec3_dot(r->dir, r->dir) - pow(ft_vec3_dot(r->dir, p->v), 2);
// 	d.b = 2.0 * (ft_vec3_dot(r->dir, x)
// 			- ft_vec3_dot(r->dir, p->v) * (ft_vec3_dot(x, p->v)
// 				+ 2.0 * p->k));
// 	d.c = ft_vec3_dot(x, x) - ft_vec3_dot(x, p->v) * (ft_vec3_dot(x, p->v)
// 			+ 4.0 * p->k);
// 	d.delta = d.b * d.b - 4.0 * d.c * d.a;
// 	if (d.delta < 0.0001)
// 		return (0);
// 	d.delta = sqrt(d.delta);
// 	return (ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
// 				(-d.b - d.delta) / (2.0 * d.a), t));
// }
