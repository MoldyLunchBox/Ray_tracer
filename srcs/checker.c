/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:17:33 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/11 17:16:16 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_checker(t_data **data)
{
	int	i;
	int	light;

	light = 0;
	i = -1;
	while ((*data)->tab[++i])
	{
		if (ft_strcmp((*data)->tab[i], "camera") == 0)
			camera_check(data, i);
		if (ft_strcmp((*data)->tab[i], "sphere") == 0)
			obj_check(data, i, 1);
		if (ft_strcmp((*data)->tab[i], "cylinder") == 0)
			obj_check(data, i, 2);
		if (ft_strcmp((*data)->tab[i], "light") == 0)
			light_check(data, i, light++);
		if (ft_strcmp((*data)->tab[i], "plane") == 0)
			obj_check(data, i, 4);
		if (ft_strcmp((*data)->tab[i], "cone") == 0)
			obj_check(data, i, 5);
		if (ft_strcmp((*data)->tab[i], "ellipsoid") == 0)
			obj_check(data, i, 6);
		if (ft_strcmp((*data)->tab[i], "paraploid") == 0)
			obj_check(data, i, 7);

	}
	if (!light)
		call_error(*data);
	return (0);
}

int		str_isnum(char *tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_isdigit(tab[i]))
			i++;
		else
			return (0);
	}
	return (i);
}

void	obj_check(t_data **dat, int i, int id)
{
	int		check;
	t_obj	*temp;
	t_data	*data;

	data = *dat;
	check = 1;
	while (data->tab[i + check] && check < 4)
		check++;
	if (check != 4 && id != 6)
		call_error(data);
	temp = add_node(dat);
	i = init_obj(temp, i, data, id);
	if (id == 1)
		temp->inter = &intersection_spher;
	else if (id == 2)
		temp->inter = &intersection_cylinder;
	else if (id == 4)
		temp->inter = &intersect_plane;
	else if (id == 5)
		temp->inter = &cone_intersection;
	else if (id == 6)
		temp->inter = &intersection_ellipsoid;
	else if (id == 7)
		temp->inter = &intersection_paraploid;

}

void	camera_check(t_data **dat, int i)
{
	int		check;
	t_data	*data;

	data = *dat;
	check = 1;
	while (data->tab[i + check] && check < 3)
		check++;
	if (check != 3)
		call_error(data);
	data->camera->look_from = split_data(data, data->tab[i + 1]);
	data->camera->cam_dir = split_data(data, data->tab[i + 2]);
}

void	light_check(t_data **dat, int i, int light)
{
	int		check;
	t_data	*data;

	(void)light;
	data = *dat;
	check = 1;
	while (data->tab[i + check] && check < 2)
		check++;
	if (check != 2)
		call_error(data);
	data->light->pos = split_data(data, data->tab[i + 1]);
	data->light->color = split_data(data, data->tab[i + 2]);
}
