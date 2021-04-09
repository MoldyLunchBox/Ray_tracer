/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:54:18 by amya              #+#    #+#             */
/*   Updated: 2021/03/28 18:50:14 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_2d_i		get_uv(t_obj *obj, t_2d_i size)
{
	t_2d_i	uv;

	if (ft_strcmp(obj->name, "sphere") == 0)
		uv = sphere_uv(obj, size);
	if (ft_strcmp(obj->name, "cylinder") == 0)
		uv = uv_mapping_cyl_cone(obj, size);
	if (ft_strcmp(obj->name, "cone") == 0)
		uv = uv_mapping_cyl_cone(obj, size);
	if (ft_strcmp(obj->name, "plane") == 0)
		uv = plane_uv(obj, size);
	return (uv);
}

int			init_bpp(unsigned char **pos, int bpp, t_obj *obj)
{
	t_2d_i size;
	t_2d_i tex;

	bpp = obj->surface->format->BytesPerPixel;
	size.x = obj->surface->w;
	size.y = obj->surface->h;
	tex = get_uv(obj, size);
	*pos = (unsigned char *)obj->surface->pixels + ((int)(tex.y +
	obj->text_modif.y) * obj->surface->pitch + (int)(tex.x +
	obj->text_modif.x) * bpp);
	return (bpp);
}

void		texturing(t_obj *obj)
{
	int					bpp;
	int					pix;
	SDL_Color			rgb;
	unsigned char		*pos;

	bpp = init_bpp(&pos, bpp, obj);
	if (bpp == 1)
		pix = *pos;
	else if (bpp == 2)
		pix = *(unsigned short *)pos;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pix = pos[0] << 16 | pos[1] << 8 | pos[2];
		else
			pix = pos[0] | pos[1] << 8 | pos[2] << 16;
	}
	else if (bpp == 4)
		pix = *(unsigned int *)pos;
	else
		pix = -1;
	SDL_GetRGB(pix, obj->surface->format, &rgb.r, &rgb.g, &rgb.b);
	obj->color.x = rgb.r;
	obj->color.y = rgb.g;
	obj->color.z = rgb.b;
}
