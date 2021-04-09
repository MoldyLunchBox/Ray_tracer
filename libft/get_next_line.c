/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:16:46 by yoelguer          #+#    #+#             */
/*   Updated: 2019/10/23 23:29:14 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_there(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		ft_copy(char **str, char **line)
{
	int			i;
	char		*ptr;
	char		*tmp;

	i = 0;
	ptr = *str;
	if (ft_is_there(ptr, '\n') == 0)
	{
		*line = ft_strdup(ptr);
		ft_strdel(str);
		return (1);
	}
	tmp = ft_strchr(*str, '\n');
	*tmp = '\0';
	*line = ft_strdup(*str);
	*str = ft_strdup(tmp + 1);
	ft_strdel(&ptr);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	char		*ptr;
	static char	*str[10240];
	int			ret;

	if (fd < 0 || fd > 10240 || read(fd, buff, 0) < 0)
		return (-1);
	(!str[fd]) ? str[fd] = ft_strnew(0) : str[fd];
	while (!ft_is_there(str[fd], '\n') && (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		ptr = str[fd];
		str[fd] = ft_strjoin(str[fd], buff);
		ft_strdel(&ptr);
		if (ft_is_there(str[fd], '\n') || ret < BUFF_SIZE)
			break ;
	}
	if (ret <= 0 && !*str[fd])
	{
		if (ret < 0)
			ft_strdel(&str[fd]);
		return (ret);
	}
	return (ft_copy(&str[fd], line));
}
