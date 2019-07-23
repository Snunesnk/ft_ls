/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:07:52 by snunes            #+#    #+#             */
/*   Updated: 2019/04/15 19:07:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	char	occur;
	int		pos;
	int		i;

	occur = (char)c;
	pos = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == occur)
			pos = i;
		i++;
	}
	if (s[i] == occur)
		return ((char *)s + i);
	if (pos == -1)
		return (NULL);
	return ((char *)s + pos);
}
