/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 00:05:50 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/27 17:15:59 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "SDL.h"
# include "math.h"
# define SDL_AUDIO_ALLOW_CHANGES SDL_AUDIO_ALLOW_ANY_CHANGE
# define AUDIO_FORMAT AUDIO_S16LSB
# define AUDIO_FREQUENCY 48000
# define AUDIO_CHANNELS 2
# define AUDIO_SAMPLES 4096
# define AUDIO_MAX_SOUNDS 25
# define SCALE 1024
# define WID 800
# define HEI	600

typedef struct			s_map
{
	char				*data;
	struct s_map		*next;
}						t_map;

typedef struct			s_win
{
	t_map				map;
	int					wid;
	int					hei;
	SDL_Window			*win;
	SDL_Surface			*win_surface;
	SDL_Event			event;
	SDL_Renderer		*render;
}						t_win;

typedef	struct			s_norn
{
	int					width;
	int					alfavit;
	int					height;
	int					strok;
}						t_norm;

typedef	struct			s_hor_cast
{
	float				ay;
	float				ax;
	float				step_x;
	float				step_y;
	float				angle;
}						t_hor_cast;

typedef	struct			s_ver_cast
{
	float				by;
	float				bx;
	float				step_x;
	float				step_y;
	float				angle;
}						t_ver_cast;

typedef struct			s_man
{
	float				x;
	float				y;
	float				xhor_fin;
	float				yvert_fin;
	int					flag_side;
	float				fov;
	float				pov;
	float				angle;
	float				ver;
	float				hor;
	t_ver_cast			vercast;
	t_hor_cast			horcast;
}						t_man;

typedef struct			s_texture
{
	SDL_Texture			*west;
	SDL_Texture			*north;
	SDL_Texture			*east;
	SDL_Texture			*south;
	SDL_Texture			*sky;
	SDL_Texture			*hand1;
	SDL_Texture			*hand2;
	SDL_Texture			*hand3;
	SDL_Texture			*gun;
	SDL_Surface			*west_srf;
	SDL_Surface			*north_srf;
	SDL_Surface			*east_srf;
	SDL_Surface			*south_srf;
	SDL_Surface			*sky_srf;
	SDL_Surface			*picture;
	SDL_Surface			*h1_srf;
	SDL_Surface			*h2_srf;
	SDL_Surface			*h3_srf;
}						t_texture;

typedef	struct			s_render
{
	float				begin;
	float				height;
	int					x;
	Uint32				*temp_srf;
}						t_render;

typedef struct			s_all
{
	t_win				win;
	t_man				man;
	t_texture			img;
	t_render			render;
}						t_all;

typedef struct			s_privateaudio
{
	SDL_AudioDeviceID	device;
	SDL_AudioSpec		want;
	uint8_t				audio_enabled;
}						t_privateaudio;

typedef struct			s_audio
{
	uint32_t			length;
	uint32_t			length_true;
	uint8_t				*buffer_true;
	uint8_t				*buffer;
	uint8_t				loop;
	uint8_t				fade;
	uint8_t				free;
	uint8_t				volume;
	SDL_AudioSpec		audio;
	struct s_audio		*next;
}						t_audio;

void					init_win(t_win *win);
void					parse(char *av, t_map *map);
char					**make_ar(t_map *map, t_win *win);
void					print_struct(t_map *map);
void					print_ar(char **ar);
int						validation(char *str, int flag);
int						countarrtochar(char const *s, char c);
void					error(const char *str, int fd);
SDL_Rect				init_rect(float x, float y, int w, int h);
void					draw_man(t_man *man, t_win *win);
void					draw_rect(t_win *win, SDL_Rect *rect, SDL_Color color);
void					init_man(t_man *man, char **ar);
void					draw_line_view(t_all *wolf, char **ar);
void					check_event(t_all *wolf, char **ar);
void					init_textures_wall(t_win *win, t_texture *img);
void					render_textures(t_win *win, t_texture *img, \
						t_render *render, t_man *man);
float					find_ver_line(t_man *man, char **ar, t_win *win);
void					init_ver(t_man *man);
float					find_hor_line(t_man *man, char **ar, t_win *win);
void					init_hor(t_man *man);
float					check_angle(t_man *man);
void					destroy(t_render *render, t_win *win, t_texture *img, \
						char **ar);
void					check_move(t_man *man, t_win *win, SDL_Event *event, \
						char **ar);
void					check_move2(t_man *man, t_win *win, SDL_Event *event, \
						char **ar);
void					check_rotate(t_man *man, t_win *win, SDL_Event *event);
void					initaudio(void);
void					endaudio(t_privateaudio *gdevice);
void					pauseaudio(t_privateaudio *gdevice);
void					unpauseaudio(t_privateaudio *gdevice);
t_audio					*createaudio(const char *filename, uint8_t loop, \
						int volume);
void					addmusic(t_audio *root, t_audio *new);
void					addaudio(t_audio *root, t_audio *new);
void					playmusic(const char *filename, int volume,\
						t_privateaudio	*gdevice, uint32_t gsoundcount);
void					freeaudio(t_audio *audio);
void					playaudio(const char *filename, int volume, \
						t_privateaudio *gdevice, uint32_t gsoundcount);
uint32_t				audiotemplength(int len, t_audio *audio);
void					audiolen(t_audio *audio, t_audio *previous, \
						uint32_t gsoundcount);
void					audiobiglen(t_audio *audio, int templength, \
						uint8_t *stream, t_audio *previous);
void					audiobig(t_audio *audio, uint8_t music);
void					audiocallback(void *userdata, uint8_t *stream, \
						int len, uint32_t gsoundcount);

#endif
