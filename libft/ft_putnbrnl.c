/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:58:03 by amya              #+#    #+#             */
/*   Updated: 2019/04/08 11:06:43 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrnl(int n)
{
	unsigned int	k;

	k = (unsigned int)(n);
	if (n < 0)
	{
		ft_putchar('-');
		k = -k;
	}
	if (k <= 9)
		ft_putchar(k + '0');
	else
	{
		ft_putnbr(k / 10);
		ft_putchar(k % 10 + '0');
	}
	ft_putchar('\n');
}
