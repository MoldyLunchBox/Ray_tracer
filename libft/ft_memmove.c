/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 01:56:58 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/29 02:34:58 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dstt;
	char	*srcc;

	dstt = (char *)dst;
	srcc = (char *)src;
	if (srcc < dstt)
	{
		while (n--)
			*(dstt + n) = *(srcc + n);
	}
	else
		ft_memcpy(dstt, srcc, n);
	return (dst);
}
