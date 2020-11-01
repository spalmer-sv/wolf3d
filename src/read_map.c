/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 22:18:49 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/27 15:23:45 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_lstsize(t_map *map)
{
	t_map	*temp;
	int		len;

	len = 0;
	temp = map;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

void	init_ar(char **res, int *i, int *j, int *jj)
{
	i = 0;
	j = 0;
	jj = 0;
}

char	**clean_ar(char **input, int len, t_win *win)
{
	char	**res;
	int		i;
	int		j;
	int		jj;

	init_ar(res, &i, &j, &jj);
	res = (char **)malloc(sizeof(char*) * (len + 1));
	res[len] = NULL;
	win->wid = ft_strlen(input[i]) / 2 + 1;
	while (input[i])
	{
		res[i] = (char*)malloc(sizeof(char) * (ft_strlen(input[i]) / 2 + 2));
		while (input[i][j])
		{
			if (input[i][j] != ' ')
				res[i][jj++] = input[i][j];
			j++;
		}
		res[i][jj] = '\0';
		free(input[i++]);
		j = 0;
		jj = 0;
	}
	free(input);
	return (res);
}

char	**make_ar(t_map *map, t_win *win)
{
	int		len;
	char	**ar;
	t_map	*temp;
	int		i;

	i = 0;
	temp = map;
	len = ft_lstsize(map);
	win->hei = len - 1;
	ar = (char **)malloc(sizeof(char *) * (len + 1));
	ar[len] = NULL;
	while (temp)
	{
		ar[i] = temp->data;
		temp = temp->next;
		i++;
	}
	return (clean_ar(ar, len, win));
}

void	parse(char *av, t_map *map)
{
	int		fd;
	char	*line;
	t_map	*temp;

	temp = map;
	fd = open(av, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		temp->data = line;
		temp->next = (t_map *)malloc(sizeof(t_map));
		temp = temp->next;
	}
	temp->data = line;
	temp->next = NULL;
	close(fd);
}
