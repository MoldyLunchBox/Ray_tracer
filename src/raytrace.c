/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:48:25 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/18 17:22:18 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	cylinder_surface_normal(t_obj *obj, double t, t_ray ray)
{
	obj->hit = add_vect(ray.origine, vect_mult_val(ray.direction, t));
	obj->norm = get_normalized(sub_vect(sub_vect(obj->hit, obj->position),
				vect_mult_val(obj->direction, vect_scal(obj->direction,
						sub_vect(obj->hit, obj->position)))));
	obj->norm = vect_mult_val(obj->norm, -1);
}

static t_sol	return_new_sol(t_obj *obj, t_sol *t, t_sol t2, t_ray ray)
{
	t->tmin = -1;
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
				return (return_new_sol(obj, &t, t2, ray));
		}
		looper = looper->next;
	}
	return (t);
}

void static	init_sol(t_sol *t)
{
	t->tmin = -1;
	t->tmax = -1;
}

static t_sol cyl_inter_negative(t_sol t, t_obj *header, t_all data, t_ray hit_to_light)
{
	if (t.tmin != -1 && ft_strequ(header->name, (char const *)"cylinder"))
	{
		t = look_for_negative(header, data, t, hit_to_light);
		if (t.tmin == -1)
			t.tmin = t.tmax;
	}
	return (t);
}

void static	closest_hit(double *t1, t_sol t)
{
	if (t.tmin != -1)
	{
		if (*t1 == -1)
			*t1 = t.tmin;
		else
		{
			if (*t1 > t.tmin)
				*t1 = t.tmin;
		}
	}
}

