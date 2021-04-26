/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:46:00 by amya              #+#    #+#             */
/*   Updated: 2019/04/08 10:06:10 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len2;
	int		i;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	len2 = ft_strlen(needle);
	while (*haystack && len >= len2)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, len2) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
