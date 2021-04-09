/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:46:21 by yoelguer          #+#    #+#             */
/*   Updated: 2021/03/28 16:40:17 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		f_plane2(char **str, int j, t_obj *plane)
{
	if (j == 5)
		init_vect(&plane->pos_slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 6)
		init_vect(&plane->color, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 7)
		plane->size = ft_atof(str[0]);
	if (j == 8)
		plane->type = ft_atof(str[0]);
	if (j == 9)
		plane->trans = ft_atof(str[0]);
	if (j == 10)
		plane->refl = ft_atof(str[0]);
}

void		f_plane(char **str, int j, t_obj *plane)
{
	if (j == -1)
		init_vect(&plane->text_modif, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 0)
		init_vect(&plane->position, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&plane->direction, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&plane->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&plane->rotation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&plane->slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	f_plane2(str, j, plane);
}

int			s_plane(char **table, int i, t_all *data, t_obj *plane)
{
	int		j;
	char	**str;

	j = -1;
	plane->name = ft_strdup(table[i - 1]);
	plane->texture = ft_strdup(table[i]);
	while (table[++i] && j < 11)
	{
		str = ft_strsplit(table[i], ' ');
		if (f_str(str, j, 6) == -1)
			return (-1);
		f_plane(str, j, plane);
		j++;
	}
	data->id++;
	plane->id = data->id;
	if (ft_strcmp(plane->texture, ".") != 0)
		if (!(plane->surface = IMG_Load(plane->texture)))
			sdl_error("can't load surface");
	if (ft_strcmp(plane->texture, ".") == 0)
		plane->direction = rot_vect_xyz(plane->direction, plane->rotation);
	plane->position = trans_vect_xyz(plane->position, plane->translation);
	plane->half_size = plane->size / 2;
	plane->inter = &intersection_ray_plan;
	return (0);
}
