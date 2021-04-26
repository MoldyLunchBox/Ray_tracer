/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_paraploid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:32:44 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 15:41:55 by amya             ###   ########.fr       */
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
		init_vect(&paraploid->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		paraploid->radius = ft_atof(str[0]);
	paraploid->type = 1;
	paraploid->trans = 0;
	paraploid->refl = 0;
	paraploid->is_negative = 0;
	paraploid->disruption = 0;
}

int	s_paraploid(char **table, int i, t_obj *paraploid)
{
	int		j;
	char	**str;

	j = 0;
	paraploid->name = ft_strsub(table[i - 1], 0, ft_strlen(table[i - 1]) - 1);
	if (!space_counter(table[i]))
		return (-1);
	while (table[i] && j < 4)
	{
		if (!checker_loop(&str, table[i], j, 3))
			return (-1);
		f_paraploid(str, j, paraploid);
		j++;
		i++;
	}
	paraploid->inter = &intersection_paraploid;
	return (0);
}
