/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:18:55 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/31 19:01:10 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_str(char **ar)
{
	int i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

void	destroy(t_render *render, t_win *win, t_texture *img, char **ar)
{
	free(render->temp_srf);
	free_str(ar);
	SDL_FreeSurface(img->west_srf);
	SDL_FreeSurface(img->east_srf);
	SDL_FreeSurface(img->north_srf);
	SDL_FreeSurface(img->south_srf);
	SDL_FreeSurface(img->sky_srf);
	SDL_FreeSurface(img->h1_srf);
	SDL_FreeSurface(img->h2_srf);
	SDL_FreeSurface(img->h3_srf);
	SDL_FreeSurface(img->picture);
	SDL_DestroyTexture(img->sky);
	SDL_DestroyTexture(img->hand1);
	SDL_DestroyTexture(img->hand2);
	SDL_DestroyTexture(img->hand3);
	//SDL_DestroyTexture(img->gun);
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->win);
	win->win = NULL;
	win->render = NULL;
	SDL_Quit();
	exit(1);
}

int		main(int argc, char **args)
{
	char	**ar;
	t_all	wolf;

	if (argc != 2)
		error("arguments", 0);
	if (validation(args[1], 0) == 0)
		error("validation", 0);
	if (!(wolf.render.temp_srf = (Uint32 *)malloc(sizeof(Uint32) *
		(WID * HEI + 1))))
		error("malloc", 0);
	parse(args[1], &wolf.win.map);
	ar = make_ar(&wolf.win.map, &wolf.win);
	init_man(&wolf.man, ar);
	init_win(&wolf.win);
	init_textures_wall(&wolf.win, &wolf.img);
	initaudio();
	check_event(&wolf, ar);
	return (0);
}
