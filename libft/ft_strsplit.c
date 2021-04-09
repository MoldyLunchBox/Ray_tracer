/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:54:19 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/18 05:56:18 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_words(const char *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (j == 1 && *s == c)
			j = 0;
		if (j == 0 && *s != c)
		{
			j = 1;
			i++;
		}
		s++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		word;
	int		i;
	int		j;
	int		start;
	char	**tab;

	if (s == 0 || c == 0)
		return (NULL);
	word = ft_count_words(s, c);
	if (!(tab = (char**)malloc((sizeof(char *) * (word + 1)))))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < word)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = ft_strsub(s, start, i - start);
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
