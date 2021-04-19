/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:49:00 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/17 14:50:58 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int	ft_val(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if ((str[i] <= '9' && str[i] >= '0')
			|| str[i] == '.')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	ft_val2(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] <= '9' && str[i] >= '0')
			|| str[i] == '.')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	check_str2(char **str, int j, int k)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i != 3)
		return (-1);
	return (1);
}

int	check_str1(char **str, int j, int k)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if ((i == 1 && j == k + 1) || (i == 1 && j == k + 2)
		|| (i == 1 && j == k + 3) || (i == 1 && j == k + 4)
		|| (i == 1 && j == k + 5))
		return (1);
	if (i != 3)
		return (-1);
	return (1);
}

int	f_str(char **str, int j, int d)
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
		if (ft_val2(str[k]) || ft_val2(str[k + 1])
			|| ft_val2(str[k + 2]))
			return (-1);
	}
	else
	{
		if (ft_val2(str[k]))
			return (-1);
	}
	return (1);
}
