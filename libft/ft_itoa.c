/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:51:22 by ramoukha          #+#    #+#             */
/*   Updated: 2020/02/25 14:58:56 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		nmbrlen(int n)
{
	int		cmpt;

	cmpt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		cmpt++;
		n = n * (-1);
	}
	while (n)
	{
		n = n / 10;
		cmpt++;
	}
	return (cmpt);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = nmbrlen(n);
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	str[i] = '\0';
	while (n != 0)
	{
		i--;
		if (n < 0)
			str[i] = -(n % 10) + '0';
		else
			str[i] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}
