/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:20:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/19 17:21:38 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int	ft_lines_in_file(char *str)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
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

int	ft_objects_rest(t_all *data, int i, char **table, t_obj **obj)
{
	if (ft_strcmp("box:", table[i]) == 0)
		if (s_box(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("limited_cylinder:", table[i]) == 0)
		if (s_limited_cylinder(table, i + 1, data, *obj) < 0)
			return (-1);
	if (ft_strcmp("limited_cone:", table[i]) == 0)
		if (s_limited_cone(table, i + 1, data, *obj) < 0)
			return (-1);
	return (0);
}

int	is_object(char *str)
{
	if (ft_strcmp("cylinder:", str) == 0
		|| ft_strcmp("sphere:", str) == 0
		|| ft_strcmp("cone:", str) == 0
		|| ft_strcmp("plane:", str) == 0
		|| ft_strcmp("ellipsoid:", str) == 0
		|| ft_strcmp("box:", str) == 0
		|| ft_strcmp("paraploid:", str) == 0
		|| ft_strcmp("limited_cylinder:", str) == 0
		|| ft_strcmp("limited_cone:", str) == 0)
		return (1);
	return (0);
}

double	if_t1_isnull(double t1, t_sol t)
{
	if (t1 == -1)
		t1 = t.tmin;
	return (t1);
}
double	if_t1_isbigger(double t1, t_sol t)
{
	if (t1 > t.tmin)
		t1 = t.tmin;
	return (t1);
}