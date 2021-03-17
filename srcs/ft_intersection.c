/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:25:01 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/17 17:34:24 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cone_intersection(t_ray *ray, t_obj *cone)
{
	t_sol	n;
	t_vec	obj_center;
	double	discr;
	double t2 = -1;
	double t3 = 1;
	t_vec 	p1 = (t_vec){0,10,0};
	t_vec p2 = (t_vec){0, -10,0};
	n.k = tan((cone->an_ra * M_PI / 180.0));
	obj_center = vec_sub(ray->o, cone->pos);
	n.a = dot_product(ray->dir, ray->dir) - (1 + pow(n.k, 2)) *
	(dot_product(ray->dir, cone->axis) * dot_product(ray->dir, cone->axis));
	n.b = 2 * (dot_product(ray->dir, obj_center) - (1 + pow(n.k, 2))
	* (dot_product(ray->dir, cone->axis) *
	dot_product(obj_center, cone->axis)));
	n.c = (dot_product(obj_center, obj_center) - (1 + pow(n.k, 2))
	* (dot_product(obj_center, cone->axis)
	* dot_product(obj_center, cone->axis)));
	discr = n.b * n.b - 4 * n.a * n.c;
	if (discr < 0)
		return (0);
	n.t1 = (-n.b - sqrt(discr)) / (2 * n.a);
	n.t2 = (-n.b + sqrt(discr)) / (2 * n.a);
	n.t1 =ft_min_ray(n.t1, n.t2, n.t);
	if (n.t1 > 0)
	{
		t_vec q = vec_add(ray->o, vec_product(ray->dir, n.t1));
		t2 = dot_product(cone->axis, vec_sub(q,p1));
		t3 = dot_product(cone->axis, vec_sub(q,p2));
	}
	if ( t2 < 0  && t3 > 0)
	{
		return (n.t1);
		// return (t3);

	}
	return (0);
}



double	intersect_plane(t_ray *r, t_obj *plane)
{
	double	res;
	double	s1;
	double	denom;
	t_vec	nomin;

	res = dot_product(r->dir, plane->axis);
	if (res == 0)
		return (0);
	nomin = vec_sub(r->o, plane->pos);
	denom = dot_product(nomin, plane->axis);
	s1 = -(denom) / (res);
	if (s1 < 0)
		return (0);
	return (s1);
}

double	intersection_cylinder(t_ray *ray, t_obj *cylinder)
{
	t_sol	n;
	t_vec	x;
	//double	m;
	double t2 = -1;
	double t3 = 1;
	t_vec 	p1 = (t_vec){0,5,0};
	t_vec p2 = (t_vec){0, -5,0};
	double	delta;

	x = vec_sub(ray->o, cylinder->pos);
	n.tmp = dot_product(ray->dir, cylinder->axis);
	n.tmp_2 = dot_product(x, cylinder->axis);
	n.tmp1 = dot_product(x, ray->dir);
	n.a = dot_product(ray->dir, ray->dir)
	- pow(dot_product(ray->dir, cylinder->axis), 2);
	n.b = 2 * (n.tmp1 - n.tmp * n.tmp_2);
	n.c = dot_product(x, x) - pow(n.tmp_2, 2)
	- (cylinder->an_ra * cylinder->an_ra);
	delta = n.b * n.b - (4 * n.a * n.c);
	if (delta < 0)
		return (0);
	n.t1 = (-n.b - sqrt(delta)) / (2 * n.a);
	n.t2 = (-n.b + sqrt(delta)) / (2 * n.a);
	n.t1 =ft_min_ray(n.t1, n.t2, n.t);
	if (n.t1 > 0)
	{
		t_vec q = vec_add(ray->o, vec_product(ray->dir, n.t1));
		t2 = dot_product(cylinder->axis, vec_sub(q,p1));
		t3 = dot_product(cylinder->axis, vec_sub(q,p2));
	}

	if (t2 < 0  && t3 > 0)
	{
		return (n.t1);
		// return (t3);

	}
	return (0);
}


