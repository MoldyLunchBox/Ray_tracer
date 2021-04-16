/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:20:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/15 17:20:28 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

int	ft_lines_in_file(char *str)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	if (close(fd) < 0)
		return (-1);
	return (count);
}
