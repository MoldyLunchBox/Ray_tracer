/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 22:36:26 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/16 07:50:53 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		lent;
	char	*str;
	char	*src;

	i = 0;
	if (s)
	{
		src = (char*)s;
		lent = ft_strlen(s) + 1;
		if (!(str = (char*)malloc(sizeof(char) * lent)))
			return (NULL);
		while (src[i] != '\0')
		{
			str[i] = f(src[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
