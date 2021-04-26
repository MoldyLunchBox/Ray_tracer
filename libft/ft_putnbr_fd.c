/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:10:20 by amya              #+#    #+#             */
/*   Updated: 2019/04/08 07:52:18 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	k;

	k = (unsigned int)(n);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		k = -k;
	}
	if ((int)k >= 0 && k <= 9)
		ft_putchar_fd(k + '0', fd);
	else
	{
		ft_putnbr_fd(k / 10, fd);
		ft_putchar_fd(k % 10 + '0', fd);
	}
}
