/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:58:50 by spalmer           #+#    #+#             */
/*   Updated: 2020/10/27 17:40:22 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

typedef struct				s_get_next_line
{
	int						fd;
	char					*remainder;
	struct s_get_next_line	*next;
}							t_get_next_line;

# define BUFF_SIZE 32

int							get_next_line(const int fd, char **line);

#endif