// t_vec	normal_ellipsoid(t_ellipsoid *e, t_vec p)
// {
// 	return(vec_product(p, 1/e->radius));
// }

double	intersection_ellipsoid(t_ray *r, t_obj *e)
{
	t_vec		x;
	t_sol		n;
	t_delta		d;
	double		a1;
	double		a2;


	e->k = 6;
	x = vec_sub(r->o, e->pos);
	e->radius2 = e->radius * e->radius;
	a1 = 2.0 * e->k * dot_product(r->dir, e->axis);
	a2 = e->radius2 + 2.0 * e->k * dot_product(x, e->axis) - e->k;
	d.a = 4.0 * e->radius2 * dot_product(r->dir, r->dir) - (a1 * a1);
	d.b = 2.0 * (4.0 * e->radius2 * dot_product(r->dir, x) - (a1 * a2));
	d.c = 4.0 * e->radius2 * dot_product(x, x) - (a2 * a2);
	d.delta = d.b * d.b - 4.0 * d.c * d.a;
	if (d.delta < 0.0001)
		return (0);
	d.delta = sqrt(d.delta);
	double t = ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
				(-d.b - d.delta) / (2.0 * d.a), n.t);
		
	// t_vec C = vec_sub(e->pos, vec_product(e->axis,e->k));
	t_vec cmid = vec_add(e->pos, vec_product(e->axis, e->k / 2));
	e->hit = vec_add(r->o, vec_product(r->dir, t));
	t_vec rr = vec_sub(e->hit, cmid);
	double nbr = (1 - ((d.b * d.b)/(d.a * d.a))) * dot_product(e->axis, rr);
	t_vec product = vec_product(e->axis, nbr);
	e->n =normalize(vec_sub(rr, product));
	if (e->id == 6)
		ft_putendl("");
	return (t);

}

double	intersection_paraploid(t_ray *r, t_obj *p)
{
	t_vec x;
	t_delta d;
	t_sol n;
	x = vec_sub(r->o, p->pos);
	d.a = dot_product(r->dir, r->dir) - pow(dot_product(r->dir, p->axis), 2);
	d.b = 2.0 * (dot_product(r->dir, x)
			- dot_product(r->dir, p->axis) * (dot_product(x, p->axis)
				+ 2.0 * p->radius));
	d.c = dot_product(x, x) - dot_product(x, p->axis) * (dot_product(x, p->axis)
			+ 4.0 *  p->radius);
	d.delta = d.b * d.b - 4.0 * d.c * d.a;
	if (d.delta < 0.0001)
		return (0);
	d.delta = sqrt(d.delta); 
	double t = ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
				(-d.b - d.delta) / (2.0 * d.a), n.t);
	p->hit = vec_add(r->o, vec_product(r->dir, t));
	double m = dot_product(vec_sub(p->hit, p->pos),p->axis);
	t_vec pc = vec_sub(p->hit,p->pos);
	t_vec mk = vec_product(p->axis, m +p->radius);
	 p->n = normalize (vec_sub(pc, mk));

	

			return(t);
}


double	intersection_spher(t_ray *r, t_obj *s)
{
	t_sol n;
	t_vec dist;

	dist = vec_sub(r->o, s->pos);
	n.a = get_norm(r->dir);
	n.b = 2 * dot_product(r->dir, dist);
	n.c = get_norm(dist) - (s->an_ra * s->an_ra);
	n.delta = n.b * n.b - 4 * n.a * n.c;
	if (n.delta < 0)
		return (-1);
	n.t1 = (-1 * n.b - sqrt(n.delta)) / (2 * n.a);
	n.t2 = (-1 * n.b + sqrt(n.delta)) / (2 * n.a);
	return (ft_min_ray(n.t1, n.t2, n.t));
}
