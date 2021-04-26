/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split4fil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 06:35:13 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:32:39 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	case1(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

int	case2(char **ptr, char *str, char c)
{
	int	i;
	int	count;
	int	j;

	j = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] && str[i] != c)
			{
				i++;
				count++;
			}
			ptr[j] = (char *)(malloc(count + 1));
			count = 0;
			j++;
		}
		if (str[i])
			i++;
	}
	return (0);
}

static void	fill(char **ptr, char *str, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] && str[i] != c)
			{
				ptr[k][j] = str[i];
				i++;
				j++;
			}
			ptr[k][j] = '\0';
			j = 0;
			k++;
		}
		if (str[i])
			i++;
	}
}

char	**ft_split4fil(char *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		n;
	int		size;

	ptr = NULL;
	if (s != NULL && c != '\0')
	{
		size = 0;
		n = case1((char *)s, c);
		j = 0;
		i = 0;
		ptr = (char **)(malloc(sizeof(char *) * (n + 1)));
		if (ptr == NULL)
			return (0);
		ptr[n] = NULL;
		case2(ptr, (char *)s, c);
		fill(ptr, (char *)s, c);
	}
	return (ptr);
}
