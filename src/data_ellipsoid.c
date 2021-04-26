/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ellipsoid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:42:39 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 16:42:46 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	f_ellipsoid(char **str, int j, t_obj *ellipsoid)
{
	if (j == 0)
		init_vect(&ellipsoid->position, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&ellipsoid->direction, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&ellipsoid->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		ellipsoid->radius = ft_atof(str[0]);
	if (j == 4)
		ellipsoid->size = ft_atof(str[0]);
	ellipsoid->type = 1;
	ellipsoid->trans = 0;
	ellipsoid->refl = 0;
	ellipsoid->is_negative = 0;
	ellipsoid->disruption = 0;
}

int	s_ellipsoid(char **table, int i, t_obj *ellipsoid)
{
	int		j;
	char	**str;

	j = 0;
	ellipsoid->name = ft_strsub(table[i - 1], 0, ft_strlen(table[i - 1]) - 1);
	if (!space_counter(table[i]))
		return (-1);
	while (table[i] && j < 5)
	{
		if (!checker_loop(&str, table[i], j, 3))
			return (-1);
		f_ellipsoid(str, j, ellipsoid);
		j++;
		i++;
	}
	ellipsoid->inter = &intersection_ellipsoid;
	return (0);
}
