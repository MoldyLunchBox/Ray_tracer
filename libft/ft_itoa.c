/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 02:00:35 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:27:24 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_alloc(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 1;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	char			*ptr;
	unsigned int	n;
	unsigned int	i;
	unsigned int	total;

	if (nbr < 0)
		n = (unsigned int)(nbr * -1);
	else
		n = (unsigned int)nbr;
	total = (unsigned int)ft_alloc(nbr);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (total + 1));
	if (!ptr)
		return (0);
	if (nbr < 0)
		ptr[i] = '-';
	i = total - 1;
	while (n >= 10)
	{
		ptr[i--] = (char)(n % 10 + 48);
		n /= 10;
	}
	ptr[i] = (char)(n % 10 + 48);
	ptr[total] = '\0';
	return (ptr);
}
