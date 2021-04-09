/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:36:06 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/16 07:19:47 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p_s;

	i = 0;
	p_s = (char*)s;
	while (p_s[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (p_s[i] == c)
			return (p_s + i);
		i--;
	}
	return (NULL);
}
