/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:01:06 by amya              #+#    #+#             */
/*   Updated: 2021/04/14 16:59:34 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int     white_split_check(char **str)
{
    int i;

    i = 0;
    if (str)
    {
        while(str[i])
            i++;
    }
    if (i == 2)
        return (1);
    return (0);
}

int		info_checker(char **ar)
{
	int		j;
	int		dot;
	int		i;
	
	i = -1;
	while (ar && ar[++i])
	{
		dot = 1;
		j = 0;
		while (ar[i][j])
		{
			if (!ft_isdigit(ar[i][j]))
			{
				if ((ar[i][j] == '-' && j != 0) || (ar[i][j] == '.'
				&& !dot && j == 0) ||(ar[i][j] == '.' && !ft_isdigit(ar[i][j + 1])))
					return (0);
				if (ar[i][j] == '.')
					dot--;
			}
			j++;
		}
	}
	if (i != 3)
		return (0);
	return (1);
}

int		checker_loop(char ***str, char *table, int j, int max_ints)
{
	char	**white_split;
	char	**str2;

	if (!space_counter(table))
		return (0);
	white_split = ft_strsplit(table, ' ');
	if (!white_split_check(white_split))
		return(0);
	if (j < max_ints)
		{
			str2 = ft_strsplit(white_split[1], ':');
			if (!info_checker(str2))
				return (0);
		}
	else
		str2 = ft_strsplit(white_split[1], ' ');
	free_2d(&white_split);
	*str = str2; 
	return (1);
}