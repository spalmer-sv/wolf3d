/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:36:41 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/31 20:28:41 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_move2(t_man *man, t_win *win, SDL_Event *event, char **ar)
{
	//if (event->key.keysym.sym == SDLK_a)
	if (event->key.keysym.sym == 97 || event->key.keysym.sym == 1092)
	{
		if (ar[(int)(man->y + sin(man->pov - M_PI / 2) * 0.3)][(int)(man->x +
			cos(man->pov - M_PI / 2) * 0.3)] != '1' &&
			ar[(int)(man->y + sin(man->pov - M_PI / 2) * 0.3)][(int)(man->x +
			cos(man->pov - M_PI / 2) * 0.3)] != 'P')
		{
			man->x += (cos(man->pov - M_PI / 2) * 0.1);
			man->y += (sin(man->pov - M_PI / 2) * 0.1);
		}
	}
	//if (event->key.keysym.sym == SDLK_d)
	if (event->key.keysym.sym == 100 || event->key.keysym.sym == 1074)
	{
		if (ar[(int)(man->y + sin(man->pov + M_PI / 2) * 0.3)][(int)(man->x +
			cos(man->pov + M_PI / 2) * 0.3)] != '1' &&
			ar[(int)(man->y + sin(man->pov + M_PI / 2) * 0.3)][(int)(man->x +
			cos(man->pov + M_PI / 2) * 0.3)] != 'P')
		{
			man->x += (cos(man->pov + M_PI / 2) * 0.1);
			man->y += (sin(man->pov + M_PI / 2) * 0.1);
		}
	}
}

void	check_move(t_man *man, t_win *win, SDL_Event *event, char **ar)
{
//	if (event->key.keysym.sym == SDLK_w)
	if (event->key.keysym.sym == 119 || event->key.keysym.sym == 1094)
	{
		if (ar[(int)(man->y + sin(man->pov) * 0.3)][(int)(man->x +
			cos(man->pov) * 0.3)] != '1' &&
			ar[(int)(man->y + sin(man->pov) * 0.3)][(int)(man->x +
			cos(man->pov) * 0.3)] != 'P')
		{
			man->y += (sin(man->pov) * 0.1);
			man->x += (cos(man->pov) * 0.1);
		}
	}
	//if (event->key.keysym.sym == SDLK_s)
	if (event->key.keysym.sym == 115 || event->key.keysym.sym == 1099)
	{
		if (ar[(int)(man->y - sin(man->pov) * 0.3)][(int)(man->x -
			cos(man->pov) * 0.3)] != '1' &&
			ar[(int)(man->y - sin(man->pov) * 0.3)][(int)(man->x -
			cos(man->pov) * 0.3)] != 'P')
		{
			man->y -= (sin(man->pov) * 0.1);
			man->x -= (cos(man->pov) * 0.1);
		}
	}
}

void	check_rotate(t_man *man, t_win *win, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_LEFT)
	{
		man->pov -= 0.05;
		if (man->pov <= 0)
			man->pov += (2 * M_PI);
	}
	if (event->key.keysym.sym == SDLK_RIGHT)
	{
		man->pov += 0.05;
		if (man->pov >= 2 * M_PI)
			man->pov -= (2 * M_PI);
	}
}
