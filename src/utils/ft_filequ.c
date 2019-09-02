/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:34:33 by snunes            #+#    #+#             */
/*   Updated: 2019/08/30 16:42:52 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	abs_char(char c1, char c2)
{
	if (c1 >= 'a' && c1 <= 'z')
	{
		if (c2 >= 'A' && c2 <= 'Z')
		{
			if (c2 + 32 == c1)
				return (1);
			return (0);
		}
		return (c1 == c2);
	}
	else if (c1 >= 'A' && c1 <= 'Z')
	{
		if (c2 >= 'a' && c2 <= 'z')
		{
			if (c2 - 32 == c1)
				return (1);
			return (0);
		}
		return (c1 == c2);
	}
	return (c1 == c2);
}

int	ft_filequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (!abs_char(s1[i], s2[i]) && s1[i] != '/')
			return (0);
		i++;
	}
	if (!abs_char(s1[i], s2[i]) && s1[i] != '/')
		return (0);
	return (1);
}

int	ft_namelen(char *path)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1])
			j = i + 1;
		i++;
	}
	i = (path[i] == '/') ? i - 1 : i;
	return (ABS(i - j));
}
