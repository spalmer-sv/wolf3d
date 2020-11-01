/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:25:21 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/24 22:43:19 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

float	check_angle(t_man *man)
{
	float angle;

	angle = man->angle;
	if (angle <= 0)
		angle += (2 * M_PI);
	if (angle >= 2 * M_PI)
		angle -= (2 * M_PI);
	return (angle);
}

void	init_hor(t_man *man)
{
	if (man->horcast.angle >= M_PI)
	{
		man->horcast.step_x = 1 / tan(man->horcast.angle) * -1;
		man->horcast.ay = (int)man->y - 0.00001;
		man->horcast.step_y = -1;
		man->horcast.ax = man->x + (man->y - man->horcast.ay) /
		tan(man->horcast.angle) * -1;
	}
	else
	{
		man->horcast.step_x = 1 / tan(man->horcast.angle);
		man->horcast.ay = (int)man->y + 1;
		man->horcast.step_y = 1;
		man->horcast.ax = man->x + (man->y - man->horcast.ay) /
		tan(man->horcast.angle) * -1;
	}
}

float	find_hor_line(t_man *man, char **ar, t_win *win)
{
	man->horcast.angle = check_angle(man);
	init_hor(man);
	while (1)
	{
		if ((int)man->horcast.ay >= win->hei || (int)man->horcast.ay < 0 ||
			(int)man->horcast.ax >= win->wid || (int)man->horcast.ax < 0)
			return (INFINITY);
		if (ar[(int)man->horcast.ay][(int)man->horcast.ax] == '1' ||
			ar[(int)man->horcast.ay][(int)man->horcast.ax] == 'P')
		{
			man->xhor_fin = man->horcast.ax;
			return (fabs((man->horcast.ax - man->x) / cos(man->angle)));
		}
		else
		{
			man->horcast.ax += man->horcast.step_x;
			man->horcast.ay += man->horcast.step_y;
		}
	}
}

void	init_ver(t_man *man)
{
	if (man->vercast.angle <= M_PI_2 || man->vercast.angle >= 3 * M_PI_2)
	{
		man->vercast.bx = (int)man->x + 1;
		man->vercast.step_x = 1;
		man->vercast.step_y = tan(man->vercast.angle);
		man->vercast.by = man->y + (man->vercast.bx - man->x) *
		tan(man->vercast.angle);
	}
	else
	{
		man->vercast.bx = (int)man->x - 0.00001;
		man->vercast.step_x = -1;
		man->vercast.step_y = tan(man->vercast.angle) * -1;
		man->vercast.by = man->y + (man->x - man->vercast.bx) *
		tan(man->vercast.angle) * -1;
	}
}

float	find_ver_line(t_man *man, char **ar, t_win *win)
{
	man->vercast.angle = check_angle(man);
	init_ver(man);
	while (1)
	{
		if ((int)man->vercast.by >= win->hei || (int)man->vercast.by < 0 ||
			(int)man->vercast.bx >= win->wid || (int)man->vercast.bx < 0)
			return (INFINITY);
		if (ar[(int)man->vercast.by][(int)man->vercast.bx] == '1' ||
			ar[(int)man->vercast.by][(int)man->vercast.bx] == 'P')
		{
			man->yvert_fin = man->vercast.by;
			return (fabs((man->vercast.bx - man->x) / cos(man->angle)));
		}
		else
		{
			man->vercast.bx += man->vercast.step_x;
			man->vercast.by += man->vercast.step_y;
		}
	}
}
