/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ellipsoid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:46:09 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/15 13:08:18 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

static void	f_ellipsoid_rest(char **str, int j, t_obj *ellipsoid)
{
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
	ellipsoid->type = 1;
	ellipsoid->trans = 0;
	ellipsoid->refl = 0;
	ellipsoid->is_negative = 0;
	ellipsoid->disruption = 0;
}

void	f_ellipsoid(char **str, int j, t_obj *ellipsoid)
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
}

static void	load_texture(t_all *data, t_obj *ellipsoid)
{
	data->id++;
	ellipsoid->id = data->id;
	if (ft_strcmp(ellipsoid->texture, ".") != 0)
	{
		ellipsoid->surface = IMG_Load(ellipsoid->texture);
		if (!ellipsoid->surface)
			sdl_error("can't load surface");
	}
	ellipsoid->direction = rot_vect_xyz(ellipsoid->direction,
			ellipsoid->rotation);
	ellipsoid->position = trans_vect_xyz(ellipsoid->position,
			ellipsoid->translation);
	ellipsoid->inter = &intersection_ellipsoid;
}

int	s_ellipsoid(char **table, int i, t_all *data, t_obj *ellipsoid)
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
	load_texture(data, ellipsoid);
	return (0);
}
