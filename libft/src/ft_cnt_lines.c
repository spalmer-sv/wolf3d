/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:58:47 by spalmer           #+#    #+#             */
/*   Updated: 2019/09/29 17:59:34 by spalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_cnt_lines(char const *s, char c)
{
	int		i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (cnt);
}
