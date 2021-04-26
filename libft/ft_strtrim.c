/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 05:05:10 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:39:03 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		max;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	max = ft_strlen(s);
	if (max != 1)
		max -= !!max;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[max] == ' ' || s[max] == '\n' || s[max] == '\t')
		max--;
	if (max - i > 0)
		return (ft_strsub(s, i, max - i + 1));
	return (NULL);
}
