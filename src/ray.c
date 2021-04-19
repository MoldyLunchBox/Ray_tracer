/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:33:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/17 14:27:26 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	init_ray(t_ray *r, t_vect origine, t_vect direc)
{
	r->origine = origine;
	r->direction = direc;
}

t_ray	init_rayy(int i, int j, t_data_camera *cam)
{
	t_vect	s;
	t_ray	r;
	t_vect	destination;
	t_vect	new_cam_pos;

	s = sub_vect(cam->pos, vect_mult_val(cam->dir, cam->dist));
	s = sub_vect(s, vect_mult_val(cam->u_dir, i - (WIN_W / 2)));
	s = add_vect(s, vect_mult_val(cam->v_dir, (WIN_H / 2) - j));
	r.direction = sub_vect(s, cam->pos);
	normalize(&(r.direction));
	destination = add_vect(cam->pos, vect_mult_val(r.direction,
				cam->focus_dis));
	r.origine = cam->pos;
	r.direction = get_normalized(sub_vect(destination, cam->pos));
	return (r);
}
