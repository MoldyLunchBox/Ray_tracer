#include "../header/rt.h"

void		case_one(t_4vects *slicers, int *first_two, int the_case)
{
	slicers->one = (t_vect){1, 0, 0};
	slicers->two = (t_vect){-1, 0, 0};
	*first_two = 1;
}

void		case_two(t_4vects *slicers, int *first_two, int the_case)
{
	if (!*first_two)
	{
		slicers->one = (t_vect){0, 1, 0};
		slicers->two = (t_vect){0, -1, 0};
		*first_two = 1;
	}
	else
	{
		slicers->three = (t_vect){0, 1, 0};
		slicers->four = (t_vect){0, -1, 0};
	}
	
}

void		fill_vects(t_4vects *slicers, int *first_two, int the_case)
{
	if (the_case == 1)
		case_one(slicers, first_two, the_case);
	if (the_case == 2)
		case_two(slicers, first_two, the_case);
	if (the_case == 3)
	{
		slicers->three = (t_vect){0, 0, 1};
		slicers->four = (t_vect){0, 0, -1};
	}

}

t_4vects	slicer_maker(t_vect template)
{
	t_4vects	slicers;
	int			first_two;
	u_vect		sort;
	t_vect		order = (t_vect){0,0,0};

	sort.order = order;
	sort.tab[(int)template.x-1] = 1;
	sort.tab[(int)template.y-1] = 1;
	first_two = 0;
	template = sort.order;
	if (template.x == 1)
		fill_vects(&slicers, &first_two, 1);
	if (template.y == 1)
		fill_vects(&slicers, &first_two, 2);
	if (template.z == 1)
		fill_vects(&slicers, &first_two, 3);
	return(slicers);
}
int		slice_it(t_obj *plane, t_ray ray, double size, t_4vects slicers)
{
	t_vect	hit_to_pos;
	t_vect	slice_pos = add_vect(plane->position, vect_mult_val(slicers.one, size));
	
	hit_to_pos = sub_vect(slice_pos, plane->hit);

	if (vect_scal(hit_to_pos, slicers.one) < 0)
		return (0);
	if (vect_scal(sub_vect(add_vect(plane->position, vect_mult_val(slicers.two, size)), plane->hit), slicers.two) < 0)
		return (0);
	if (vect_scal(sub_vect(add_vect(plane->position, vect_mult_val(slicers.three, size)), plane->hit), slicers.three) < 0)
		return (0);
	if (vect_scal(sub_vect(add_vect(plane->position, vect_mult_val(slicers.four, size)), plane->hit), slicers.four) < 0)
		return (0);
	return (1);
}
t_sol		slice_it_four_times(t_obj *plane, t_ray ray, double size)
{
    t_vect		template;
    t_4vects	slicers;
	t_sol		sol;

	template = sorting(plane->direction);
	slicers = slicer_maker(template);
	sol = intersection_ray_plan(plane, ray);
	if( sol.tmin != -1 && !slice_it(plane, ray, size, slicers))
		sol.tmin = -1;
	return (sol);
}

t_obj	box_sides(t_vect plane_direction, t_obj *box, t_ray ray)
{
	t_vect	plane_position;
	t_obj	plane;

	plane_position = add_vect(vect_mult_val(plane_direction, box->size), box->position);
    plane.direction = plane_direction;
    plane.position = plane_position;
	plane.color = (t_vect){255,0,0};
	plane.slice = (t_vect){0,0,0};
	plane.sol = slice_it_four_times(&plane, ray, box->size);
	return (plane);
}
void	init_box(t_obj plane, t_obj *box, t_sol *closest)
{
	box->direction = plane.direction;
	box->hit = plane.hit;
	box->norm = plane.norm;
	box->t = plane.t;
	closest->tmin = plane.sol.tmin;
}
t_sol intersection_box(t_obj *box, t_ray ray)
{
    t_obj plane;
    t_sol closest;

	closest.tmin = -1;
    plane = box_sides((t_vect){0,1,0}, box, ray);
	if (closest.tmin == -1 || closest.tmin > plane.sol.tmin)
		init_box(plane, box, &closest);
	plane = box_sides((t_vect){0,-1,0}, box, ray);
	if (closest.tmin == -1 || (closest.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &closest);
	plane = box_sides((t_vect){1,0,0}, box, ray);
	if (closest.tmin == -1 || (closest.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &closest);
	plane = box_sides((t_vect){-1,0,0}, box, ray);
	if (closest.tmin == -1 || (closest.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &closest);
	plane = box_sides((t_vect){0,0,-1}, box, ray);
	if (closest.tmin == -1 || (closest.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &closest);
	plane = box_sides((t_vect){0,0,1}, box, ray);
	if (closest.tmin == -1 || (closest.tmin > plane.sol.tmin && plane.sol.tmin != -1))
		init_box(plane, box, &closest);
    return(closest);
}

