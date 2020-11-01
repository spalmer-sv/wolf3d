/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:02:18 by sdonya            #+#    #+#             */
/*   Updated: 2020/10/27 17:15:26 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		unpauseaudio(t_privateaudio *gdevice)
{
	if (gdevice->audio_enabled)
		SDL_PauseAudioDevice(gdevice->device, 0);
}

t_audio		*createaudio(const char *filename, uint8_t loop, int volume)
{
	t_audio			*new;

	new = calloc(1, sizeof(t_audio));
	if (new == NULL)
		error("Memory allocation error", 2);
	if (filename == NULL)
		error("Warning: filename NULL:", 2);
	new->next = NULL;
	new->loop = loop;
	new->fade = 0;
	new->free = 1;
	new->volume = volume;
	if (SDL_LoadWAV(filename, &(new->audio), &(new->buffer_true),\
	&(new->length_true)) == NULL)
	{
		free(new);
		error("Warning: failed to open wave file: %s error:", 2);
	}
	new->buffer = new->buffer_true;
	new->length = new->length_true;
	(new->audio).callback = NULL;
	(new->audio).userdata = NULL;
	return (new);
}

void		addaudio(t_audio *root, t_audio *new)
{
	if (root == NULL)
		return ;
	while (root->next != NULL)
		root = root->next;
	root->next = new;
}

void		pauseaudio(t_privateaudio *gdevice)
{
	if (gdevice->audio_enabled)
		SDL_PauseAudioDevice(gdevice->device, 1);
}

void		playaudio(const char *filename,\
int volume, t_privateaudio *gdevice, uint32_t gsoundcount)
{
	t_audio		*new;
	uint8_t		loop;

	loop = 1;
	if (!gdevice->audio_enabled)
		return ;
	if (loop == 0)
	{
		if (gsoundcount >= AUDIO_MAX_SOUNDS)
			return ;
		else
			gsoundcount++;
	}
	if (filename != NULL)
		new = createaudio(filename, loop, volume);
	else
		error("Warning: filename and Audio parameters NULL", 2);
	SDL_LockAudioDevice(gdevice->device);
	if (loop == 1)
		addmusic((t_audio *)(gdevice->want).userdata, new);
	else
		addaudio((t_audio *)(gdevice->want).userdata, new);
	SDL_UnlockAudioDevice(gdevice->device);
}
