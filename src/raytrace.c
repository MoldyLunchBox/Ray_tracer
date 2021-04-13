/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:48:25 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/12 19:57:09 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void			cylinder_surface_normal(t_obj *obj, double t, t_ray ray)
{
	obj->hit = add_vect(ray.origine, vect_mult_val(ray.direction, t));
	obj->norm = get_normalized(sub_vect(sub_vect(obj->hit, obj->position),
			vect_mult_val(obj->direction, vect_scal(obj->direction,
			sub_vect(obj->hit, obj->position)))));
	obj->norm = vect_mult_val(obj->norm, -1);
}
t_sol			look_for_negative(t_obj *obj, t_all data, t_sol t, t_ray ray)
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
			{
				t.tmin = -1;
				if (t.tmax <= t2.tmax && t.tmax >= t2.tmin)
				{
					t.tmax = -1;
					return (t);
				}
				cylinder_surface_normal(obj, t.tmax, ray);
				return (t);
			}
		}
		looper = looper->next;
	}
	return (t);
}
double			find_obj_scnd(t_all data, t_ray ray, t_ray to_light, t_obj *pos)
{
	t_obj		*header;
	t_sol		t;
	double		t1;

	t1 = -1;
	header = data.obj;
	while (header->next)
	{
		if (header->id == pos->id && (header = header->next))
			continue;
		if (!header->is_negative)
			t = header->inter(header, to_light);
		else
		{
			t.tmin = -1;
			t.tmax = -1;
		}
		if (t.tmin != -1 && ft_strequ(header->name, (char const *)"cylinder"))
		{
			t = look_for_negative(header, data, t, to_light);
			if (t.tmin == -1)
			{
				t.tmin = t.tmax;
			}
		}
		if (t.tmin != -1)
		{
			if (t1 == -1)
				t1 = t.tmin;
			else
			{
				if (t1 > t.tmin)
					t1 = t.tmin;
			}
		}
		header = header->next;
	}
	return (t1);
}


t_obj			*find_closest(t_all data, t_ray ray)
{
	t_obj		*pos;
	t_obj		*header;
	t_sol		t;
	double		t1;

	t1 = -1;
	t.tmin = -1;
	t.tmax = -1;
	header = data.obj;
	pos = header;
	while (header->next)
	{
		if (!header->is_negative)
			t = header->inter(header, ray);
		else
		{
			t.tmin = -1;
			t.tmax = -1;
		}
		if (t.tmin != -1 && ft_strequ(header->name, (char const *)"cylinder"))
		{
			t = look_for_negative(header, data, t, ray);
			if (t.tmin == -1)
			{
				t.tmin = t.tmax;
			}
		}
		if (t.tmin != -1)
		{
			t1 == -1 ? pos = header : 0;
			t1 == -1 ? t1 = t.tmin : 0;
			t1 > t.tmin ? pos = header : 0;
			t1 > t.tmin ? t1 = t.tmin : 0;
		}
		header = header->next;
	}
	pos->t = t1;
	return (pos);
}

t_vect			sorting(t_vect in)
{
	t_vect	ret;
	int		hold;
	t_vect	order;

	order = (t_vect){1, 2, 3};
	ret = (t_vect){fabs(in.x), fabs(in.y), fabs(in.z)};
	if (ret.x > ret.y)
	{
		hold = ret.y;
		ret.y = ret.x;
		ret.x = hold;
		hold = order.y;
		order.y = order.x;
		order.x = hold;
	}
	if (ret.x > ret.z)
	{
		hold = ret.z;
		ret.z = ret.x;
		ret.x = hold;
		hold = order.z;
		order.z = order.x;
		order.x = hold;
	}
	if (ret.y > ret.z)
	{
		hold = ret.z;
		ret.z = ret.y;
		ret.y = hold;
		hold = order.z;
		order.z = order.y;
		order.y = hold;
	}
	if (ret.x > ret.z)
	{
		hold = ret.z;
		ret.z = ret.x;
		ret.x = hold;
		hold = order.z;
		order.z = order.x;
		order.x = hold;
	}
	return (order);
}

t_vect			distrupt_a_sphere(t_obj *obj, t_vect col)
{
	t_vect	center_to_hit;
	double	hit_to_axis;
	double	center_to_hit_len;
	center_to_hit = obj->hit;
	center_to_hit_len = sqrt(center_to_hit.x*center_to_hit.x + center_to_hit.y*center_to_hit.y + center_to_hit.z*center_to_hit.z);
	// hit_to_axis = sqrt((center_to_hit_len * center_to_hit_len) - (obj->radius * obj->radius));
	if ((int)center_to_hit_len % 2)
		col = (t_vect){255,0,0};
	else
		col = (t_vect){255,255,255};
	return (col);
}

t_vect			distrupt_a_sphere_color(t_obj *obj, t_vect col)
{
	
	col = (t_vect){255, 255, 255};
	col.x *= 1 - fabs(2*(obj->hit.x - floor(obj->hit.x) - 1));
col.x = fabs(col.x);
	col.y *= 1 - fabs(2*(obj->hit.y - floor(obj->hit.y) - 1));
col.y = fabs(col.y);
	col.z *= 1 - fabs(2*(obj->hit.z - floor(obj->hit.z) - 1));
	col.z = fabs(col.z);
	return (col);
}


