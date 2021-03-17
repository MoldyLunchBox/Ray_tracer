/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 00:06:47 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/12 06:01:56 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while ((s[i] == '\t' || s[i] == '\n' || s[i] == ' ') && s[i])
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	while ((s[j] == '\t' || s[j] == '\n' || s[j] == ' ') && s[i])
		j--;
	str = ft_strsub((char *)s, i, j - i + 1);
	return (str);
}
