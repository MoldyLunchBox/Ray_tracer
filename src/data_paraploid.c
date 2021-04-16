/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_paraploid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:32:44 by amya              #+#    #+#             */
/*   Updated: 2021/04/15 13:32:45 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	f_paraploid(char **str, int j, t_obj *paraploid)
{
	if (j == 0)
		init_vect(&paraploid->position, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&paraploid->direction, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&paraploid->translation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&paraploid->rotation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&paraploid->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		paraploid->radius = ft_atof(str[0]);
	if (j == 6)
		paraploid->type = ft_atof(str[0]);
	if (j == 7)
		paraploid->trans = ft_atof(str[0]);
	if (j == 8)
		paraploid->refl = ft_atof(str[0]);
}

static void	load_texture(t_all *data, t_obj *paraploid)
{
	data->id++;
	paraploid->id = data->id;
	if (ft_strcmp(paraploid->texture, ".") != 0)
	{
		paraploid->surface = IMG_Load(paraploid->texture);
		if (!paraploid->surface)
			sdl_error("can't load surface");
	}
	paraploid->direction = rot_vect_xyz(paraploid->direction,
			paraploid->rotation);
	paraploid->position = trans_vect_xyz(paraploid->position,
			paraploid->translation);
	paraploid->inter = &intersection_paraploid;
}

int	s_paraploid(char **table, int i, t_all *data, t_obj *paraploid)
{
	int		j;
	char	**str;

	j = 0;
	paraploid->name = ft_strdup(table[i - 1]);
	paraploid->texture = ft_strdup(table[i]);
	while (table[++i] && j < 9)
	{
		str = ft_strsplit(table[i], ' ');
		if (f_str(str, j, 4) == -1)
			return (-1);
		f_paraploid(str, j, paraploid);
		j++;
	}
	load_texture(data, paraploid);
	return (0);
}
