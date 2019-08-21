/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:52:34 by snunes            #+#    #+#             */
/*   Updated: 2019/08/21 13:29:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		j;
	size_t	i;
	char	*str;

	j = 0;
	i = start;
	if (!s)
		return (NULL);
	if (!(str = (char *)ft_memalloc((size_t)(sizeof(*str) * len + 1))))
		return (NULL);
	while (i < (start + len))
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
