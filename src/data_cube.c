/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:44:56 by amya              #+#    #+#             */
/*   Updated: 2021/03/28 17:40:55 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		f_cube(char **str, int j, t_obj *cube)
{
	if (j == 0)
		init_vect(&cube->position, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&cube->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&cube->color, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		cube->size = ft_atof(str[0]);
	if (j == 4)
		cube->type = ft_atof(str[0]);
	if (j == 5)
		cube->trans = ft_atof(str[0]);
	if (j == 6)
		cube->refl = ft_atof(str[0]);
}

int			s_cube(char **table, int i, t_all *data, t_obj *cube)
{
	int		j;
	char	**str;

	j = 0;
	cube->name = ft_strdup(table[i - 1]);
	cube->texture = ft_strdup(table[i]);
	while (table[++i] && j < 7)
	{
		str = ft_strsplit(table[i], ' ');
		if (f_str(str, j, 2) == -1)
			return (-1);
		f_cube(str, j, cube);
		j++;
	}
	data->id++;
	cube->id = data->id;
	if (ft_strcmp(cube->texture, ".") != 0)
		if (!(cube->surface = IMG_Load(cube->texture)))
			sdl_error("can't load surface");
	cube->direction = rot_vect_xyz(cube->direction,
			cube->rotation);
	cube->position = trans_vect_xyz(cube->position, cube->translation);
	cube->inter = &intersection_cube;
	return (0);
}
