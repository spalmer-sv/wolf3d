/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <spalmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:00:56 by sdonya            #+#    #+#             */
/*   Updated: 2020/10/27 17:41:07 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		error(const char *str, int fd)
{
	if (!str)
		ft_putstr_fd("Error Error\n", 2);
	else
	{
		ft_putstr_fd("Error ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	if (fd != 0)
		close(fd);
	exit(1);
}

int			countarrtochar(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}
