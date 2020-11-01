/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 22:20:10 by spalmer           #+#    #+#             */
/*   Updated: 2020/11/01 15:35:57 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		init_textures_sprites(t_win *win, t_texture *img)
{
	Uint32 colorkey;

	colorkey = 0xFFFFFF;
	if (!(img->h1_srf = SDL_LoadBMP("./img/hand.bmp")))
		error(SDL_GetError(), 0);
	if (SDL_SetColorKey(img->h1_srf, SDL_TRUE, colorkey))
		error(SDL_GetError(), 0);
	if (!(img->hand1 = SDL_CreateTextureFromSurface(win->render, img->h1_srf)))
		error(SDL_GetError(), 0);
	if (!(img->h2_srf = SDL_LoadBMP("./img/hand2.bmp")))
		error(SDL_GetError(), 0);
	if (SDL_SetColorKey(img->h2_srf, SDL_TRUE, colorkey))
		error(SDL_GetError(), 0);
	if (!(img->hand2 = SDL_CreateTextureFromSurface(win->render, img->h2_srf)))
		error(SDL_GetError(), 0);
	if (!(img->h3_srf = SDL_LoadBMP("./img/hand8.bmp")))
		error(SDL_GetError(), 0);
	if (SDL_SetColorKey(img->h3_srf, SDL_TRUE, colorkey))
		error(SDL_GetError(), 0);
	if (!(img->hand3 = SDL_CreateTextureFromSurface(win->render, img->h3_srf)))
		error(SDL_GetError(), 0);
	if (!(img->sky_srf = SDL_LoadBMP("./img/sky15.bmp")))
		error(SDL_GetError(), 0);
}

void		init_textures_wall(t_win *win, t_texture *img)
{
	if (!(img->west_srf = SDL_LoadBMP("./img/101.bmp")))
		error(SDL_GetError(), 0);
	if (!(img->east_srf = SDL_LoadBMP("./img/103.bmp")))
		error(SDL_GetError(), 0);
	if (!(img->north_srf = SDL_LoadBMP("./img/105.bmp")))
		error(SDL_GetError(), 0);
	if (!(img->south_srf = SDL_LoadBMP("./img/108.bmp")))
		error(SDL_GetError(), 0);
	if (!(img->picture = SDL_LoadBMP("./img/109.bmp")))
		error(SDL_GetError(), 0);
	init_textures_sprites(win, img);
	img->gun = img->hand1;
}

SDL_Rect	init_rect(float x, float y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

SDL_Window	*init_window(t_win *win)
{
	SDL_Window		*window;
	SDL_Renderer	*render;

	window = NULL;
	render = NULL;
	win->render = render;
	if (SDL_CreateWindowAndRenderer(WID, HEI, 0, &window, &win->render) != 0)
		error(SDL_GetError(), 0);
	return (window);
}

void		init_win(t_win *win)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error(SDL_GetError(), 0);
	win->win = init_window(win);
}
