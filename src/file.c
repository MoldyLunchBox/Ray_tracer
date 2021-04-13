/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:13 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/11 16:49:25 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int			ft_objects(t_all *data, int i, char **table, t_obj **obj)
{
	if (ft_strcmp("sphere:", table[i]) == 0)
		if (s_sphere(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("plane:", table[i]) == 0)
		if (s_plane(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("cylinder:", table[i]) == 0)
		if (s_cylinder(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("cone:", table[i]) == 0)
		if (s_cone(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("ring:", table[i]) == 0)
		if (s_ring(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("paraploid:", table[i]) == 0)
		if (s_paraploid(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("ellipsoid:", table[i]) == 0)
		if (s_ellipsoid(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("box:", table[i]) == 0)
		if (s_box(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("limited_cylinder:", table[i]) == 0)
		if (s_limited_cylinder(table, i + 1, data, *obj) < 0)
			return (-1);
	return (0);
}

int			ft_obj(char **table, t_all *data)
{
	int		i;
	t_obj	*obj;

	i = -1;
	obj = data->obj;
	data->id = 0;
	while (table[++i])
	{
		if (ft_strcmp("cylinder:", table[i]) == 0
				|| ft_strcmp("sphere:", table[i]) == 0
				|| ft_strcmp("cone:", table[i]) == 0
				|| ft_strcmp("plane:", table[i]) == 0
				|| ft_strcmp("ring:", table[i]) == 0
				|| ft_strcmp("ellipsoid:", table[i]) == 0
				|| ft_strcmp("box:", table[i]) == 0
				|| ft_strcmp("paraploid:", table[i]) == 0
				|| ft_strcmp("limited_cylinder:", table[i]) == 0)
		{
			if (ft_objects(data, i, table, &obj) < 0)
				return (-1);
			ft_alloc_obj(&obj->next);
			obj = obj->next;
		}
	}
	return (0);
}

int			ft_checker(char ***table, t_all *data)
{
	if (ft_camera(*table, data) < 0)
	{
		free(data->camera);
		return (-1);
	}
	if (ft_obj(*table, data) < 0)
	{
		ft_free_obj(data);
		return (-1);
	}
	if (ft_light(*table, data) < 0)
	{
		ft_free_obj(data);
		return (-1);
	}
	return (0);
}

int			ft_lines_in_file(char *str)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	if ((fd = open(str, O_RDONLY)) < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	if (close(fd) < 0)
		return (-1);
	return (count);
}

int			file_checker(char *str, t_all *data)
{
	int		fd;
	int		lines;
	int		i;
	char	**table;

	i = 0;
	lines = ft_lines_in_file(str);
	if (!(table = (char **)malloc(sizeof(char*) * (lines + 1))))
		return (-1);
	if ((fd = open(str, O_RDONLY)) < 0)
		return (-1);
	while (get_next_line(fd, &table[i]) > 0)
		i++;
	table[i] = NULL;
	if (ft_checker(&table, data) < 0)
	{
		ft_putendl("error data");
		ft_strdel(table);
		return (-1);
	}
	if (table != NULL)
		ft_strdel(table);
	return (1);
}
