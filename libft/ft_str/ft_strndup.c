/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:30:01 by snunes            #+#    #+#             */
/*   Updated: 2019/05/02 19:35:09 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	int		i;
	char	*s2;

	i = 0;
	if (!(s2 = (char *)ft_memalloc(sizeof(*s2) * (len + 1))))
		return (NULL);
	while (s1[i] && len)
	{
		s2[i] = s1[i];
		i++;
		len--;
	}
	s2[i] = '\0';
	return (s2);
}
