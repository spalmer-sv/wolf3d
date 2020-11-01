/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 14:20:43 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/24 22:32:16 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_side(t_man *man, char **ar)
{
	if (man->flag_side != 5)
	{
		if (man->hor > man->ver)
		{
			if (man->angle <= M_PI_2 || man->angle >= 3 * M_PI_2)
				man->flag_side = 3;
			else
				man->flag_side = 1;
		}
		else
		{
			if (man->angle <= M_PI)
				man->flag_side = 2;
			else
				man->flag_side = 4;
		}
	}
}

void	build_labirint(t_all *wolf, int x, char **ar)
{
	float		len;
	float		wall;
	SDL_Rect	rect_wall;
	float		begin;

	if (wolf->man.hor > wolf->man.ver)
	{
		len = wolf->man.ver;
		if (ar[(int)wolf->man.vercast.by][(int)wolf->man.vercast.bx] == 'P')
			wolf->man.flag_side = 5;
	}
	else
	{
		len = wolf->man.hor;
		if (ar[(int)wolf->man.horcast.ay][(int)wolf->man.horcast.ax] == 'P')
			wolf->man.flag_side = 5;
	}
	check_side(&wolf->man, ar);
	wolf->render.height = HEI / (len * cos(wolf->man.angle - wolf->man.pov));
	wolf->render.x = x;
	wolf->render.begin = HEI / 2 - wolf->render.height / 2;
	render_textures(&wolf->win, &wolf->img, &wolf->render, &wolf->man);
}

void	draw_line_view(t_all *wolf, char **ar)
{
	float	iter;
	int		i;

	i = 0;
	wolf->man.angle = wolf->man.pov;
	iter = wolf->man.fov / WID;
	wolf->man.angle = wolf->man.pov - wolf->man.fov / 2;
	while (i < WID)
	{
		if (wolf->man.angle <= 0)
			wolf->man.angle += (2 * M_PI);
		if (wolf->man.angle >= 2 * M_PI)
			wolf->man.angle -= (2 * M_PI);
		wolf->man.hor = find_hor_line(&wolf->man, ar, &wolf->win);
		wolf->man.ver = find_ver_line(&wolf->man, ar, &wolf->win);
		build_labirint(wolf, i, ar);
		wolf->man.angle += iter;
		i++;
	}
}

void	init_man(t_man *man, char **ar)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ar[i])
	{
		while (ar[i][j] != '\0')
		{
			if (ar[i][j] == 'W')
			{
				man->x = j + 0.5;
				man->y = i + 0.5;
			}
			j++;
		}
		j = 0;
		i++;
	}
	man->fov = 1.0472;
	man->pov = 3 * M_PI_2;
}