t_vect			disruption(t_obj *obj, t_vect col)
{
	double	res;
	double	res2;
	double	res3;
	t_vect	vec;
	t_vect	usable_res;

	if (obj->disruption == 1)
	{
		vec = sorting(obj->norm);
		// printf("\n%f %f %f %f %f",obj->norm.x, obj->norm.y, obj->norm.z, vec.x, vec.y, vec.z);
		if (obj->hit.x < 0)
			res = ((int)obj->hit.x - 1) % 2;
		else
			res = ((int)obj->hit.x) % 2;
		if (obj->hit.y < 0)
			res2 = ((int)obj->hit.y - 1) % 2;
		else
			res2 = ((int)obj->hit.y) % 2;
		if (obj->hit.z < 0)
			res3 = ((int)obj->hit.z - 1) % 2;
		else
			res3 = ((int)obj->hit.z) % 2;
		if (vec.x == 1)
			usable_res.x = res;
		if (vec.x == 2)
			usable_res.x = res2;
		if (vec.x == 3)
			usable_res.x = res3;
		if (vec.y == 1)
			usable_res.y = res;
		if (vec.y == 2)
			usable_res.y = res2;
		if (vec.y == 3)
			usable_res.y = res3;
		// exit(1);
		// t_vect	hit_to_pos=sub_vect(obj->hit, obj->position);
		// normalize(&hit_to_pos);
		// test = vect_scal(hit_to_pos, obj->norm);
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

#include <time.h>
#include <stdlib.h>
#include  <stdio.h>

float random_gen(){
	static int initialized = 0;

	if (!initialized){
		srand((time(NULL)));
	}

	return (drand48()  * 2.0 - 1.0)/ 1000.0f;
}

t_vect			reflection(t_all data, t_obj *obj, int nbrbonds, t_ray ray)
{
	t_vect	light_plus_norm;
	t_vect	ray_copy;
	t_ray	reflected_ray;
	t_vect	color;
	t_vect p;
	double n_dot_d;


	// p = (t_vect){obj->hit.x + random_gen(), obj->hit.y + random_gen(),  obj->hit.z + random_gen()};


	n_dot_d = vect_scal(ray.direction, obj->norm) * 2;
	reflected_ray.direction = vect_mult_val(obj->norm, n_dot_d);
	reflected_ray.direction = sub_vect(ray.direction, reflected_ray.direction);
	// light_plus_norm = add_vect(ray_copy, vect_mult_val(obj->norm, 2));
	reflected_ray.origine = add_vect(obj->hit, vect_mult_val(obj->norm, 0.01));
	// reflected_ray.direction = light_plus_norm;
	color = rend_pix(data, reflected_ray, --nbrbonds);
	return color;
}

int				under_shadow(t_vect col)
{
	if (!col.x && !col.y && !col.z)
		return (0);
	return (1);
}

t_vect			refraction(t_all data, t_obj *obj, int limit, t_ray ray)
{
	t_ray		refracted_ray;
	double		n1 = 1;
	double		n2 = 1.3;
	double		radical;
	t_vect		col;
	t_vect		ref_norm;

	ref_norm = (t_vect){obj->norm.x, obj->norm.y, obj->norm.z};
	if (vect_scal(ray.direction, obj->norm) > 0)
	{
		n1 = 1.3;
		n2 = 1;
		ref_norm = vect_mult_val(obj->norm, -1);
	}
	radical = 1 - pow(n1/n2, 2) * (1 - pow(vect_scal(ref_norm, ray.direction), 2));
	if (radical > 0)
	{
		refracted_ray.origine = sub_vect(obj->hit, vect_mult_val(ref_norm, 0.001));
		refracted_ray.direction = sub_vect(vect_mult_val(sub_vect(ray.direction, vect_mult_val(ref_norm,vect_scal(ray.direction, ref_norm))), n1/n2) , vect_mult_val(ref_norm , sqrt(radical)));
		col = rend_pix(data, refracted_ray, limit-1);
	}
	return safe_color(col);

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




t_vect			rend_pix(t_all data, t_ray ray, int nbrbonds)
{
	t_vect		col;
	int			shad;
	t_obj		*pos;

	if (nbrbonds == 0)
		return ((t_vect){0, 0, 0});
	col = (t_vect){0, 0, 0};
	col = direct_light(ray, data, data.light);
	pos = find_closest(data, ray);
	if (pos->t != -1)
	{
		if (pos->disruption)
			pos->color = disruption(pos, pos->color_copy);
		if (pos->type == 2)
		{
			col = add_vect(vect_mult_val(pos->color, pos->refl), reflection(data, pos, nbrbonds, ray));
		}
		else if (pos->type == 3)
			col = add_vect(vect_mult_val(pos->color, pos->trans),refraction(data, pos, nbrbonds, ray));
		else
		{
			col = light_obj(pos, data, ray, pos->t);
			col = on_shadow(pos, data, ray, col);
		}
	}
	return (safe_color(col));
}

void			set_pixel(t_all data, t_vect col, t_vect_i var, t_ray ray)
{

	if (SDL_SetRenderDrawColor(data.rend, col.x, col.y, col.z, 255) != 0)
		sdl_error("Get color failed");
	if (SDL_RenderDrawPoint(data.rend, var.x, var.y) != 0)
		sdl_error("draw point failed");
	data.screen_pixels[var.x * WIN_W + var.y] = col;
}

t_vect		negative_filter(t_vect col)
{
	col.x = 255 - col.x;
	col.y = 255 - col.y;
	col.z = 255 - col.z;
	return (col);
}

void			*raytracing(void *dataa)
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
			var.z = -1;
			while (++var.z < ((data.aalias || data.deep) ? NBR_RAYS : 1))
			{
				ray = new_ray(var.x, var.y, data);
				col = add_vect(col, vect_mult_val(rend_pix(data, ray, 6), 1. /
					((data.aalias || data.deep) ? NBR_RAYS : 1)));
			}
			// col = negative_filter(col);
			set_pixel(data, col, var, ray);
		}
	}

	filtre(&data);
	return (NULL);
}
