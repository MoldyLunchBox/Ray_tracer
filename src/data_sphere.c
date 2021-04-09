/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:00 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/06 19:43:23 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		f_sphere2(char **str, int j, t_obj *sphere)
{
	if (j == 6)
		init_vect(&sphere->color, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 7)
		sphere->radius = ft_atof(str[0]);
	if (j == 8)
		sphere->size = ft_atof(str[0]);
	if (j == 9)
		sphere->type = ft_atof(str[0]);
	if (j == 10)
		sphere->trans = ft_atof(str[0]);
	if (j == 11)
		sphere->refl = ft_atof(str[0]);
	if (j == 12)
		sphere->is_negative = ft_atof(str[0]);
	if (j == 13)
		sphere->disruption = ft_atof(str[0]);
}

void		f_sphere(char **str, int j, t_obj *sphere)
{
	if (j == -1)
		init_vect(&sphere->text_modif, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 0)
		init_vect(&sphere->position, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&sphere->direction, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&sphere->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&sphere->rotation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&sphere->slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		init_vect(&sphere->pos_slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	f_sphere2(str, j, sphere);
}

int			s_sphere(char **table, int i, t_all *data, t_obj *sphere)
{
	int		j;
	char	**str;
	char	**white_split;

	j = -1;
	sphere->name = ft_strsub(table[i - 1], 0, ft_strlen(table[i - 1]) - 1);
	if (!space_counter(table[i]))
		return (-1);
	white_split = ft_strsplit(table[i], ' ');
	if (!white_split_check(white_split))
		return(-1);
	sphere->texture = ft_strdup(white_split[1]);
	free_2d(&white_split);
	while (table[++i] && j < 14)
	{
		if (!checker_loop(&str, table[i], j))
			return (-1);
		f_sphere(str, j, sphere);
		j++;
	}
	data->id++;
	sphere->id = data->id;
	if (ft_strcmp(sphere->texture, ".") != 0)
		if (!(sphere->surface = IMG_Load(sphere->texture)))
			sdl_error("can't load surface");
	if (ft_strcmp(sphere->texture, ".") == 0)
		sphere->direction = rot_vect_xyz(sphere->direction,
		sphere->rotation);
	sphere->position = trans_vect_xyz(sphere->position, sphere->translation);
	sphere->inter = &intersection_ray_sphere;
	return (0);
}
