/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:52:13 by sdonya            #+#    #+#             */
/*   Updated: 2020/10/27 16:52:45 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		null_tecstur(t_norm *norm)
{
	norm->strok = 0;
	norm->height = 0;
	norm->alfavit = 0;
	norm->width = 0;
}

int			chek_ones(char *line, t_norm *norm, int i, int j)
{
	if (line[i] != '1' && line[i] != ' ' && norm->strok == 0 && line[i] != 'P')
		return (0);
	else if (((line[0] != '1' || line[j - 1] != '1') && (line[0] != 'P' \
	|| line[j - 1] != 'P') && (line[0] != 'P' || line[j - 1] != '1') \
	&& (line[0] != '1' || line[j - 1] != 'P')) && norm->strok != 0)
		return (0);
	else if (line[i] != '1' && line[i] != ' ' \
	&& norm->strok == norm->height - 1 && line[i] != 'P')
		return (0);
	return (1);
}

int			checkline(char *line, int *flag, t_norm *norm)
{
	int		i;
	int		j;

	j = ft_strlen(line);
	i = 0;
	if (!line)
		error("no line", 2);
	while (line[i] != '\0')
	{
		if (!chek_ones(line, norm, i, j))
			return (0);
		if ((line[i] == '1' || line[i] == 'P') && line[i + 1] != '\0')
			if (line[i + 1] == '1' || line[i + 1] == 'P')
				return (0);
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && \
		line[i] != 'W' && line[i] != 'P')
			return (0);
		if (line[i] == 'W')
			(*flag)++;
		i++;
	}
	return (1);
}

void		chek_norm_val(t_norm *norm, char *line, int flag, char *str)
{
	int		fd;
	int		gnl;

	null_tecstur(norm);
	if ((fd = open(str, O_RDWR)) < 1)
		error("open fd validation", 0);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (checkline(line, &norm->alfavit, norm) == 0)
			error("check", fd);
		norm->strok = -1;
		if (flag == 0)
		{
			norm->width = countarrtochar(line, ' ');
			flag = norm->width;
		}
		if (countarrtochar(line, ' ') != flag || flag < 3)
			error("validation: wrong len", fd);
		norm->height++;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	close(fd);
}

int			validation(char *str, int flag)
{
	int		fd;
	int		gnl;
	char	*line;
	t_norm	norm;

	line = NULL;
	chek_norm_val(&norm, line, flag, str);
	norm.alfavit = 0;
	norm.strok = 0;
	if ((fd = open(str, O_RDWR)) < 1)
		error("open fd validation", 0);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (checkline(line, &norm.alfavit, &norm) == 0)
			error("check", fd);
		norm.strok++;
		ft_memdel((void **)&line);
	}
	if (norm.height < 3)
		error("validation: wrong len", fd);
	if ((gnl == 0 && norm.width == 0) || norm.alfavit != 1)
		error("read validation", 2);
	ft_memdel((void **)&line);
	close(fd);
	return (gnl == -1 ? 0 : 1);
}
