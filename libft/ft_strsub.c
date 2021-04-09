/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 23:58:04 by yoelguer          #+#    #+#             */
/*   Updated: 2019/06/13 22:11:37 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	char	*p_s;

	if (s)
	{
		i = 0;
		p_s = (char*)s;
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (p_s[start] != '\0' && i < len)
		{
			str[i] = p_s[start];
			i++;
			start++;
		}
		return (str);
	}
	return (NULL);
}
