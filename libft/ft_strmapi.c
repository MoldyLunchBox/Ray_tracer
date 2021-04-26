/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 04:20:39 by amya              #+#    #+#             */
/*   Updated: 2019/04/08 04:36:24 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s2;

	s2 = NULL;
	if (s != NULL && f != NULL)
	{
		i = 0;
		s2 = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
		if (s2 == NULL)
			return (0);
		while (s[i])
		{
			s2[i] = f(i, s[i]);
			i++;
		}
		s2[i] = '\0';
	}
	return (s2);
}
