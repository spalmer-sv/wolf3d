/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:58:50 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/27 17:39:17 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char						*check_remainder(char *remainder, char **line)
{
	char					*p_n;

	p_n = NULL;
	if (remainder)
		if ((p_n = ft_strchr(remainder, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup(remainder);
			ft_strcpy(remainder, ++p_n);
		}
		else
		{
			*line = ft_strdup(remainder);
			ft_strclr(remainder);
		}
	else
		*line = ft_strnew(1);
	return (p_n);
}

int							get_line(const int fd, char **line,
		char **remainder)
{
	char					buf[BUFF_SIZE + 1];
	int						byte_was_read;
	char					*p_n;
	char					*tmp;

	tmp = NULL;
	p_n = check_remainder(*remainder, line);
	while (!p_n && (byte_was_read = read(fd, buf, BUFF_SIZE)))
	{
		buf[byte_was_read] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			tmp = ft_strdup(++p_n);
			free(*remainder);
			*remainder = tmp;
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)) || byte_was_read < 0)
			return (-1);
		free(tmp);
	}
	if (!(*remainder))
		return (byte_was_read || ft_strlen(*line)) ? 1 : 0;
	return (byte_was_read || ft_strlen(*line) || ft_strlen(*remainder)) ? 1 : 0;
}

t_get_next_line				*new_linked_list_el(int fd)
{
	t_get_next_line			*new;

	new = (t_get_next_line *)malloc(sizeof(t_get_next_line));
	if (!new)
		return (0);
	new->fd = fd;
	new->remainder = NULL;
	new->next = NULL;
	return (new);
}

int							get_next_line(const int fd, char **line)
{
	static t_get_next_line	*head;
	t_get_next_line			*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if (head == NULL)
		head = new_linked_list_el(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = new_linked_list_el(fd);
		tmp = tmp->next;
	}
	return (get_line(tmp->fd, line, &tmp->remainder));
}
