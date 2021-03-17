/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:51:00 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/19 06:20:11 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mots(char const *s, char c)
{
	int		i;
	int		l;
	int		k;

	i = 0;
	l = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		{
			k = 0;
			i++;
		}
		while (s[i] && s[i] != c)
		{
			if (k == 0)
			{
				k = 1;
				l++;
			}
			i++;
		}
	}
	return (l);
}

static int	chara(char const *s, char c, int i)
{
	int l;

	l = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		l++;
		i++;
	}
	return (l);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		l;
	int		j;

	i = 0;
	l = 0;
	if ((!s) || (!(tab = (char **)malloc(sizeof(char *) * (mots(s, c) + 1)))))
		return (NULL);
	while (s[i])
	{
		if (!(tab[l] = (char *)malloc(sizeof(char) * (chara(s, c, i) + 1))))
			return (NULL);
		while (s[i] == c)
			i++;
		j = 0;
		while (s[i] && s[i] != c)
			tab[l][j++] = s[i++];
		tab[l++][j] = '\0';
		while (s[i] == c)
			i++;
	}
	tab[mots(s, c)] = NULL;
	return (tab);
}
