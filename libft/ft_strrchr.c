/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 00:56:31 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:35:14 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	v;
	char	*r;
	int		check;

	check = 0;
	v = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == v)
		{
			check = 1;
			r = (char *)s + i;
		}
		i++;
	}
	if (check)
		return (r);
	if (s[i] == v)
		return ((char *)s + i);
	return (0);
}
