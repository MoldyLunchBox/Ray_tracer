/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:03:56 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/08 17:04:27 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int pos;

	if (n >= 0)
	{
		pos = n;
	}
	else
	{
		ft_putchar('-');
		pos = n * -1;
	}
	if (pos >= 10)
		ft_putnbr(pos / 10);
	ft_putchar(48 + pos % 10);
}
