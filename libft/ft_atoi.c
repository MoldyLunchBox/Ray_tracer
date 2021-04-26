/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 04:26:28 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:25:26 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static	int	ft_sign(const char *str, int i, int sign)
{
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		else
			sign = 1;
		i++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	r;

	i = 0;
	sign = 0;
	r = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	sign = ft_sign(str, i, sign);
	if (sign != 0)
		i++;
	else
		sign = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r >= LONG_MAX && sign == 1)
			return (-1);
		if (r >= (unsigned long)LONG_MIN * (-1) && sign == -1)
			return (0);
		i++;
	}
	return (r * sign);
}
