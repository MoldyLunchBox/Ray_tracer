
#include "../header/rt.h"

void	ft_alloc_light(t_data_light **light)
{
	(*light) = (t_data_light *)malloc(sizeof(t_data_light));
	init_vect(&(*light)->position, 0, 0, 0);
	init_vect(&(*light)->direction, 0, 0, 0);
	init_vect(&(*light)->color, 0, 0, 0);
	(*light)->intensity = 0;
	(*light)->type = 0;
	(*light)->angle = 0;
	(*light)->ambient = 0;
	(*light)->next = NULL;
}

void	ft_alloc_camera(t_data_camera **camera)
{
	(*camera) = (t_data_camera *)malloc(sizeof(t_data_camera));
	init_vect(&(*camera)->pos, 0, 0, 0);
	init_vect(&(*camera)->dir, 0, 0, 0);
	init_vect(&(*camera)->u_dir, 0, 0, 0);
	init_vect(&(*camera)->v_dir, 0, 0, 0);
	(*camera)->dist = 0;
	(*camera)->focus_dis = 0;
}

void	ft_lstdel(t_obj **alst)
{
	t_obj	*temp;

	if (!alst)
		return ;
	while (*alst)
	{
		temp = (*alst)->next;
		free(*alst);
		*alst = temp;
	}
	*alst = NULL;
	return ;
}

void	ft_free_obj(t_all *data)
{
	while (data->light)
	{
		free(data->light);
		data->light = data->light->next;
	}
	free(data->camera);
	ft_lstdel(&data->obj);
}
