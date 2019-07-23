/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:24:51 by snunes            #+#    #+#             */
/*   Updated: 2019/05/15 21:18:05 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*source;
	char	*destination;

	source = (char *)src;
	destination = (char *)dst;
	i = 0;
	while (n > 0 && source[i])
	{
		destination[i] = source[i];
		n--;
		i++;
	}
	dst = (void *)destination;
	return (dst);
}
