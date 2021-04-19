#include "../header/rt.h"

t_vect  distrupt_a_sphere(t_obj *obj, t_vect col)
{
	t_vect	center_to_hit;
	double	hit_to_axis;
	double	center_to_hit_len;

	center_to_hit = sub_vect(obj->hit, (t_vect){0, 0, 1000});
	center_to_hit_len = sqrt(center_to_hit.x * center_to_hit.x
			+ center_to_hit.y * center_to_hit.y
			+ center_to_hit.z * center_to_hit.z);
	if ((int)center_to_hit_len % 2)
		col = (t_vect){255, 0, 0};
	else
		col = (t_vect){255, 255, 255};
	return (col);
}

t_vect	distrupt_a_sphere_color(t_obj *obj, t_vect col)
{
	col = (t_vect){255, 255, 255};
	col.x *= 1 - fabs(2 * (obj->hit.x - floor(obj->hit.x) - 1));
	col.x = fabs(col.x);
	col.y *= 1 - fabs(2 * (obj->hit.y - floor(obj->hit.y) - 1));
	col.y = fabs(col.y);
	col.z *= 1 - fabs(2 * (obj->hit.z - floor(obj->hit.z) - 1));
	col.z = fabs(col.z);
	return (col);
}

static t_vect	sol(t_vect template, double res, double res2, double res3)
{
	u_vect	sort;
	t_vect	applied;
	t_vect	usable_res;
	int		check;

	check = 0;
	applied = (t_vect){0, 0, 0};
	sort.order = applied;
	sort.tab[(int)template.x - 1] = 1;
	sort.tab[(int)template.y - 1] = 1;
	applied = sort.order;
	if (applied.x == 1)
		usable_res.x = res;
	if (applied.x == 1)
		check = 1;
	if (applied.y == 1 && check == 0)
		usable_res.x = res2;
	else
		usable_res.y = res2;
	if (applied.z == 1)
		usable_res.y = res3;
	return (usable_res);
}

static t_vect	possible_results(t_obj *obj)
{
	t_vect	res;

	if (obj->hit.x < 0)
		res.x = ((int)obj->hit.x - 1) % 2;
	else
		res.x = ((int)obj->hit.x) % 2;
	if (obj->hit.y < 0)
		res.y = ((int)obj->hit.y - 1) % 2;
	else
		res.y = ((int)obj->hit.y) % 2;
	if (obj->hit.z < 0)
		res.z = ((int)obj->hit.z - 1) % 2;
	else
		res.z = ((int)obj->hit.z) % 2;
	return (res);
}

t_vect			disruption(t_obj *obj, t_vect col)
{
	t_vect	res;
	t_vect	vec;
	t_vect	usable_res;

	if (obj->disruption == 1)
	{
		vec = sorting(obj->norm);
		res = possible_results(obj);
		usable_res = sol(vec, res.x, res.y, res.z);
		if ((usable_res.x && usable_res.y) || (!usable_res.x && !usable_res.y))
			col = (t_vect){0, 0, 0};
		else
			col = (t_vect){255, 255, 255};
	}
	if (obj->disruption == 2)
		col = distrupt_a_sphere(obj, col);
	if (obj->disruption == 3)
		col = distrupt_a_sphere_color(obj, col);
	return (col);
}