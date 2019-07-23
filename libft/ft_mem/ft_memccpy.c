/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:58:42 by snunes            #+#    #+#             */
/*   Updated: 2019/04/26 19:01:01 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int				i;
	unsigned char	convert;
	char			*source;
	char			*destination;

	i = 0;
	convert = (unsigned char)c;
	source = (char *)src;
	destination = (char *)dst;
	while (n > 0)
	{
		destination[i] = source[i];
		i++;
		n--;
		if ((unsigned char)(destination[i - 1]) == convert)
		{
			dst = (void *)destination;
			return (dst + i);
		}
	}
	return (NULL);
}
