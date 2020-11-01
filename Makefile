# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 16:51:13 by sdonya            #+#    #+#              #
#    Updated: 2020/10/25 16:56:17 by sdonya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc
FLAGS = -g
LIBRARIES = -lft -L$(LIBFT_DIRECTORY) -L$(SDL_LIBRARY) -lSDL2
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS)

SDL_LIBRARY = $(HOME)/.brew/lib
SDL_HEADERS = $(HOME)/.brew/include/SDL2

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

HEADERS_LIST = wolf.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./src/
SOURCES_LIST = main.c init_sdl.c read_map.c validation.c move.c\
draw_man.c events.c raycast.c render.c audio.c initaudio.c audiocallback.c\
addmusic.c additional.c 
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = obj/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c -I$(HEADERS_DIRECTORY) -I$(SDL_HEADERS) -I$(LIBFT_HEADERS) $< -o $@

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

sdl:
	@brew install SDL2

sdlre:
	@brew reinstall SDL2

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all
