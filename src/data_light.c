/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:46:34 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/15 13:09:02 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	f_light(char **str, int j, t_data_light *light)
{
	int		k;

	k = 0;
	if (j == 0)
		init_vect(&light->position, ft_atof(str[k]),
			ft_atof(str[k + 1]), ft_atof(str[k + 2]));
	if (j == 1)
		init_vect(&light->direction, ft_atof(str[k]),
			ft_atof(str[k + 1]), ft_atof(str[k + 2]));
	if (j == 2)
		init_vect(&light->color, ft_atof(str[k]),
			ft_atof(str[k + 1]), ft_atof(str[k + 2]));
	if (j == 3)
		light->intensity = ft_atof(str[k]);
	if (j == 4)
		light->angle = ft_atof(str[k]);
	if (j == 5)
		light->type = ft_atof(str[k]);
	if (j == 6)
		light->ambient = ft_atof(str[k]);
}

int	s_light(char **table, int i, t_data_light *light)
{
	int		j;
	int		k;
	char	**space_split;
	char	**dot_split;

	j = 0;
	while (table[i] && j < 7)
	{
		k = 0;
		space_split = ft_strsplit(table[i], ' ');
		dot_split = ft_strsplit(space_split[1], ':');
		if (f_str(dot_split, j, 2) == -1)
			return (-1);
		if (!space_counter(table[i]))
			return (-1);
		f_light(dot_split, j, light);
		j++;
		i++;
	}
	return (0);
}

int	ft_light(char **table, t_all *data)
{
	int				i;
	char			**aray;
	t_data_light	*light;

	i = 0;
	aray = table;
	light = data->light;
	while (table[i])
	{
		if (ft_strcmp("light:", table[i]) == 0)
		{
			if (s_light(aray, i + 1, light) < 0)
				return (-1);
			ft_alloc_light(&light->next);
			light = light->next;
		}
		i++;
	}
	return (0);
}
