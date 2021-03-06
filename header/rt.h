/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:55:27 by amya              #+#    #+#             */
/*   Updated: 2021/04/26 11:23:08 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIN_W       1200
# define WIN_H       1200
# define NBR_RAYS    40
# define PI          3.14159265359
# include "vector.h"
# include <pthread.h>
# include "ray.h"
# include "data.h"
# include "../libft/libft.h"
# include <stdio.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "vector.h"
# include <math.h>

int			s_box(char **table, int i, t_all *data, t_obj *box);
void		threading(t_all alll);
void		cartoon_filter(t_all *rt);
void		ft_filter_mb(t_all *rt);
void		sepia_filtre(t_all *rt);
void		filtre(t_all *rt);
int			light_direct(t_all data, t_ray ray);
t_vect		ft_refraction(t_obj *pos, t_all data, t_ray ray, int nbrbonds);
t_vect		ft_reflection(t_obj *pos, t_all data, t_ray ray, int nbrbonds);
t_vect		rend_pix(t_all data, t_ray ray, int nbrbonds);
int			ft_val(char *str);
int			ft_val2(char *str);
int			ft_camera(char **table, t_all *data);
int			ft_obj(char **table, t_all *data);
int			check_str2(char **str);
int			f_str(char **str, int j, int k);
int			check_str1(char **str, int j, int k);
int			f_str2(char **str, int j, int d);
int			ft_cylinder(char **table, t_all *data);
int			ft_light(char **table, t_all *data);
int			file_checker(char *str, t_all *data);
int			s_sphere(char **table, int i, t_all *data, t_obj *sphere);
int			s_plane(char **table, int i, t_all *data, t_obj *plane);
int			s_cone(char **table, int i, t_all *data, t_obj *cone);
int			s_ring(char **table, int i, t_all *data, t_obj *ring);
int			s_cylinder(char **table, int i, t_all *data, t_obj *cyl);
int			s_triangle(char **table, int i, t_all *data, t_obj *tri);
int			s_paraploid(char **table, int i, t_obj *par);
int			s_ellipsoid(char **table, int i, t_obj *el);
int			s_cube(char **table, int i, t_all *data, t_obj *cube);
void		loop_program(t_all *data);
void		init_sdl(t_all *data);
void		del_list(t_obj **alst);
void		sdl_error(char *message);
void		ft_alloc_light(t_data_light **light);
void		ft_alloc_obj(t_obj **obj);
void		*raytracing(void *data);
void		ft_free_obj(t_all *data);
void		init_li(t_light *li, t_data_light *ligth, t_obj *obj, t_ray ray, t_all data);
t_vect		light_obj(t_obj *obj, t_all data, t_ray ray);
t_vect		on_shadow(t_obj *pos, t_all data, t_vect col);
t_ray		init_rayy(int i, int j, t_data_camera *cam);
double		find_obj_scnd(t_all data, t_ray to_light, t_obj *pos, double *val);
double		ft_atof(char *str);
void		texturing(t_obj *obj);
t_sol		find_solution(double delta, t_vect abc);
t_sol		intersection_ray_sphere(t_obj *obj, t_ray r);
t_sol		intersection_ray_ring(t_obj *obj, t_ray r);
t_sol		intersection_ray_plan(t_obj *obj, t_ray r);
t_sol		intersection_ray_cylindre(t_obj *obj, t_ray r);
t_sol		intersection_ray_cone(t_obj *cone, t_ray r);
t_sol		intersection_ray_geometry(t_obj *gem, t_ray r);
t_sol		intersection_paraploid(t_obj *para, t_ray r);
t_sol		intersection_ellipsoid(t_obj *eli, t_ray r);
t_sol		intersection_cube(t_obj *box, t_ray r);
double		get_length(t_vect u);
t_vect		safe_color(t_vect p);
int			inside_rect(t_all *data, SDL_Rect r);
void		init_2d_vect(t_2d_d *v);
t_2d_i		plane_uv(t_obj *obj, t_2d_i size);
t_uv		sphere_uv(t_obj *obj, t_2d_i size);
t_uv		uv_mapping_cyl_cone(t_obj *obj, t_2d_i size);
void		sdl_set_text(char *txt, t_vect_i col, t_4d_i rect, t_all *data);
t_ray		new_ray(int i, int j, t_all data);
void		event_filter(t_all *data);
void		cone_norm(t_obj *cone, t_ray r, double t);
int			space_counter(char *str);
void		free_2d(char ***str);
int			white_split_check(char **str);
int			info_checker(char **str);
int			checker_loop(char ***str, char *table, int j, int max_vects);
void		f_limited_cylinder2(char **str, int j, t_obj *cylinder);
void		f_limited_cylinder(char **str, int j, t_obj *cylinder);
int			s_limited_cylinder(char **table, int i, t_all *data, t_obj *cyl);
t_sol		intersection_ray_limited_cylindre(t_obj *cyl, t_ray r);
t_sol		intersection_box(t_obj *box, t_ray ray);
t_vect		norm_cube(t_obj *box, t_vect hit_point);
t_vect		sorting(t_vect in);
int			space_counter(char *str);
int			ft_lines_in_file(char *str);
void		set_camera_dir(t_data_camera *camera);
void		event_start(t_all *data);
int			s_limited_cone(char **table, int i, t_all *data, t_obj *cyl);
t_sol		intersection_ray_limited_cone(t_obj *cone, t_ray r);
int			slice_it(t_obj *plane, double size, t_4vects slicers);
t_4vects	slicer_maker(t_vect template);
void		fill_vects(t_4vects *slicers, int *first_two, int the_case);
void		case_two(t_4vects *slicers, int *first_two);
void		case_one(t_4vects *slicers, int *first_two);
void		event_orbiter(t_all *data);
int			inside_left_arrow(t_all *data);
int			inside_right_arrow(t_all *data);
void		event_orbiter(t_all *data);
int			inside_filter(t_all *data);
void		orbiter(t_all *data);
int			ft_objects_rest(t_all *data, int i, char **table, t_obj **obj);
int			is_object(char *str);
t_sol		bottom_cap(t_obj *cyl, t_vect bottom, t_ray r, t_sol sol);
t_sol		top_cap(t_obj *cyl, t_vect top, t_ray r, t_sol sol);
t_sol		limited_object(t_obj *cyl, t_ray r, t_sol sol, t_vect top);
t_vect		light_is_behind(t_vect cam_to_light, t_all data,
				double cam_light, t_data_light *light);
t_vect		direct_light(t_ray ray, t_all data, t_data_light *light);
t_obj		*find_closest(t_all data, t_ray ray);
t_sol		out_of_range(double result_top, double result_bottom, t_sol sol);
t_sol		top_cap_cone(t_cone_top var, t_obj *cone, t_sol sol);
t_sol		cone_top(t_obj *cone, t_ray r, t_sol sol, t_vect top);
t_sol		bottom_cap_cone(t_cone_bottom var, t_obj *cone, t_sol sol);
t_sol		cone_bottom(t_obj *cone, t_ray r, t_sol sol, t_vect bottom);
t_sol		limited_object_cone(t_obj *cone, t_ray r, t_sol sol);
double		if_t1_isnull(double t1, t_sol t);
double		if_t1_isbigger(double t1, t_sol t);
t_sol		look_for_negative(t_obj *obj, t_all data, t_sol t, t_ray ray);
void		init_sol(t_sol *t);
t_vect		sorting(t_vect in);
t_sol		cyl_inter_negative(t_sol t,
				t_obj *header, t_all data, t_ray hit_to_light);
t_vect		disruption(t_obj *obj, t_vect col);
t_vect		filter(t_all *data, t_vect col, t_vect_i var);
t_obj		*find_closest(t_all data, t_ray ray);
void		set_pixel(t_all data, t_vect col, t_vect_i var);
t_vect		light_n_shadow(t_obj *obj, t_all data, t_ray ray, t_vect col);
t_vect		loop_direct_light(t_ray ray, t_all data, t_data_light *light);
void		bad_file(void);
t_2d_d	shadow(t_obj *pos, t_data_light *light, double t1);
#endif
