/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 09:43:51 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/03 14:47:26 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		keyhook(int key, t_data *data)
{
	if (key == 53)
		ft_close(data);
	return (0);
}

int		ft_close(t_data *data)
{
	free_list(data->obj);
	exit(1);
	return (0);
}

void	call_error(t_data *data)
{
	free_2d(data->tab);
	ft_putstr("parsing error\n");
	exit(1);
}

void	image_clear(int *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
			d[y * WIDTH + x] = 0x000000;
		y++;
	}
}

t_obj	*add_node(t_data **dat)
{
	int		i;
	t_obj	*temp;
	t_obj	*p;
	t_data	*data;

	data = *dat;
	i = 1;
	temp = ft_memalloc(sizeof(t_obj));
	if (data->obj == NULL)
		data->obj = temp;
	else
	{
		p = data->obj;
		while (p->next != NULL)
		{
			p = p->next;
			i++;
		}
		p->next = temp;
	}
	temp->id = i;
	return (temp);
}