double	find_obj_scnd(t_all data, t_ray ray, t_ray hit_to_light, t_obj *pos)
{
	t_obj		*header;
	t_sol		t;
	double		t1;

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
		closest_hit(&t1, t);
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

static double	if_t1_isnull(double t1, t_sol t)
{
	if (t1 == -1)
		t1 = t.tmin;
	return (t1);
}
static double	if_t1_isbigger(double t1, t_sol t)
{
	if (t1 > t.tmin)
		t1 = t.tmin;
	return (t1);
}
t_obj	*find_closest(t_all data, t_ray ray)
{
	t_find_closest var;

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

static void	x_bigger_thany(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->y;
	ret->y = ret->x;
	ret->x = *hold;
	*hold = order->y;
	order->y = order->x;
	order->x = *hold;
}
static void	x_bigger_thanz(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->z;
	ret->z = ret->x;
	ret->x = *hold;
	*hold = order->y;
	order->y = order->x;
	order->x = *hold;
}
static void	y_bigger_thanz(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->z;
	ret->z = ret->y;
	ret->y = *hold;
	*hold = order->z;
	order->z = order->y;
	order->y = *hold;
}

static void	x_bigger_thanz2(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->z;
	ret->z = ret->x;
	ret->x = *hold;
	*hold = order->z;
	order->z = order->x;
	order->x = *hold;
}

t_vect			sorting(t_vect in)
{
	t_vect	ret;
	int		hold;
	t_vect	order;

	order = (t_vect){1, 2, 3};
	ret = (t_vect){fabs(in.x), fabs(in.y), fabs(in.z)};
	if (ret.x > ret.y)
		x_bigger_thany(&ret, &hold, &order);
	if (ret.x > ret.z)
		x_bigger_thanz(&ret, &hold, &order);
	if (ret.y > ret.z)
		y_bigger_thanz(&ret, &hold, &order);
	if (ret.x > ret.z)
		x_bigger_thanz2(&ret, &hold, &order);
	return (order);
}

t_vect			distrupt_a_sphere(t_obj *obj, t_vect col)
{
	t_vect	center_to_hit;
	double	hit_to_axis;
	double	center_to_hit_len;

	center_to_hit = sub_vect(obj->hit, (t_vect){0, 0, 1000});
	center_to_hit_len = sqrt(center_to_hit.x * center_to_hit.x
			+ center_to_hit.y * center_to_hit.y
			+ center_to_hit.z * center_to_hit.z);
	if ((int)center_to_hit_len % 2)
		col = (t_vect){255, 0, 0};
	else
		col = (t_vect){255, 255, 255};
	return (col);
}

t_vect	distrupt_a_sphere_color(t_obj *obj, t_vect col)
{
	col = (t_vect){255, 255, 255};
	col.x *= 1 - fabs(2 * (obj->hit.x - floor(obj->hit.x) - 1));
	col.x = fabs(col.x);
	col.y *= 1 - fabs(2 * (obj->hit.y - floor(obj->hit.y) - 1));
	col.y = fabs(col.y);
	col.z *= 1 - fabs(2 * (obj->hit.z - floor(obj->hit.z) - 1));
	col.z = fabs(col.z);
	return (col);
}

static t_vect	sol(t_vect template, double res, double res2, double res3)
{
	u_vect	sort;
	t_vect	applied;
	t_vect	usable_res;
	int		check;

	check = 0;
	applied = (t_vect){0, 0, 0};
	sort.order = applied;
	sort.tab[(int)template.x - 1] = 1;
	sort.tab[(int)template.y - 1] = 1;
	applied = sort.order;
	if (applied.x == 1)
		usable_res.x = res;
	if (applied.x == 1)
		check = 1;
	if (applied.y == 1 && check == 0)
		usable_res.x = res2;
	else
		usable_res.y = res2;
	if (applied.z == 1)
		usable_res.y = res3;
	return (usable_res);
}

static t_vect	possible_results(t_obj *obj)
{
	t_vect	res;

	if (obj->hit.x < 0)
		res.x = ((int)obj->hit.x - 1) % 2;
	else
		res.x = ((int)obj->hit.x) % 2;
	if (obj->hit.y < 0)
		res.y = ((int)obj->hit.y - 1) % 2;
	else
		res.y = ((int)obj->hit.y) % 2;
	if (obj->hit.z < 0)
		res.z = ((int)obj->hit.z - 1) % 2;
	else
		res.z = ((int)obj->hit.z) % 2;
	return (res);
}

t_vect			disruption(t_obj *obj, t_vect col)
{
	t_vect	res;
	t_vect	vec;
	t_vect	usable_res;

	if (obj->disruption == 1)
	{
		vec = sorting(obj->norm);
		res = possible_results(obj);
		usable_res = sol(vec, res.x, res.y, res.z);
		if ((usable_res.x && usable_res.y) || (!usable_res.x && !usable_res.y))
			col = (t_vect){0, 0, 0};
		else
			col = (t_vect){255, 255, 255};
	}
	if (obj->disruption == 2)
		col = distrupt_a_sphere(obj, col);
	if (obj->disruption == 3)
		col = distrupt_a_sphere_color(obj, col);
	return (col);
}

t_vect	reflection(t_all data, t_obj *obj, int nbrbonds, t_ray ray)
{
	t_ray	reflected_ray;
	t_vect	color;
	double	n_dot_d;

	n_dot_d = vect_scal(ray.direction, obj->norm) * 2;
	reflected_ray.direction = vect_mult_val(obj->norm, n_dot_d);
	reflected_ray.direction = sub_vect(ray.direction, reflected_ray.direction);
	reflected_ray.origine = add_vect(obj->hit, vect_mult_val(obj->norm, 0.01));
	color = rend_pix(data, reflected_ray, --nbrbonds);
	return (color);
}

int	under_shadow(t_vect col)
{
	if (!col.x && !col.y && !col.z)
		return (0);
	return (1);
}

static t_ray	calc_refracted(t_obj *obj, t_ray ray, t_vect ref_norm)
{
	double		n1;
	double		n2;
	t_ray		refracted_ray;
	double		r;

	n2 = 1.3;
	n1 = 1;
	if (vect_scal(ray.direction, obj->norm) > 0)
	{
		n1 = 1.3;
		n2 = 1;
	}
	r = 1 - pow(n1 / n2, 2) * (1 - pow(vect_scal(ref_norm, ray.direction), 2));
	refracted_ray.origine = sub_vect(obj->hit, vect_mult_val(ref_norm, 0.001));
	refracted_ray.direction = sub_vect(vect_mult_val(sub_vect(ray.direction,
					vect_mult_val(ref_norm, vect_scal(ray.direction, ref_norm))
					), n1 / n2), vect_mult_val(ref_norm, sqrt(r)));
	return (refracted_ray);
}

t_vect	refraction(t_all data, t_obj *obj, int limit, t_ray ray)
{
	t_refraction	v;
	double			r;

	v.n1 = 1;
	v.n2 = 1.3;
	v.ref_norm = (t_vect){obj->norm.x, obj->norm.y, obj->norm.z};
	if (vect_scal(ray.direction, obj->norm) > 0)
	{
		v.n1 = 1.3;
		v.n2 = 1;
		v.ref_norm = vect_mult_val(obj->norm, -1);
	}
	r = 1 - pow(v.n1 / v.n2, 2) * (1 - pow(
				vect_scal(v.ref_norm, ray.direction), 2));
	if (r > 0)
	{
		v.refracted_ray = calc_refracted(obj, ray, v.ref_norm);
		v.col = rend_pix(data, v.refracted_ray, limit - 1);
	}
	return (safe_color(v.col));
}

t_vect  direct_light(t_ray ray, t_all data, t_data_light *light)
{
	t_vect color = (t_vect){0,0,0};
	t_obj *objet;
	double cam_light;
	double light_behind;
	t_ray ray_light;

	t_vect light_direct;
	light_direct = sub_vect( light->direction, light->position);
	light_direct = get_normalized(light_direct);
	t_vect camera_to_light;
	camera_to_light = sub_vect(light->position, data.camera->pos);
	camera_to_light = get_normalized(camera_to_light);
	cam_light = vect_scal(ray.direction, light_direct);
	light_behind = vect_scal(light_direct, camera_to_light);

	if (cam_light < 0)
	{
		if (light_behind < 0)
		{
			ray_light.origine = data.camera->pos;
			ray_light.direction = camera_to_light;

			objet = find_closest(data, ray_light);
			if(objet->t != -1)
			{
				return ((t_vect){0,0,0});

			}
			color = (t_vect){255,255,255};
			cam_light = fabs(cam_light);
			cam_light = pow(cam_light, 500);
			color = vect_mult_val(color, cam_light);



		}
	}


	return(color);

}


static t_vect	light_n_shadow(t_obj *obj, t_all data, t_ray ray, t_vect col)
{
	col = light_obj(obj, data, ray, obj->t);
	col = on_shadow(obj, data, ray, col);
	return (col);
}

t_vect			rend_pix(t_all data, t_ray ray, int nbrbonds)
{
	t_vect		col;
	t_obj		*pos;

	if (nbrbonds == 0)
		return ((t_vect){0, 0, 0});
	col = direct_light(ray, data, data.light);
	pos = find_closest(data, ray);
	if (pos->t != -1)
	{
		if (pos->disruption)
			pos->color = disruption(pos, pos->color_copy);
		if (pos->type == 2)
			col = add_vect(vect_mult_val(pos->color, pos->refl),
					reflection(data, pos, nbrbonds, ray));
		else if (pos->type == 3)
			col = add_vect(vect_mult_val(pos->color, pos->trans),
					refraction(data, pos, nbrbonds, ray));
		else
			col = light_n_shadow(pos, data, ray, col);
	}
	return (safe_color(col));
}

void	set_pixel(t_all data, t_vect col, t_vect_i var, t_ray ray)
{
	if (SDL_SetRenderDrawColor(data.rend, col.x, col.y, col.z, 255) != 0)
		sdl_error("Get color failed");
	if (SDL_RenderDrawPoint(data.rend, var.x, var.y) != 0)
		sdl_error("draw point failed");
	data.screen_pixels[var.x * WIN_W + var.y] = col;
}

t_vect	negative_filter(t_vect col)
{
	col.x = 255 - col.x;
	col.y = 255 - col.y;
	col.z = 255 - col.z;
	return (col);
}

t_vect	red_blue(t_vect col, t_vect_i var)
{
	if (var.x < WIN_W / 2)
	{
		col.x += 50;
		col.y = 0;
		col.z = 0;
	}
	else
	{
		col.x = 0;
		col.y = 0;
		col.z += 50;
	}
	return (safe_color(col));
}

t_vect	filter(t_all *data, t_vect col, t_vect_i var)
{
	if (data->filter == 1)
		col = negative_filter(col);
	if (data->filter == 2)
		col = red_blue(col, var);
	return (col);
}

void	*raytracing(void *dataa)
{
	t_vect_i	var;
	t_ray		ray;
	t_vect		col;
	t_all		data;

	data = *((t_all *)(dataa));
	var.x = data.start - 1;
	while (++var.x < data.end)
	{
		var.y = -1;
		while (++var.y < WIN_H)
		{
			init_vect(&col, 0., 0., 0.);
			ray = new_ray(var.x, var.y, data);
			col = add_vect(col, rend_pix(data, ray, 6));
			col = filter(&data, col, var);
			set_pixel(data, col, var, ray);
		}
	}
	return (NULL);
}
