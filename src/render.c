/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:52:43 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/25 15:21:36 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*choose_surface(t_texture *img, t_man *man)
{
	SDL_Surface *surface;

	if (man->flag_side == 1)
		surface = img->west_srf;
	if (man->flag_side == 2)
		surface = img->north_srf;
	if (man->flag_side == 3)
		surface = img->east_srf;
	if (man->flag_side == 4)
		surface = img->south_srf;
	if (man->flag_side == 5)
		surface = img->picture;
	man->flag_side = 0;
	return (surface);
}

Uint32		getcolor(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;
	Uint32	color;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x *
	surface->format->BytesPerPixel;
	color = p[2] << 16 | p[1] << 8 | p[0];
	return (color);
}

float		find_x(t_render *render, int i, t_man *man)
{
	float fin;
	float res;

	if (man->hor > man->ver)
		fin = man->yvert_fin;
	else
		fin = man->xhor_fin;
	res = fin - (int)fin;
	return (res * 64);
}

void		render_skybox(t_texture *img, t_render *render, int j, t_man *man)
{
	Uint32	color;
	float	x;
	float	y;

	x = man->angle * 180 * 4 / M_PI;
	y = 64 * j / HEI * 6;
	color = getcolor(img->sky_srf, x, y);
	render->temp_srf[(int)(WID * j + render->x)] = color;
}

void		render_textures(t_win *win, t_texture *img, t_render *render,
			t_man *man)
{
	int			j;
	SDL_Surface	*surface;
	float		x;
	Uint32		color;

	j = 0;
	surface = choose_surface(img, man);
	while (j < HEI)
	{
		if (j >= render->begin && j < (render->begin + render->height))
		{
			x = find_x(render, (j - render->begin) / render->height * 64, man);
			color = getcolor(surface, x, (j - render->begin) /
			render->height * 64);
			render->temp_srf[(int)(WID * j + render->x)] = color;
		}
		else if (j < render->begin)
			render_skybox(img, render, j, man);
		else
			render->temp_srf[(int)(WID * j + render->x)] = 0x44444444;
		j++;
	}
}
