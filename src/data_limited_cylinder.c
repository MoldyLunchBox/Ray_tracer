#include "../header/rt.h"

void		f_limited_cylinder2(char **str, int j, t_obj *cylinder)
{
	if (j == 6)
		init_vect(&cylinder->color, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 7)
		cylinder->radius = ft_atof(str[0]);
	if (j == 8)
		cylinder->size = ft_atof(str[0]);
	if (j == 9)
		cylinder->type = ft_atof(str[0]);
	if (j == 10)
		cylinder->trans = ft_atof(str[0]);
	if (j == 11)
		cylinder->refl = ft_atof(str[0]);
	if (j == 12)
		cylinder->disruption = ft_atof(str[0]);
	cylinder->is_negative = 0;
}

void		f_limited_cylinder(char **str, int j, t_obj *cylinder)
{
	if (j == -1)
		init_vect(&cylinder->text_modif, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 0)
		init_vect(&cylinder->position, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&cylinder->direction, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&cylinder->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&cylinder->rotation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&cylinder->slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		init_vect(&cylinder->pos_slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	f_cylinder2(str, j, cylinder);
}

int			s_limited_cylinder(char **table, int i, t_all *data, t_obj *cyl)
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
		return(-1);
	cyl->texture = ft_strdup(white_split[1]);
	free_2d(&white_split);
	while (table[++i] && j < 12)
	{
		if (!checker_loop(&str, table[i], j))
			return (-1);
		f_cylinder(str, j, cyl);
		j++;
	}
	data->id++;
	cyl->id = data->id;
	if (ft_strcmp(cyl->texture, ".") != 0)
		if (!(cyl->surface = IMG_Load(cyl->texture)))
			sdl_error("can't load surface");
	if (ft_strcmp(cyl->texture, ".") == 0)
		cyl->direction = rot_vect_xyz(cyl->direction, cyl->rotation);
	cyl->position = trans_vect_xyz(cyl->position, cyl->translation);
	cyl->inter = &intersection_ray_cylindre;
	cyl->half_size = cyl->size / 2;
	return (0);
}
