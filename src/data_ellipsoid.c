/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ellipsoid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:46:09 by yoelguer          #+#    #+#             */
/*   Updated: 2021/03/29 13:23:13 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		f_ellipsoid(char **str, int j, t_obj *ellipsoid)
{
	if (j == 0)
		init_vect(&ellipsoid->position, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&ellipsoid->direction, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&ellipsoid->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&ellipsoid->rotation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&ellipsoid->color, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		ellipsoid->radius = ft_atof(str[0]);
	if (j == 6)
		ellipsoid->size = ft_atof(str[0]);
	if (j == 7)
		ellipsoid->type = ft_atof(str[0]);
	if (j == 8)
		ellipsoid->trans = ft_atof(str[0]);
	if (j == 9)
		ellipsoid->refl = ft_atof(str[0]);
}

int			s_ellipsoid(char **table, int i, t_all *data, t_obj *ellipsoid)
{
	int		j;
	char	**str;

	j = 0;
	ellipsoid->name = ft_strdup(table[i - 1]);
	ellipsoid->texture = ft_strdup(table[i]);
	while (table[++i] && j < 10)
	{
		str = ft_strsplit(table[i], ' ');
		if (f_str(str, j, 4) == -1)
			return (-1);
		f_ellipsoid(str, j, ellipsoid);
		j++;
	}
	data->id++;
	ellipsoid->id = data->id;
	if (ft_strcmp(ellipsoid->texture, ".") != 0)
		if (!(ellipsoid->surface = IMG_Load(ellipsoid->texture)))
			sdl_error("can't load surface");
	ellipsoid->direction = rot_vect_xyz(ellipsoid->direction,
			ellipsoid->rotation);
	ellipsoid->position = trans_vect_xyz(ellipsoid->position,
			ellipsoid->translation);
	ellipsoid->inter = &intersection_ellipsoid;
	return (0);
}
