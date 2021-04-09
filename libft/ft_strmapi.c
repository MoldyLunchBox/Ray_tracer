/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 23:24:01 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/16 07:53:14 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	int		lent;
	char	*str;
	char	*src;

	i = 0;
	j = 0;
	if (s)
	{
		src = (char*)s;
		lent = ft_strlen(s) + 1;
		if (!(str = (char*)malloc(sizeof(char) * lent)))
			return (NULL);
		while (src[i] != '\0')
		{
			str[i] = f(j, src[i]);
			i++;
			j++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
