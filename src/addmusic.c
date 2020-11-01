/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addmusic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:38:57 by sdonya            #+#    #+#             */
/*   Updated: 2020/10/25 15:10:21 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		addmusic(t_audio *root, t_audio *new)
{
	uint8_t		musicfound;
	t_audio		*rootnext;

	musicfound = 0;
	rootnext = root->next;
	while (rootnext != NULL)
	{
		if (rootnext->loop == 1 && rootnext->fade == 0)
		{
			if (musicfound)
			{
				rootnext->length = 0;
				rootnext->volume = 0;
			}
			rootnext->fade = 1;
		}
		else if (rootnext->loop == 1 && rootnext->fade == 1)
			musicfound = 1;
		rootnext = rootnext->next;
	}
	addaudio(root, new);
}
