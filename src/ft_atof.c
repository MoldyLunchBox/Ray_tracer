/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:25 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:47:29 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"
#include <math.h>

double		ft_res(char *str, int i)
{
	int		j;
	double	res;

	res = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	j = 0;
	if (str[i] == '.')
	{
		i++;
		while (str[i] <= '9' && str[i] >= '0' && j <= 3)
		{
			res = res + (double)((str[i] - '0')
					/ pow(10.0, (double)++j));
			i++;
		}
	}
	return (res);
}

double		ft_atof(char *str)
{
	int		i;
	int		j;
	int		signe;
	double	res;

	i = 0;
	res = 0;
	signe = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		signe = str[i] == '-' ? -1 : 1;
		i++;
	}
	res = ft_res(str, i);
	return (res * signe);
}
