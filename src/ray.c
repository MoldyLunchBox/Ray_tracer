/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:33:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/16 11:33:24 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	init_ray(t_ray *r, t_vect origine, t_vect direc)
{
	r->origine = origine;
	r->direction = direc;
}

t_ray	init_rayy(t_2d_i var, t_data_camera *cam, t_2d_d alis, t_2d_d deep)
{
	t_vect	s;
	t_ray	r;
	t_vect	destination;
	t_vect	new_cam_pos;

	s = sub_vect(cam->pos, vect_mult_val(cam->dir, cam->dist));
	s = sub_vect(s, vect_mult_val(cam->u_dir, var.x - (WIN_W / 2) + alis.x));
	s = add_vect(s, vect_mult_val(cam->v_dir, (WIN_H / 2) - var.y + alis.y));
	r.direction = sub_vect(s, cam->pos);
	normalize(&(r.direction));
	destination = add_vect(cam->pos, vect_mult_val(r.direction,
				cam->focus_dis));
	new_cam_pos = add_vect(cam->pos, (t_vect){deep.x, deep.y, 0.});
	r.origine = new_cam_pos;
	r.direction = get_normalized(sub_vect(destination, new_cam_pos));
	return (r);
}
