/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:45:52 by amya              #+#    #+#             */
/*   Updated: 2021/04/20 12:26:40 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int	f_str2(char **str, int j, int d)
{
	int		k;

	k = 0;
	if (check_str1(str, j, d) == -1)
		return (-1);
	if (j < d)
	{
		if (ft_val(str[k]) || ft_val(str[k + 1])
			|| ft_val(str[k + 2]))
			return (-1);
	}
	else if (j == d)
	{
		if (ft_val(str[k]) || ft_val(str[k + 1])
			|| ft_val(str[k + 2]))
			return (-1);
	}
	else
	{
		if (ft_val2(str[k]))
			return (-1);
	}
	return (1);
}

double	get_length(t_vect u)
{
	return (sqrt((u.x * u.x) + (u.y * u.y) + (u.z * u.z)));
}

static void	check_form(char *str, int *i, int *j)
{
	while (ft_isalpha(str[*i]) || str[*i] == '_')
		(*i)++;
	if (str[*i] == ':')
	{
		(*i)++;
		while (str[*i] == ' ')
		{
			(*i)++;
			(*j)++;
		}
	}
}

int	space_counter(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (str)
	{
		while (str[i] == ' ')
			i++;
		if (i == 1)
			check_form(str, &i, &j);
		if (j == 1)
			return (1);
	}
	return (0);
}
