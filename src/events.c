/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 22:41:56 by spalmer           #+#    #+#             */
/*   Updated: 2020/11/01 15:25:14 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	choose_weapon(SDL_Event *event, t_texture *img)
{
	if (event->key.keysym.sym == SDLK_1)
		img->gun = img->hand1;
	else if (event->key.keysym.sym == SDLK_2)
		img->gun = img->hand2;
	else if (event->key.keysym.sym == SDLK_3)
		img->gun = img->hand3;
}

void	draw(t_all *wolf, char **ar, SDL_Texture *res, SDL_Rect gun)
{
	if (SDL_RenderClear(wolf->win.render))
		error(SDL_GetError(), 0);
	draw_line_view(wolf, ar);
	if (SDL_UpdateTexture(res, NULL, wolf->render.temp_srf,
		sizeof(Uint32) * WID))
		error(SDL_GetError(), 0);
	if (SDL_RenderCopy(wolf->win.render, res, NULL, NULL))
		error(SDL_GetError(), 0);
	if (SDL_RenderCopy(wolf->win.render, wolf->img.gun, NULL, &gun))
		error(SDL_GetError(), 0);
	SDL_RenderPresent(wolf->win.render);
}

void	check_botton(SDL_Event *event, t_all *wolf, char **ar, int *quit)
{
	check_move(&wolf->man, &wolf->win, event, ar);
	check_move2(&wolf->man, &wolf->win, event, ar);
	check_rotate(&wolf->man, &wolf->win, event);
	choose_weapon(event, &wolf->img);
	// printf("x = %x\n", event->key.keysym.sym);
	// printf("i = %i\n", event->key.keysym.sym);
	if (event->key.keysym.sym == SDLK_ESCAPE)
		*quit = 1;
}

void	check_event(t_all *wolf, char **ar)
{
	SDL_Event	event;
	int			quit;
	SDL_Texture	*res;
	SDL_Rect	gun;

	quit = 0;
	if (!(res = SDL_CreateTexture(wolf->win.render, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STATIC, WID, HEI)))
		error(SDL_GetError(), 0);
	gun = init_rect(WID / 2 - 64, HEI - 128, 128, 128);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = 1;
				break ;
			}
			if (event.type == SDL_KEYDOWN)
				check_botton(&event, wolf, ar, &quit);
			draw(wolf, ar, res, gun);
		}
	}
	destroy(&wolf->render, &wolf->win, &wolf->img, ar);
}
