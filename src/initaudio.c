/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initaudio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:55:23 by sdonya            #+#    #+#             */
/*   Updated: 2020/10/27 17:15:26 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				init_a(t_privateaudio *gdevice, t_audio *global)
{
	(gdevice->want).freq = AUDIO_FREQUENCY;
	(gdevice->want).format = AUDIO_FORMAT;
	(gdevice->want).channels = AUDIO_CHANNELS;
	(gdevice->want).samples = AUDIO_SAMPLES;
	(gdevice->want).callback = (void *)audiocallback;
	(gdevice->want).userdata = calloc(1, sizeof(t_audio));
	global = (gdevice->want).userdata;
	if (global == NULL)
		error("Memory allocation error", 2);
	global->buffer = NULL;
	global->next = NULL;
}

void				initaudio(void)
{
	t_audio			*global;
	t_privateaudio	*gdevice;
	uint32_t		gsoundcount;

	gdevice = calloc(1, sizeof(t_privateaudio));
	gsoundcount = 0;
	if (gdevice == NULL)
		error("Memory c-allocation error", 2);
	gdevice->audio_enabled = 0;
	if (!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO))
		error("SDL_INIT_AUDIO not initialized", 2);
	SDL_memset(&(gdevice->want), 0, sizeof(gdevice->want));
	init_a(gdevice, global);
	if ((gdevice->device = SDL_OpenAudioDevice(NULL, 0, &(gdevice->want),\
	NULL, SDL_AUDIO_ALLOW_CHANGES)) == 0)
		error(SDL_GetError(), 0);
	else
	{
		gdevice->audio_enabled = 1;
		unpauseaudio(gdevice);
	}
	playmusic("music/highlands.wav", SDL_MIX_MAXVOLUME, gdevice, gsoundcount);
	free(gdevice);
}

void				playmusic(const char *filename, int volume,\
t_privateaudio *gdevice, uint32_t gsoundcount)
{
	playaudio(filename, volume, gdevice, gsoundcount);
}

void				freeaudio(t_audio *audio)
{
	t_audio		*temp;

	while (audio != NULL)
	{
		if (audio->free == 1)
			SDL_FreeWAV(audio->buffer_true);
		temp = audio;
		audio = audio->next;
		free(temp);
	}
}

void				endaudio(t_privateaudio *gdevice)
{
	if (gdevice->audio_enabled)
	{
		pauseaudio(gdevice);
		freeaudio((t_audio *)(gdevice->want).userdata);
		SDL_CloseAudioDevice(gdevice->device);
	}
	free(gdevice);
}
