
#include "../header/rt.h"

void	f_box(char **str, int j, t_obj *cube)
{
	if (j == -1)
		init_vect(&cube->position, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&cube->translation, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 6)
		init_vect(&cube->color, ft_atof(str[0]),
			ft_atof(str[1]), ft_atof(str[2]));
	if (j == 8)
		cube->size = ft_atof(str[0]);
	if (j == 9)
		cube->type = ft_atof(str[0]);
	if (j == 10)
		cube->trans = ft_atof(str[0]);
	if (j == 11)
		cube->refl = ft_atof(str[0]);
	cube->is_negative = 0;
	cube->disruption = 0;
}



int	s_box(char **table, int i, t_all *data, t_obj *box)
{
	int		j;
	char	**str;
	char	**white_split;

	j = 0;
	box->name = ft_strsub(table[i - 1], 0, ft_strlen(table[i - 1]) - 1);
	if (!space_counter(table[i]))
		return (-1);
	while (table[i] && j < 4)
	{
		if (!checker_loop(&str, table[i], j, 3))
			return (-1);
		f_box(str, j, box);
		j++;
		i++;
	}
	data->id++;
	box->id = data->id;
	box->inter = &intersection_box;
	return (0);
}
