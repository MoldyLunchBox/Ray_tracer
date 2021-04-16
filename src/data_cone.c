/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:45:53 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/15 12:56:53 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	sd_cone(char **str, int j, t_obj *cone)
{
	if (j == 7)
		cone->radius = ft_atof(str[0]);
	if (j == 8)
		cone->size = ft_atof(str[0]);
	if (j == 9)
		cone->type = ft_atof(str[0]);
	if (j == 10)
		cone->trans = ft_atof(str[0]);
	if (j == 11)
		cone->refl = ft_atof(str[0]);
	if (j == 12)
		cone->disruption = ft_atof(str[0]);
	cone->is_negative = 0;
}

void	f_cone(char **str, int j, t_obj *cone)
{
	if (j == -1)
		init_vect(&cone->text_modif, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 0)
		init_vect(&cone->position, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&cone->direction, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&cone->translation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&cone->rotation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&cone->slice, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		init_vect(&cone->pos_slice, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 6)
		init_vect(&cone->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	sd_cone(str, j, cone);
}

void	free_2d(char ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		free((*str)[i]);
	free((*str));
	(*str) = NULL;
}

void	load_texture(t_all *data, t_obj *cone)
{
	data->id++;
	cone->id = data->id;
	if (ft_strcmp(cone->texture, ".") != 0)
	{
		cone->surface = IMG_Load(cone->texture);
		if (!cone->surface)
			sdl_error("can't load surface");
	}
	if (ft_strcmp(cone->texture, ".") == 0)
		cone->direction = rot_vect_xyz(cone->direction, cone->rotation);
	cone->position = trans_vect_xyz(cone->position, cone->translation);
	cone->inter = &intersection_ray_cone;
}

int	s_cone(char **table, int i, t_all *data, t_obj *cone)
{
	int		j;
	char	**str;
	char	**white_split;

	j = -1;
	cone->name = ft_strsub(table[i - 1], 0, ft_strlen(table[i - 1]) - 1);
	if (!space_counter(table[i]))
		return (-1);
	white_split = ft_strsplit(table[i], ' ');
	if (!white_split_check(white_split))
		return (-1);
	cone->texture = ft_strdup(white_split[1]);
	free_2d(&white_split);
	while (table[++i] && j < 12)
	{
		if (!checker_loop(&str, table[i], j, 7))
			return (-1);
		f_cone(str, j, cone);
		j++;
	}
	load_texture(data, cone);
	return (0);
}
