/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:59:41 by amya              #+#    #+#             */
/*   Updated: 2021/04/18 16:20:56 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	f_camera(char **str, int j, t_data_camera *camera)
{
	if (j == 0)
		camera->pos = new_vect(ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		camera->dir = new_vect(ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		camera->dist = ft_atof(str[0]);
	if (j == 3)
		camera->focus_dis = ft_atof(str[0]);
}

void	set_camera_dir(t_data_camera *camera)
{
	t_vect	up;

	up = new_vect(0, 1.0, 0);
	if (up.x == camera->pos.x && up.z == camera->pos.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	camera->dir = get_normalized(sub_vect(camera->pos, camera->dir));
	camera->u_dir = get_normalized(vect_cross(camera->dir, up));
	camera->v_dir = vect_cross(camera->dir, camera->u_dir);
}

int	s_camera(char **table, int i, t_data_camera *camera)
{
	int		j;
	int		k;
	char	**space_split;
	char	**dot_split;

	j = 0;
	while (table[i] && j < 4)
	{
		k = 0;
		space_split = ft_strsplit(table[i], ' ');
		dot_split = ft_strsplit(space_split[1], ':');
		if (!space_counter(table[i]))
			return (-1);
		if (f_str2(dot_split, j, 1) == -1)
			return (-1);
		f_camera(dot_split, j, camera);
		j++;
		i++;
	}
	set_camera_dir(camera);
	return (0);
}

int	ft_camera(char **table, t_all *data)
{
	int		i;
	int		a;
	char	**aray;

	i = 0;
	a = 0;
	aray = table;
	while (table[i])
	{
		if (ft_strcmp("camera:", table[i]) == 0 && a == 0)
		{
			a = 1;
			if (s_camera(table, i + 1, (*data).camera) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}
