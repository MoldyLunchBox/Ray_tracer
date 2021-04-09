/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:00 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/02 17:03:37 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		f_sphere2(char **str, int j, t_obj *sphere)
{
	if (j == 5)
	{
		init_vect(&sphere->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
		sphere->color_copy = sphere->color;
	}
	if (j == 6)
		sphere->radius = ft_atof(str[0]);
	if (j == 7)
		sphere->type = ft_atof(str[0]);
	if (j == 8)
		sphere->trans = ft_atof(str[0]);
	if (j == 9)
		sphere->refl = ft_atof(str[0]);
	sphere->zero_one_to_skip = 0;
	sphere->is_negative = 1;
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
		init_vect(&sphere->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&sphere->rotation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&sphere->slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&sphere->pos_slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	f_sphere2(str, j, sphere);
}

int			s_sphere(char **table, int i, t_all *data, t_obj *sphere)
{
	int		j;
	char	**str;

	j = -1;
	sphere->name = ft_strdup(table[i - 1]);
	sphere->texture = ft_strdup(table[i]);
	while (table[++i] && j < 10)
	{
		str = ft_strsplit(table[i], ' ');
		if (f_str(str, j, 5) == -1)
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
