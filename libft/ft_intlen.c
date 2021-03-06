/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:42:21 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:26:19 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int nbr)
{
	int	i;

	i = 0;
	while (nbr)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}
