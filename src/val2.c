/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:45:52 by amya              #+#    #+#             */
/*   Updated: 2021/03/28 18:48:22 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int			f_str2(char **str, int j, int d)
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

double		get_length(t_vect u)
{
	return (sqrt((u.x * u.x) + (u.y * u.y) + (u.z * u.z)));
}
