/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:48 by yoelguer          #+#    #+#             */
/*   Updated: 2021/03/29 12:57:01 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		f_ring2(char **str, int j, t_obj *ring)
{
	if (j == 4)
		init_vect(&ring->color, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		ring->radius = ft_atof(str[0]);
	if (j == 6)
		ring->size = ft_atof(str[0]);
	if (j == 7)
		ring->type = ft_atof(str[0]);
	if (j == 8)
		ring->trans = ft_atof(str[0]);
	if (j == 9)
		ring->refl = ft_atof(str[0]);
}

void		f_ring(char **str, int j, t_obj *ring)
{
	if (j == 0)
		init_vect(&ring->position, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&ring->direction, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&ring->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&ring->rotation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	f_ring2(str, j, ring);
}

int			s_ring(char **table, int i, t_all *data, t_obj *ring)
{
	int		j;
	char	**str;

	j = 0;
	ring->name = ft_strdup(table[i - 1]);
	ring->texture = ft_strdup(table[i]);
	while (table[++i] && j < 8)
	{
		str = ft_strsplit(table[i], ' ');
		if (f_str(str, j, 4) == -1)
			return (-1);
		f_ring(str, j, ring);
		j++;
	}
	data->id++;
	ring->id = data->id;
	if (ft_strcmp(ring->texture, ".") != 0)
		if (!(ring->surface = IMG_Load(ring->texture)))
			sdl_error("can't load surface");
	ring->direction = rot_vect_xyz(ring->direction, ring->rotation);
	ring->position = trans_vect_xyz(ring->position, ring->translation);
	ring->inter = &intersection_ray_ring;
	return (0);
}
