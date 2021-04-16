/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:58:04 by amya              #+#    #+#             */
/*   Updated: 2021/04/15 12:38:00 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	f_box(char **str, int j, t_obj *box)
{
	if (j == 0)
		init_vect(&box->position, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&box->translation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&box->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		box->size = ft_atof(str[0]);
	box->type = 1;
	box->trans = 0;
	box->refl = 0;
	box->is_negative = 0;
	box->disruption = 0;
}

int	s_box(char **table, int i, t_all *data, t_obj *box)
{
	int		j;
	char	**str;
	char	**white_split;

	j = 0;
	box->name = ft_strsub(table[i - 1], 0, ft_strlen(table[i - 1]) - 1);
	if (!space_counter(table[i]))
		return (-1);
	while (table[i] && j < 4)
	{
		if (!checker_loop(&str, table[i], j, 3))
			return (-1);
		f_box(str, j, box);
		j++;
		i++;
	}
	data->id++;
	box->id = data->id;
	box->inter = &intersection_box;
	return (0);
}
