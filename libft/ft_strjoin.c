/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:59:34 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/19 06:29:34 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if ((!s1) || (!s2))
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (i + j) + 1)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	str[i + j] = '\0';
	return (str);
}
