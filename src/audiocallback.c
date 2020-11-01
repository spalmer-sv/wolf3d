/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audiocallback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:10:03 by sdonya            #+#    #+#             */
/*   Updated: 2020/10/27 17:15:11 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		audiobig(t_audio *audio, uint8_t music)
{
	if (audio->fade == 1 && audio->loop == 1)
	{
		music = 1;
		if (audio->volume > 0)
			audio->volume--;
		else
			audio->length = 0;
	}
}

void		audiobiglen(t_audio *audio, int templength, \
uint8_t *stream, t_audio *previous)
{
	SDL_MixAudioFormat(stream, audio->buffer, AUDIO_FORMAT,
			templength, audio->volume);
	audio->buffer += templength;
	audio->length -= templength;
	previous = audio;
}

void		audiolen(t_audio *audio, t_audio *previous, uint32_t gsoundcount)
{
	if (audio->loop == 1 && audio->fade == 0)
	{
		audio->buffer = audio->buffer_true;
		audio->length = audio->length_true;
	}
	else
	{
		previous->next = audio->next;
		if (audio->loop == 0)
			gsoundcount--;
		audio->next = NULL;
		freeaudio(audio);
		audio = previous->next;
	}
}

uint32_t	audiotemplength(int len, t_audio *audio)
{
	if ((uint32_t)len > audio->length)
		return (audio->length);
	else
		return (len);
}

void		audiocallback(void *userdata, uint8_t *stream,\
int len, uint32_t gsoundcount)
{
	t_audio		*audio;
	t_audio		*previous;
	int			templength;
	uint8_t		music;

	audio = (t_audio *)userdata;
	previous = audio;
	music = 0;
	SDL_memset(stream, 0, len);
	audio = audio->next;
	while (audio != NULL)
	{
		if (audio->length > 0)
		{
			audiobig(audio, music);
			if (music && audio->loop == 1 && audio->fade == 0)
				templength = 0;
			else
				templength = audiotemplength(len, audio);
			audiobiglen(audio, templength, stream, previous);
			audio = audio->next;
		}
		else
			audiolen(audio, previous, gsoundcount);
	}
}
