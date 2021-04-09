/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:41:02 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/17 03:02:50 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	int				i;
	unsigned char	*dst;
	unsigned char	*src;

	i = 0;
	dst = (unsigned char*)str1;
	src = (unsigned char*)str2;
	if (src >= dst)
	{
		while (n--)
		{
			dst[i] = src[i];
			i++;
		}
		return (dst);
	}
	if (dst > src)
	{
		while (n--)
			i++;
		while (i--)
			dst[i] = src[i];
		return (dst);
	}
	return (NULL);
}
