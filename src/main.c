/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:36:32 by amya              #+#    #+#             */
/*   Updated: 2021/04/15 17:36:43 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	ft_alloc(t_all *data)
{
	data->filter = 0;
	data->ren = 0;
	data->aalias = 0;
	data->deep = 0;
	data->screen_pixels = (t_vect *)malloc((WIN_W * WIN_H) * sizeof(t_vect));
	data->camera = (t_data_camera *)malloc(sizeof(t_data_camera));
	ft_alloc_obj(&data->obj);
	ft_alloc_light(&data->light);
}

int	inside_rect(t_all *data, SDL_Rect r)
{
	if (data->event.x >= r.x && data->event.x <= r.x + r.w && data->event.y
		>= r.y && data->event.y <= r.y + r.h)
		return (1);
	return (0);
}

void	menu(t_all *data)
{
	SDL_SetRenderDrawColor(data->rend, 0, 0, 0, 255);
	event_alias(data);
	event_filter(data);
	event_focus(data);
	event_go(data);
	data->event.x = 0;
	data->event.y = 0;
}

void	threading(t_all alll)
{
	pthread_t	thread_id[4];
	t_all		data[4];
	int			i;
	t_all		*all;

	all = &alll;
	i = 0;
	if (alll.ren == 0)
		menu(&alll);
	if (alll.ren == 1)
	{
		while (i < 4)
		{
			all->start = WIN_W / 4 * i;
			all->end = WIN_H / 4 * i + (WIN_H / 4);
			ft_memcpy((void *)&data[i], (void *)all, sizeof(t_all));
			pthread_create(&thread_id[i], NULL, raytracing, &data[i]);
			pthread_join(thread_id[i], NULL);
			i++;
		}
	}
	loop_program(&alll);
}

int	main(int ac, char **av)
{
	t_all	data;

	if (ac == 2)
	{
		ft_alloc(&data);
		if (file_checker(av[1], &data) == -1)
		{
			ft_putendl("error file");
			return (0);
		}
		init_sdl(&data);
		threading(data);
	}
	else
		ft_putendl("Usage : ./RT <...> ");
	return (0);
}
