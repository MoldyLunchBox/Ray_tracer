/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:05:10 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/11 05:03:45 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t					i;
	const unsigned char		*sc;
	unsigned char			*dt;

	i = 0;
	dt = (unsigned char *)dst;
	sc = (const unsigned char *)src;
	while (i < n)
	{
		dt[i] = sc[i];
		if (sc[i] == (unsigned char)c)
			return (dt + i + 1);
		i++;
	}
	return (NULL);
}
