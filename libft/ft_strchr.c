/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 10:44:02 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:33:05 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		l;
	int		i;
	char	v;

	v = (char)c;
	l = ft_strlen(s);
	i = 0;
	while (s[i])
	{
		if (s[i] == v)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == v)
		return ((char *)s + i);
	return (0);
}
