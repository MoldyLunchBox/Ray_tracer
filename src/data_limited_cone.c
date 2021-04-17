#include "../header/rt.h"

void	f_limited_cone2(char **str, int j, t_obj *cone)
{
	if (j == 6)
		init_vect(&cone->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 7)
		cone->radius = ft_atof(str[0]);
	if (j == 8)
		cone->size = ft_atof(str[0]);
	if (j == 9)
		cone->type = ft_atof(str[0]);
	if (j == 10)
		cone->trans = ft_atof(str[0]);
	if (j == 11)
		cone->refl = ft_atof(str[0]);
	if (j == 12)
		cone->disruption = ft_atof(str[0]);
	if (j == 13)
		cone->length = ft_atof(str[0]);
	cone->is_negative = 0;
}

void	f_limited_cone(char **str, int j, t_obj *cone)
{
	if (j == -1)
		init_vect(&cone->text_modif, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 0)
		init_vect(&cone->position, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&cone->direction, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&cone->translation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&cone->rotation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&cone->slice, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		init_vect(&cone->pos_slice, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	f_limited_cone2(str, j, cone);
}

static void	load_texture(t_all *data, t_obj *cyl)
{
	data->id++;
	cyl->id = data->id;
	if (ft_strcmp(cyl->texture, ".") != 0)
	{
		cyl->surface = IMG_Load(cyl->texture);
		if (!cyl->surface)
			sdl_error("can't load surface");
	}
	if (ft_strcmp(cyl->texture, ".") == 0)
		cyl->direction = rot_vect_xyz(cyl->direction, cyl->rotation);
	cyl->position = trans_vect_xyz(cyl->position, cyl->translation);
	cyl->inter = &intersection_ray_limited_cone;
}

int	s_limited_cone(char **table, int i, t_all *data, t_obj *cyl)
{
	int		j;
	char	**str;
	char	**white_split;

	j = -1;
	cyl->name = ft_strsub(table[i - 1], 0, ft_strlen(table[i - 1]) - 1);
	if (!space_counter(table[i]))
		return (-1);
	white_split = ft_strsplit(table[i], ' ');
	if (!white_split_check(white_split))
		return (-1);
	cyl->texture = ft_strdup(white_split[1]);
	free_2d(&white_split);
	while (table[++i] && j < 14)
	{
		if (!checker_loop(&str, table[i], j, 7))
			return (-1);
		f_limited_cone(str, j, cyl);
		j++;
	}
	load_texture(data, cyl);
	return (0);
}
