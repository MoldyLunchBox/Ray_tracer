/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:09:16 by amya              #+#    #+#             */
/*   Updated: 2021/04/24 10:15:37 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_vect	light_is_behind(t_vect cam_to_light,
t_all data, double cam_light, t_data_light *light)
{
	t_obj	*objet;
	t_ray	ray_light;
	t_vect	color;
	double	obj_light;

	color = (t_vect){0, 0, 0};
	ray_light.origine = data.camera->pos;
	ray_light.direction = cam_to_light;
	objet = find_closest(data, ray_light);
	color = sub_vect(objet->position, light->position);
	color = get_normalized(color);
	obj_light = vect_scal(light->dir, color);
	if (objet->t != -1)
	{
		if (obj_light > 0)
			return ((t_vect){0, 0, 0});
	}
	color = (t_vect){255, 255, 255};
	cam_light = fabs(cam_light);
	cam_light = pow(cam_light, 500);
	color = vect_mult_val(color, cam_light);
	return (color);
}

t_vect	direct_light(t_ray ray, t_all data, t_data_light *light)
{
	t_vect	color;
	double	cam_light;
	double	light_behind;
	t_vect	camera_to_light;
	t_vect	light_direct;

	color = (t_vect){0, 0, 0};
	light_direct = sub_vect(light->look_at, light->position);
	light_direct = get_normalized(light_direct);
	light->dir = light_direct;
	camera_to_light = sub_vect(light->position, data.camera->pos);
	camera_to_light = get_normalized(camera_to_light);
	cam_light = vect_scal(ray.direction, light_direct);
	light_behind = vect_scal(light_direct, camera_to_light);
	if (cam_light < 0)
	{
		if (light_behind < 0)
			color = light_is_behind(camera_to_light, data, cam_light, light);
	}
	return (color);
}

t_vect	loop_direct_light(t_ray ray, t_all data, t_data_light *light)
{
	t_data_light	*head;
	t_vect			color;

	color = (t_vect){0, 0, 0};
	head = data.light;
	while (head)
	{
		if (head->type == 1)
			color = direct_light(ray, data, light);
		head = head->next;
	}
	return (color);
}
